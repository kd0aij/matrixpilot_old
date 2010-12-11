// SEE END OF FILE FOR LICENSE TERMS


#include "../libCAN/libCAN.h"
#include "defines.h"

//	Measure the pulse widths of the servo channel inputs from the radio.
//	The capture timers are used for 8 cahnnels.  An extra channel is measured on an interrupt timer.

//	One of the channels is also used to validate pulse widths to detect loss of radio.

//	The pulse width inputs can be directly converted to units of pulse width outputs to control
//	the servos by simply dividing by 2.

// Function to set channel values and trigger other things on certain channels
void set_channel_measurement(const unsigned int Channel, const unsigned int Value);

int udb_pwIn[MAX_INPUTS+1];		// pulse widths of radio inputs
int udb_pwTrim[MAX_INPUTS+1];	// initial pulse widths for trimming
unsigned int rise[MAX_INPUTS+1] ;	// rising edge clock capture for radio inputs

int failSafePulses = 0 ;

// Empty, should never be used.
void CAN_received_radio_inputs_callback (void)
{
}


void udb_init_capture(void)
{
//	TRISD = TRISD | 0b1111111100001111 ;	// make the d port input, to enable IC1 and IC2
	TRISD = TRISD | 0b111111110000000 ;	// make the d port input, to enable IC1 and IC2
	IC1CON = IC2CON = IC7CON = IC8CON = 0b0010000010000001 ;
	IC3CON = IC4CON = IC5CON = IC6CON = 0b0010000010000001 ;
	
	IPC0bits.IC1IP = IPC1bits.IC2IP = IPC7bits.IC3IP = IPC7bits.IC4IP = 6 ; // priority 6
	IPC7bits.IC5IP = IPC7bits.IC6IP = IPC4bits.IC7IP = IPC4bits.IC8IP = 6 ; // priority 6

	IFS0bits.IC1IF = IFS0bits.IC2IF = IFS1bits.IC7IF = IFS1bits.IC8IF = 0 ; // clear the interrupt
	IFS1bits.IC3IF = IFS1bits.IC4IF = IFS1bits.IC5IF = IFS1bits.IC6IF = 0 ; // clear the interrupt

	IEC0bits.IC1IE = IEC0bits.IC2IE = IEC1bits.IC7IE = IEC1bits.IC8IE = 1 ; // turn on the interrupt
	IEC1bits.IC3IE = IEC1bits.IC4IE = IEC1bits.IC5IE = IEC1bits.IC6IE = 1 ; // turn on the interrupt

	T2CON = 0b1000000000000000  ;	// turn on timer 2 with no prescaler
//	TRISD = 0b1111111111111111 ;	// make the d port input, to enable IC1 and IC2

// If the spare channel is defined as being used, setup the timer for it.
// enable INT1 as a PWM input.
#if(SPARE_INPUT_CHANNEL != CHANNEL_UNUSED)
	TRISEbits.TRISE8 = 1 ;	 // set E8 to be an input pin
	INTCON2bits.INT1EP = 0;  // Set up the spare input channel to start out reading low-to-high edges
	IPC4bits.INT1IP = 7 ; 	// priority 7
	IFS1bits.INT1IF = 0 ; 	// clear the interrupt
	IEC1bits.INT1IE = 1 ; 	// turn on the interrupt
#endif

	return ;
}

// Input PWM Channel 1 = Radio input 6
void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
{
	interrupt_save_extended_state ;
	
//	indicate_loading_inter ;

	unsigned int time ;
	while ( IC1CONbits.ICBNE )
	{
		time = IC1BUF ;
	}
	
	if (PORTDbits.RD8)
	{
		rise[CHANNEL_6] = time ;
	}
	else
	{
		set_channel_measurement(CHANNEL_6, ((time - rise[CHANNEL_6]) >> 1 ));
	}

	IFS0bits.IC1IF =  0 ; // clear the interrupt
	
	interrupt_restore_extended_state ;
	return ;
}

// Input PWM Channel 2 = radio input 5
void __attribute__((__interrupt__,__no_auto_psv__)) _IC2Interrupt(void)
{
	interrupt_save_extended_state ;
	
//	indicate_loading_inter ;
	
	unsigned int time ;
	while ( IC2CONbits.ICBNE )
	{
		time = IC2BUF ;
	}
	
	if (PORTDbits.RD9)
	{
		rise[CHANNEL_5] = time;
	}
	else
	{
		set_channel_measurement(CHANNEL_5, ((time - rise[CHANNEL_5]) >> 1 ));
	}

	IFS0bits.IC2IF = 0 ; // clear the interrupt
	
	interrupt_restore_extended_state ;
	return ;
}


// Input PWM Channel 3 = Radio input 4
void __attribute__((__interrupt__,__no_auto_psv__)) _IC3Interrupt(void)
{
	interrupt_save_extended_state ;
	
//	indicate_loading_inter ;
	
	unsigned int time ;
	while ( IC3CONbits.ICBNE )
	{
		time = IC3BUF ;
	}
		
	if (PORTDbits.RD10)
	{
		 rise[CHANNEL_4] = time ;
	}
	else
	{
		set_channel_measurement(CHANNEL_4, ((time - rise[CHANNEL_4]) >> 1 ));
	}

	IFS1bits.IC3IF = 0 ; // clear the interrupt
	
	interrupt_restore_extended_state ;
	return ;
}

// Input PWM Channel 4 = Radio input 3
void __attribute__((__interrupt__,__no_auto_psv__)) _IC4Interrupt(void)
{
	interrupt_save_extended_state ;
	
//	indicate_loading_inter ;
	
	unsigned int time ;
	while ( IC4CONbits.ICBNE )
	{
		time = IC4BUF ;
	}
		
	if (PORTDbits.RD11)
	{
		 rise[CHANNEL_3] = time ;
	}
	else
	{
		set_channel_measurement(CHANNEL_3, ((time - rise[CHANNEL_3]) >> 1 ));
	}

	IFS1bits.IC4IF = 0 ; // clear the interrupt
	
	interrupt_restore_extended_state ;
	return ;
}

// Input PWM Channel 5 = Radio input 2
void __attribute__((__interrupt__,__no_auto_psv__)) _IC5Interrupt(void)
{
	interrupt_save_extended_state ;
	
//	indicate_loading_inter ;
		
	unsigned int time ;
	while ( IC5CONbits.ICBNE )
	{
		time = IC5BUF ;
	}
	
	if (PORTDbits.RD12)
	{
		 rise[CHANNEL_2] = time ;
	}
	else
	{
		set_channel_measurement(CHANNEL_2, ((time - rise[CHANNEL_2]) >> 1 ));
	}

	IFS1bits.IC5IF = 0 ; // clear the interrupt
	
	interrupt_restore_extended_state ;
	return ;
}

// Input PWM Channel 6 = Radio input 1
void __attribute__((__interrupt__,__no_auto_psv__)) _IC6Interrupt(void)
{
	interrupt_save_extended_state ;
	
//	indicate_loading_inter ;
		
	unsigned int time ;
	while ( IC6CONbits.ICBNE )
	{
		time = IC6BUF ;
	}
	
	if (PORTDbits.RD13)
	{
		 rise[CHANNEL_1] = time ;
	}
	else
	{
		set_channel_measurement(CHANNEL_1, ((time - rise[CHANNEL_1]) >> 1 ));
	}

	IFS1bits.IC6IF = 0 ; // clear the interrupt
	
	interrupt_restore_extended_state ;
	return ;
}

// Input Channel 7 = Radio input 7
void __attribute__((__interrupt__,__no_auto_psv__)) _IC7Interrupt(void)
{
	interrupt_save_extended_state ;
	
//	indicate_loading_inter ;
	
	unsigned int time ;
	while ( IC7CONbits.ICBNE )
	{
		time = IC7BUF ;
	}
		
	if (PORTDbits.RD14)
	{
		 rise[CHANNEL_7] = time ;
	}
	else
	{
		set_channel_measurement(CHANNEL_7, ((time- rise[CHANNEL_7]) >> 1 ));
	}

	IFS1bits.IC7IF = 0 ; // clear the interrupt
	
	interrupt_restore_extended_state ;
	return ;
}

// Input Channel 8 = Radio input 8
void __attribute__((__interrupt__,__no_auto_psv__)) _IC8Interrupt(void)
{
	interrupt_save_extended_state ;
	
//	indicate_loading_inter ;
		
	unsigned int time ;
	while ( IC8CONbits.ICBNE )
	{
		time = IC8BUF ;
	}
	
	if (PORTDbits.RD15)
	{
		 rise[CHANNEL_8] = time ;
	}
	else
	{
		set_channel_measurement(CHANNEL_8, ((time - rise[CHANNEL_8]) >> 1 ));
	}

	IFS1bits.IC8IF = 0 ; // clear the interrupt
	
	interrupt_restore_extended_state ;
	return ;
}



// Spare Input Channel on INT1 (Pin RE8)
void __attribute__((__interrupt__,__no_auto_psv__)) _INT1Interrupt(void)
{
	interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	int t = TMR2 ;
	
	if (PORTEbits.RE8)
	{
		rise[0] = t ;
		INTCON2bits.INT1EP = 1 ;	// Set up the interrupt to read high-to-low edges
	}
	else
	{
		set_channel_measurement(SPARE_INPUT_CHANNEL, ((t - rise[0]) >> 1 ));
		INTCON2bits.INT1EP = 0 ;	// Set up the interrupt to read low-to-high edges
	}
	
	IFS1bits.INT1IF = 0 ; 		// clear the interrupt
	
	interrupt_restore_extended_state ;
	return;
}


void set_channel_measurement(const unsigned int Channel, const unsigned int Value)
{
	if(Value > 5000) return;
	if(Value < 1000) return;

	udb_pwIn[Channel] =  Value;

	// Check if the last input has been done
	if(Channel == FAILSAFE_INPUT_CHANNEL)
	{
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_flags._.radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
	}	

};



/****************************************************************************/
// This is part of the servo and radio interface software
//
// ServoInterface source code
//	http://code.google.com/p/rc-servo-interface
//
// Copyright 2010 ServoInterface Team
// See the AUTHORS.TXT file for a list of authors of ServoInterface.
//
// ServoInterface is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ServoInterface is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with ServoInterface.  If not, see <http://www.gnu.org/licenses/>.
//
// Many parts of ServoInterface use either modified or unmodified code
// from the MatrixPilot pilot project.
// The project also contains code for modifying MatrixPilot to operate
// with ServoInterface.
// For details, credits and licenses of MatrixPilot see the AUTHORS.TXT file.
// or see this website: http://code.google.com/p/gentlenav
/****************************************************************************/
