// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009, 2010 MatrixPilot Team
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


////////////////////////////////////////////////////////////////////////////////
//
// GPS

void udb_init_GPS2(void)
{
	//	Initialize the USART that communicates with the GPS
	U2MODE = 0b0010000000000000 ; // turn off RX, used to clear errors
	U2STA  = 0b0000010100010000 ;
	
	U2BRG =  UDB_BAUD_9600 ;
	
	U2MODE = 0b1010000000000000 ; // turn on
	U2STA  = 0b0000010100010000 ;
	
	IFS1bits.U2RXIF = 0 ; // clear the interrupt
	IPC6bits.U2RXIP = 4 ; // priority 4
	IEC1bits.U2RXIE = 1 ; // turn on the interrupt
	
	return ;
}


void udb_gps_set_rate(int rate)
{
	U2BRG = rate ;
	return ;
}


void __attribute__((__interrupt__,__no_auto_psv__)) _U2RXInterrupt(void)
{
	interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	if ( U2STAbits.FERR ) { udb_init_GPS2(); }
	if ( U2STAbits.OERR ) { udb_init_GPS2(); }
	IFS1bits.U2RXIF = 0 ; // clear the interrupt
	while ( U2STAbits.URXDA )
	{
		unsigned char rxchar = U2RXREG ;
		udb_gps_callback_received_char(rxchar) ;
	}
	
	interrupt_restore_extended_state ;
	return ;
}


void udb_gps_send_char ( char outchar ) // output one character to the GPS
{
	//bin_out(outchar);
	while ( ! U2STAbits.TRMT ) { }
	U2TXREG = outchar ;
	return ;
}



////////////////////////////////////////////////////////////////////////////////
//
// Serial

void udb_init_USART1(void)
{	
	//	debugging/telemetry USART, runs at 19200 baud
	U1MODE = 0b0010000000000000 ; // turn off RX, used to clear errors
	U1STA  = 0b0000010100010000 ;
	
	U1BRG =  UDB_BAUD_9600 ;
	
	U1MODEbits.UARTEN = 1 ; // turn on uart
	U1MODEbits.ALTIO = 1 ; // use alternate pins
	
	U1STAbits.UTXEN = 1 ; // turn on transmitter
	
	IFS0bits.U1RXIF = 0 ; // clear the interrupt
	IPC2bits.U1RXIP = 3 ; // priority 3
	IEC0bits.U1RXIE = 1 ; // turn on the interrupt
	
	IFS0bits.U1TXIF = 0 ; // clear the interrupt 
 	IPC2bits.U1TXIP = 4 ; // priority 4 
 	IEC0bits.U1TXIE = 1 ; // turn on the interrupt
	
	return ;
}


void udb_serial_set_rate(int rate)
{
	U1BRG = rate ;
	return ;
}


void udb_serial_start_sending(void)
{
	IFS0bits.U1RXIF = 1 ; // fire the tx interrupt
	return ;
}


void __attribute__((__interrupt__,__no_auto_psv__)) _U1RXInterrupt(void)
{
	// interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	char rxchar = U1RXREG ;
	if ( U1STAbits.FERR ) {  udb_init_USART1(); }
	else if ( U1STAbits.OERR ) {  udb_init_USART1(); }
	
	IFS0bits.U1RXIF = 0 ; // clear the interrupt
	udb_serial_callback_received_char(rxchar) ;
	
	// interrupt_restore_extended_state ;
	return ;
}


void __attribute__((__interrupt__,__no_auto_psv__)) _U1TXInterrupt(void)
{
	interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	IFS0bits.U1TXIF = 0 ; // clear the interrupt 
	unsigned char txchar = udb_serial_callback_get_char_to_send() ;
	
	if ( txchar )
	{
		U1TXREG = txchar ;
	}
	
	interrupt_restore_extended_state ;
	return ;
}
