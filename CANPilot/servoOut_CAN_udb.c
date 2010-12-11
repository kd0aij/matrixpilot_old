// SEE END OF FILE FOR LICENSE TERMS


#include "../libUDB/libUDB.h"
#include "../libCAN/libCAN.h"

#include <string.h>  	// for memcpy

//	routines to drive the PWM pins for the servos,
//	assumes the use of the 16MHz crystal.

int udb_pwOut[MAX_OUTPUTS+1] ;	// pulse widths for servo outputs

int twentyHertzCounter = 0 ;

void setupOutputs( void );

void udb_init_pwm( void )	// initialize the PWM
{
	CAN_init();

	PDC1 = PDC2 = PDC3 = 0 ;
	
	int i;
	for (i=0; i <= NUM_OUTPUTS; i++)
		udb_pwOut[i] = 0;
	
#if (NORADIO == 1)
	udb_flags._.radio_on = 1 ;
#endif
	
	TRISE = 0b1111111111000000 ;
	PTPER = 25000 ;	// 25 millisecond period at 16 Mz clock, prescale = 4	
	_PTCKPS = 1;	// prescaler = 4

	_PMOD1 = 1 ;	// independent PWM mode
	_PMOD2 = 1 ;
	_PMOD3 = 1 ;
	_PEN1L = 0 ; 	// low pins used as digital I/O
	_PEN2L = 0 ;
	_PEN3L = 0 ;
	
	_PTEN = 1; 		// turn on the PWM 
	_PWMIF = 0 ; 	// clear the PWM interrupt
	_PWMIP = 3 ;    // priority 3

	return ;
}


void udb_set_action_state(boolean newValue)
{
	_LATE4 = newValue ;
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
	
	udb_servo_callback_prepare_outputs() ;
	setupOutputs() ;
	
	_PWMIF = 0 ; /* clear the interrupt */
	
	// interrupt_restore_extended_state ;
	return ;
}


// Callback when servo outputs are received
void CAN_received_servo_outputs_callback(void)
{
}

void setupOutputs( void )
{
	PDC1 = udb_pwOut[1] ;
	PDC2 = udb_pwOut[2] ;
	PDC3 = udb_pwOut[3] ;
	
	CAN_send_servo_outputs();		// Do not do this when mixers are remote
//	CAN_send_Telemetry();
	
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
