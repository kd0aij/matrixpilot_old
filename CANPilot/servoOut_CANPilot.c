// SEE END OF FILE FOR LICENSE TERMS

#include "../libUDB/libUDB.h"
#include "../libUDB/libUDB_internal.h"
#include "../libDCM/libDCM.h"
//#include "../libCAN/libCAN.h"
//#include "CANInterface_defines.h"
#include <string.h>


//	routines to drive the PWM pins for the servos,
//	assumes the use of the 16MHz crystal.

// Tracking the output number for bit bashed outputs
unsigned char outputNum ;	

int twentyHertzCounter = 0 ;

int udb_pwOut[MAX_OUTPUTS+1];	// pulse widths for servo outputs in UDB loop

void setupOutputs( void ) ;
//void manualPassthrough( void ) ;



void udb_init_pwm( void )	// initialize the PWM
{
	PDC1 = PDC2 = PDC3 = PDC4 = 0 ;
	
	int i;
	for (i=0; i <= NUM_OUTPUTS; i++)
		udb_pwOut[i] = 0;
	
	TRISE &= 0xFF00 ;		// Set low byte portE PWMs to outputs
	PTPER = 25000 ;			// 25 millisecond period at 16 Mz clock, prescale = 4	
	PTCONbits.PTCKPS = 1;	// prescaler = 4

	PWMCON1bits.PMOD1 = 1 ; // independent PWM mode
	PWMCON1bits.PMOD2 = 1 ;
	PWMCON1bits.PMOD3 = 1 ;
	PWMCON1bits.PMOD4 = 1 ;

	PWMCON1bits.PEN1H = 1 ; // High pins used as PWM
	PWMCON1bits.PEN2H = 1 ;
	PWMCON1bits.PEN3H = 1 ;
	PWMCON1bits.PEN4H = 1 ;

	PWMCON1bits.PEN1L = 0 ; // low pins used as digital I/O
	PWMCON1bits.PEN2L = 0 ;
	PWMCON1bits.PEN3L = 0 ;
	PWMCON1bits.PEN4L = 0 ;
	
	PTCONbits.PTEN = 1; 	// turn on the PWM 
	IFS2bits.PWMIF = 0 ; 	// clear the PWM interrupt
	IPC9bits.PWMIP = 3 ;    // priority 3
//	IPC9bits.PWMIP = 1 ;    // priority 1
	
	T4CON = 0b1000000000000000  ;	// turn on timer 4 with no prescaler
	IPC5bits.T4IP = 7 ;				// priority 7
	IEC1bits.T4IE = 0 ;				// disable timer 4 interrupt for now (enable for each set of pulses)

	//  note: at this point the PWM is running, so there are pulses going out,
	//	but the PWM interrupt is still off, so no interrupts are coming in yet to compute pulses.
	//  the PWM interrupt is turned on within the A/D interrupt processing

	// PWM is requried to run to keep the watchdog timer alive
	// PWM is activated by setting flag 	op_control.pwm_active = 1;
	IEC2bits.PWMIE = 1 ;     // enable the PWM interrupt

	return ;
}



void __attribute__((__interrupt__,__no_auto_psv__)) _PWMInterrupt(void)
{
	// interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	//	Executes whatever needs to be done every 25 milliseconds, using the PWM clock.
	//	This is a good place to run the A/D digital filters and compute pulse widths for servos.
	//	Also, this is used to wait a few pulses before recording input DC offsets.

#if ( NORADIO == 0 )
	twentyHertzCounter++ ;
	if ( twentyHertzCounter >= 2 )
	{
		if ( failSafePulses == 0 )
		{
			udb_flags._.radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
		else if ( failSafePulses >= 2 )
		{
			udb_flags._.radio_on = 1 ;
			LED_GREEN = LED_ON ;
		}
		twentyHertzCounter = 0 ;
		failSafePulses = 0 ;
	}
#endif
	
	CAN_failsafe_clock();

	udb_servo_callback_prepare_outputs() ;
	setupOutputs() ;

	CAN_send_servo_outputs();
	CAN_send_flags();


	ClrWdt();

	_PWMIF = 0 ; /* clear the interrupt */
	
	// interrupt_restore_extended_state ;
	return ;
}


void setupOutputs( void )
{
	PDC1 = udb_pwOut[CHANNEL_7] ;
	PDC2 = udb_pwOut[CHANNEL_5] ;
	PDC3 = udb_pwOut[CHANNEL_3] ;
	PDC4 = udb_pwOut[CHANNEL_1] ;

	outputNum = 5 ;
	if ( udb_pwOut[CHANNEL_8] > 0 )
	{
		PR4 = (udb_pwOut[CHANNEL_8] << 1) ;	// set timer to the pulse width
		LATEbits.LATE0 = 1 ;	// start the pulse by setting the E0 pin high
	}
	else
	{
		PR4 = 100 ;				// set timer to a short wait
		LATEbits.LATE0 = 0 ;	// skip the pulse by setting the E0 pin low
	}	
	TMR4 = 0 ;				// start timer at 0
	IFS1bits.T4IF = 0 ;		// clear the interrupt
	IEC1bits.T4IE = 1 ;		// enable timer 4 interrupt

	return;
}

void __attribute__((__interrupt__,__no_auto_psv__)) _T4Interrupt(void)
{
	interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	switch ( outputNum ) {
		case 5:
			LATEbits.LATE0 = 0 ;		// end the pulse by setting the E0 pin low
			if ( udb_pwOut[CHANNEL_6] > 0 )
			{
				PR4 = (udb_pwOut[CHANNEL_6] << 1) ;	// set timer to the pulse width
				LATEbits.LATE2 = 1 ;	// start the pulse by setting the E2 pin high
			}
			else
			{
				PR4 = 100 ;				// set timer to the pulse width
				LATEbits.LATE2 = 0 ;	// skip the pulse by setting the E2 pin low
			}	
			TMR4 = 0 ;				// start timer at 0
			break;
		
		case 6:
			LATEbits.LATE2 = 0 ;		// end the pulse by setting the E2 pin low

			if ( udb_pwOut[CHANNEL_4] > 0 )
			{
				PR4 = (udb_pwOut[CHANNEL_4] << 1) ;	// set timer to the pulse width
				LATEbits.LATE4 = 1 ;	// start the pulse by setting the E4 pin high
			}
			else
			{
				PR4 = 100 ;				// set timer to the pulse width
				LATEbits.LATE4 = 0 ;	// skip the pulse by setting the E4 pin low
			}
			TMR4 = 0 ;				// start timer at 0
			break ;

		case 7:
			LATEbits.LATE4 = 0 ;		// end the pulse by setting the E4 pin low
			if ( udb_pwOut[CHANNEL_2] > 0 )
			{
				PR4 = (udb_pwOut[CHANNEL_2] << 1) ;	// set timer to the pulse width
				LATEbits.LATE6 = 1 ;	// start the pulse by setting the E6 pin high
			}
			else
			{
				PR4 = 100 ;				// set timer to the pulse width
				LATEbits.LATE6 = 0 ;	// skip the pulse by setting the E6 pin low
			}
			TMR4 = 0 ;				// start timer at 0
			break ;
		default:
			LATEbits.LATE6 = 0 ;		// end the pulse by setting the E4 pin low (output 6)
			IEC1bits.T4IE = 0 ;			// disable timer 4 interrupt
			break ;
	}
	
	outputNum++;

	IFS1bits.T4IF = 0 ;					// clear the interrupt
	
	interrupt_restore_extended_state ;
	return;
}

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
