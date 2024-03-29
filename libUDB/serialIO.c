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
#include "oscillator.h"
#include "interrupt.h"
#include "ring_buffer.h"

// Baud Rate Generator -- See section 19.3.1 of datasheet.
// Fcy = FREQOSC / CLK_PHASES
// UXBRG = (Fcy/(16*BaudRate))-1
// UXBRG = ((32000000/2)/(16*9600))-1
// UXBRG = 103

#define UDB_BAUD(x) ((int16_t)(FCY / ((int32_t)4 * x) - 1))

// to be used with OpenLog for software flow control
// Warning: imcompatible with mavlink binary uplink
boolean pauseSerial = false;
#define SOFTWARE_FLOW_CONTROL 0

int16_t sb_index = 0;
int16_t end_index = 0;
char serial_interrupt_stopped = 1;

////////////////////////////////////////////////////////////////////////////////
//
// GPS

void udb_init_GPS(void)
{
	// configure U2MODE
	U1MODEbits.UARTEN = 0;      // Bit15 TX, RX DISABLED, ENABLE at end of func
	//                          // Bit14
	U1MODEbits.USIDL = 0;       // Bit13 Continue in Idle
	U1MODEbits.IREN = 0;        // Bit12 No IR translation
	U1MODEbits.RTSMD = 0;       // Bit11 Simplex Mode
	//                          // Bit10
	U1MODEbits.UEN = 0;         // Bits8,9 TX,RX enabled, CTS,RTS not
	U1MODEbits.WAKE = 0;        // Bit7 No Wake up (since we don't sleep here)
	U1MODEbits.LPBACK = 0;      // Bit6 No Loop Back
	U1MODEbits.ABAUD = 0;       // Bit5 No Autobaud (would require sending '55')
	U1MODEbits.URXINV = 0;      // Bit4 IdleState = 1  (for dsPIC)
	U1MODEbits.BRGH = 1;        // Bit3 4 clocks per bit period
	U1MODEbits.PDSEL = 0;       // Bits1,2 8bit, No Parity
	U1MODEbits.STSEL = 0;       // Bit0 One Stop Bit

	// Load all values in for U1STA SFR
	U1STAbits.UTXISEL1 = 0;     //Bit15 Int when Char is transferred (1/2 config!)
	U1STAbits.UTXINV = 0;       //Bit14 N/A, IRDA config
	U1STAbits.UTXISEL0 = 1;     //Bit13 Other half of Bit15
	//                          //Bit12
	U1STAbits.UTXBRK = 0;       //Bit11 Disabled
	//U1STAbits.UTXEN = 1;        //Bit10 TX pins controlled by periph (handled below)
	//U1STAbits.UTXBF = 0;        //Bit9 *Read Only Bit*
	//U1STAbits.TRMT = 0;         //Bit8 *Read Only bit*
	U1STAbits.URXISEL = 0;      //Bits6,7 Int. on character recieved
	U1STAbits.ADDEN = 0;        //Bit5 Address Detect Disabled
	//U1STAbits.RIDLE = 0;        //Bit4 *Read Only Bit*
	//U1STAbits.PERR = 0;         //Bit3 *Read Only Bit*
	//U1STAbits.FERR = 0;         //Bit2 *Read Only Bit*
	U1STAbits.OERR = 0;         //Bit1 *Read Only Bit*
	//U1STAbits.URXDA = 0;        //Bit0 *Read Only Bit*

	_U1TXIP = INT_PRI_U1TX;     // Mid Range Interrupt Priority level, no urgent reason
	_U1RXIP = INT_PRI_U1RX;     // Mid Range Interrupt Priority level, no urgent reason

	_U1TXIF = 0;                // Clear the Transmit Interrupt Flag
	_U1TXIE = 1;                // Disable Transmit Interrupts
	_U1RXIF = 0;                // Clear the Receive Interrupt Flag
	_U1RXIE = 1;                // Enable Receive Interrupts

	U1MODEbits.UARTEN = 1;      // And turn the peripheral on
	U1STAbits.UTXEN = 1;
}

void udb_gps_set_rate(int32_t rate)
{
#if (CONSOLE_UART != 1)
	U1BRG = UDB_BAUD(rate);
#endif
}

boolean udb_gps_check_rate(int32_t rate)
{
	return (U1BRG == UDB_BAUD(rate));
}

void udb_gps_start_sending_data(void)
{
	_U1TXIF = 1; // fire the tx interrupt
}

void __attribute__((__interrupt__,__no_auto_psv__)) _U1TXInterrupt(void)
{
	_U1TXIF = 0; // clear the interrupt
	indicate_loading_inter;
	interrupt_save_set_corcon;

#if (USE_HILSIM_USB != 1)
	int16_t txchar = udb_gps_callback_get_byte_to_send();
#else
	int16_t txchar = -1;
#endif
	if (txchar != -1)
	{
		U1TXREG = (uint8_t)txchar;
	}
	interrupt_restore_corcon;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1RXInterrupt(void)
{
	_U1RXIF = 0; // clear the interrupt
	indicate_loading_inter;
	interrupt_save_set_corcon;
	
	while (U1STAbits.URXDA)
	{
		uint8_t rxchar = U1RXREG;
#if (USE_HILSIM_USB != 1)
		udb_gps_callback_received_byte(rxchar);
#endif // USE_HILSIM_USB
	}
	U1STAbits.OERR = 0;
	interrupt_restore_corcon;
}


/////////////////////////////////////////////////////////////////////////////////////////
// Serial

void udb_init_USART(void)
{
	// configure U2MODE
	U2MODEbits.UARTEN = 0;      // Bit15 TX, RX DISABLED, ENABLE at end of func
	//                          // Bit14
	U2MODEbits.USIDL = 0;       // Bit13 Continue in Idle
	U2MODEbits.IREN = 0;        // Bit12 No IR translation
	U2MODEbits.RTSMD = 0;       // Bit11 Simplex Mode
	//                          // Bit10
	U2MODEbits.UEN = 0;         // Bits8,9 TX,RX enabled, CTS,RTS not
	U2MODEbits.WAKE = 0;        // Bit7 No Wake up (since we don't sleep here)
	U2MODEbits.LPBACK = 0;      // Bit6 No Loop Back
	U2MODEbits.ABAUD = 0;       // Bit5 No Autobaud (would require sending '55')
	U2MODEbits.URXINV = 0;      // Bit4 IdleState = 1  (for dsPIC)
	U2MODEbits.BRGH = 1;        // Bit3 4 clocks per bit period
	U2MODEbits.PDSEL = 0;       // Bits1,2 8bit, No Parity
	U2MODEbits.STSEL = 0;       // Bit0 One Stop Bit

	// Load all values in for U1STA SFR
	U2STAbits.UTXISEL1 = 0;     //Bit15 Int when Char is transferred (1/2 config!)
	U2STAbits.UTXINV = 0;       //Bit14 N/A, IRDA config
	U2STAbits.UTXISEL0 = 1;     //Bit13 Other half of Bit15
	//                          //Bit12
	U2STAbits.UTXBRK = 0;       //Bit11 Disabled
	//U2STAbits.UTXEN = 1;        //Bit10 TX pins controlled by periph (handled below)
	//U2STAbits.UTXBF = 0;        //Bit9 *Read Only Bit*
	//U2STAbits.TRMT = 0;         //Bit8 *Read Only bit*
	U2STAbits.URXISEL = 0;      //Bits6,7 Int. on character recieved
	U2STAbits.ADDEN = 0;        //Bit5 Address Detect Disabled
	//U2STAbits.RIDLE = 0;        //Bit4 *Read Only Bit*
	//U2STAbits.PERR = 0;         //Bit3 *Read Only Bit*
	//U2STAbits.FERR = 0;         //Bit2 *Read Only Bit*
	U2STAbits.OERR = 0;         //Bit1 *Read Only Bit*
	//U2STAbits.URXDA = 0;        //Bit0 *Read Only Bit*

	_U2TXIP = INT_PRI_U2TX;     // Mid Range Interrupt Priority level, no urgent reason
	_U2RXIP = INT_PRI_U2RX;     // Mid Range Interrupt Priority level, no urgent reason

	_U2TXIF = 0;                // Clear the Transmit Interrupt Flag
	_U2TXIE = 1;                // Enable Transmit Interrupts
	_U2RXIF = 0;                // Clear the Receive Interrupt Flag
	_U2RXIE = 1;                // Enable Receive Interrupts

	U2MODEbits.UARTEN = 1;      // And turn the peripheral on
	U2STAbits.UTXEN = 1;
}

void udb_serial_set_rate(int32_t rate)
{
	U2BRG = UDB_BAUD(rate);
}

boolean udb_serial_check_rate(int32_t rate)
{
	return (U2BRG == UDB_BAUD(rate));
}

void udb_serial_start_sending_data(void)
{
	_U2TXIF = 1; // fire the tx interrupt
}

#ifndef USE_RING_BUFFER
int16_t udb_serial_callback_get_byte_to_send(void)
{
	if (sb_index < end_index && sb_index < SERIAL_BUFFER_SIZE) // ensure never end up racing thru memory.
	{
		uint8_t txchar = serial_buffer[ sb_index++ ];
		return txchar;
	}
	else
	{
		serial_interrupt_stopped = 1;
	}
	return -1;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U2TXInterrupt(void)
{
	_U2TXIF = 0; // clear the interrupt
	indicate_loading_inter;
	interrupt_save_set_corcon;

	int16_t txchar = udb_serial_callback_get_byte_to_send();
	if (txchar != -1)
	{
		U2TXREG = (uint8_t)txchar;
	}
	interrupt_restore_corcon;
}
#else

// Return one character at a time, as requested.
// Requests will stop after we return false.
// called by _U2TXInterrupt at IPL5

boolean udb_serial_callback_get_binary_to_send(char *c)
{
	boolean status = false;

#if (SOFTWARE_FLOW_CONTROL != 0)
	if (!pauseSerial)
#endif
	{
		status = ring_get(c);
	}

	if (!status)
		serial_interrupt_stopped = 1;

	return status;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U2TXInterrupt(void)
{
	_U2TXIF = 0; // clear the interrupt
	indicate_loading_inter;
	interrupt_save_set_corcon;

	char txchar;
	boolean status = udb_serial_callback_get_binary_to_send(&txchar);

	if (status)
		U2TXREG = (unsigned char) txchar;

	interrupt_restore_corcon;
	return;
}
#endif

void __attribute__((__interrupt__, __no_auto_psv__)) _U2RXInterrupt(void)
{
	_U2RXIF = 0; // clear the interrupt
	indicate_loading_inter;
	interrupt_save_set_corcon;

	while (U2STAbits.URXDA)
	{
		uint8_t rxchar = U2RXREG;
		udb_serial_callback_received_byte(rxchar);
	}
	U2STAbits.OERR = 0;
	interrupt_restore_corcon;
}
