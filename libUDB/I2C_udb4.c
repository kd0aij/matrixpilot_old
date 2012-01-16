// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


#include "libUDB_internal.h"

#if (BOARD_TYPE == UDB4_BOARD)

#define I2C1_SDA 		_RG3
#define I2C1_SCL 		_RG2

#define I2C1_SDA_TRIS 	_TRISG3
#define I2C1_SCL_TRIS 	_TRISG2

#define _I2C1EN 		I2C1CONbits.I2CEN

//const unsigned char enableMagRead[] =        { 0x3C , 0x00 , 0x10 , 0x20 , 0x00 } ;
//const unsigned char enableMagCalibration[] = { 0x3C , 0x00 , 0x11 , 0x20 , 0x01 } ;
//const unsigned char resetMagnetometer[]    = { 0x3C , 0x00 , 0x10 , 0x20 , 0x02 } ;

void I2C1_start(void) ;
void I2C1_idle(void) ;
void I2C1_stopReadMagData(void);
void I2C1_doneRead(void);
void I2C1_recstore(void);
void I2C1_rerecen(void);
void I2C1_recen(void);
void I2C1_stop(void);
void I2C1_stopRead(void);
void I2C1_writeDataByte(void);
void I2C1_Command(void);


int I2C1ERROR = 0 ;
int I2C1interrupts = 0 ;

void (* I2C1_state ) ( void ) = &I2C1_idle ;

#define I2C1BRGVAL 120 // 100 Khz

#define I2C1_NORMAL ((( I2C1CON & 0b0000000000011111 ) == 0) && ( (I2C1STAT & 0b0100010011000001) == 0 ))


unsigned int I2C1_writeIndex = 0;  		// index into the write buffer
unsigned int I2C1_readIndex = 0; 		// index into the read buffer

unsigned int I2C1_tx_data_size = 0;		// tx data size
unsigned int I2C1_rx_data_size = 0;		// rx data size

unsigned char* pI2C1txBuffer = NULL;	// pointer to transmit buffer
unsigned char* pI2C1rxBuffer = NULL;	// pointer to receive  buffer

unsigned char I2C1txBuffer[16] = {'A', '5', 'A', '5'};
unsigned char I2C1rxBuffer[32];

// To pause a number of service cycles
unsigned int I2C1Pause = 0 ;


void udb_init_I2C1(void)
{
//	I2C1_SDA_TRIS = I2C1_SCL_TRIS = 0 ;		// SDA and SCL as outputs
	I2C1BRG = I2C1BRGVAL ; 
	_I2C1EN = 1 ; 	 		// enable I2C1		

	_MI2C1IP = 5 ; 			// I2C1 at priority 5
	_MI2C1IF = 0 ; 			// clear the I2C1 master interrupt
	_MI2C1IE = 1 ; 			// enable the interrupt
	return ;
}


void serviceI2C1(void)  // service the I2C
{
	if ( _I2C1EN == 0 ) // I2C is off
	{
		I2C1_state = &I2C1_idle ; 	// disable response to any interrupts
//		I2C1_SDA = I2C1_SCL = 1 ; 	// pull SDA and SCL high
		udb_init_I2C1() ; 			// turn the I2C back on
		// Put something here to reset state machine.  Make sure attached servies exit nicely.
		return ;
	}

	if (  I2C1_NORMAL )
	{
	}
	else
	{
		I2C1_state = &I2C1_idle ;	// disable the response to any more interrupts
		I2C1ERROR = I2C1STAT ; 		// record the error for diagnostics
		_I2C1EN = 0 ;  				// turn off the I2C
		_MI2C1IF = 0 ; 				// clear the I2C master interrupt
		_MI2C1IE = 0 ; 				// disable the interrupt
//		I2C1_SDA = I2C1_SCL = 0 ;	// pull SDA and SCL low
		// Put something here to reset state machine.  Make sure attached servies exit nicely.
		return ;
	}

	if ( I2C1Pause == 0 )
	{
		pI2C1txBuffer = I2C1txBuffer;
		pI2C1rxBuffer = I2C1rxBuffer;

		I2C1_tx_data_size = 2;
		I2C1_rx_data_size = 0;

//		I2C1CONbits.PEN = 1 ;

//		I2C1TRN = 0xAA;
		I2C1_state = &I2C1_Command;
		_MI2C1IF = 1 ;

		I2C1Pause = 10;
	}
	else
	{
		I2C1Pause -- ;
	}
	return ;
}

void __attribute__((__interrupt__,__no_auto_psv__)) _MI2C1Interrupt(void)
{
	indicate_loading_inter ;
	interrupt_save_set_corcon ;
	
	_MI2C1IF = 0 ; // clear the interrupt
	(* I2C1_state) () ; // execute the service routine
	
	interrupt_restore_corcon ;
	return ;
}


void I2C1_Command(void)
{
	I2C1_writeIndex = 0;  		// Reset index into the write buffer
	I2C1_readIndex = 0; 		// Reset index into the read buffer

	I2C1_state = &I2C1_writeDataByte ;
	I2C1CONbits.SEN = 1 ;
	return ;
}

void I2C1_writeDataByte(void)
{
	I2C1TRN = pI2C1txBuffer[I2C1_writeIndex++] ;
	if ( I2C1_writeIndex >= I2C1_tx_data_size)
	{
		I2C1_state = &I2C1_recen ;
	}
	return ;
}

void I2C1_stop(void)
{
	I2C1_state = &I2C1_idle ;
	I2C1CONbits.PEN = 1 ;
	return ;
}


void I2C1_recen(void)
{
	if ( I2C1STATbits.ACKSTAT == 1 )  	// Device not responding
	{
		// Put something here to reset state machine.  Make sure attached servies exit nicely.
		I2C1CONbits.PEN = 1; // stop the bus
		I2C1_state = &I2C1_idle ; 
	}
	else
	{
		I2C1CONbits.RCEN = 1 ;
		I2C1_state = &I2C1_recstore ;
	}
	return ;
}

void I2C1_rerecen(void)
{
	I2C1CONbits.RCEN = 1 ;
	I2C1_state = &I2C1_recstore ;
	return ;
}

void I2C1_recstore(void)
{
	pI2C1rxBuffer[I2C1_readIndex++] = I2C1RCV ;
	if ( I2C1_readIndex > I2C1_rx_data_size )
	{
		I2C1CONbits.ACKDT = 1 ;
		I2C1_state = &I2C1_stopRead ;
	}
	else
	{
		I2C1CONbits.ACKDT = 0 ;
		I2C1_state = &I2C1_rerecen ;
	}
	I2C1CONbits.ACKEN = 1 ;
	return ;
}


void I2C1_stopRead(void)
{
	I2C1CONbits.PEN = 1;
	I2C1_state = &I2C1_doneRead ;
	return ;
}


void I2C1_idle(void)
{
	return ;
}

void I2C1_doneRead(void)
{
}

#endif
