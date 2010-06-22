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


#include "libDCM.h"
#include "defines.h"

//	routines to drive the PWM pins for the servos,
//	assumes the use of the 16MHz crystal.

int gpscount ; // counter to initialize GPS
int calibcount ; // number of PWM pulses before control is turned on

char fourHertzCounter = 0 ;
boolean startTelemetry = 0 ;


void manualPassthrough( void ) ;


void init_servoPrepare( void )	// initialize the PWM
{
	calibcount = 400 ;	// wait 400 PWM pulses before turning on the control (10 seconds)
	gpscount = 1000 ;	// wait 25 seconds for GPS to initialize

	int i;
	for (i=0; i <= NUM_INPUTS; i++)
		if (i != THROTTLE_INPUT_CHANNEL)
			udb_pwTrim[i] = udb_pwIn[i] = 3000 ;
	
	for (i=0; i <= NUM_OUTPUTS; i++)
		if (i != THROTTLE_OUTPUT_CHANNEL)
			udb_pwTrim[i] = udb_pwIn[i] = udb_pwOut[i] = 3000 ;
	
#if (NORADIO == 1)
	udb_pwIn[MODE_SWITCH_INPUT_CHANNEL] = udb_pwTrim[MODE_SWITCH_INPUT_CHANNEL] = 4000 ;
#endif
	
	return ;
}


void dcm_servo_callback_prepare_outputs(void)
{
	// This is a simple counter to do stuff at 4hz
	fourHertzCounter++ ;
	if ( fourHertzCounter >= 10 )
	{
		if ( startTelemetry )
		{
			serial_output_4hz() ;
		}
		fourHertzCounter = 0 ;
	}
	
	
	switch ( calibcount ) {
		// case 0 is when the control is up and running
			
		case 0: {
			
#if ( DEADRECKONING == 1 )
			processwaypoints() ;
#endif
			
			updateBehavior() ;
			rollCntrl() ;
			yawCntrl() ;
			altitudeCntrl();
			pitchCntrl() ;
			servoMix() ;
#if ( USE_CAMERA_STABILIZATION == 1 )
			cameraCntrl();
#endif
			updateTriggerAction() ;
			break ;
		}
			
		case 1: {
			// almost ready to turn the control on, save the input offsets
			dcm_calibrate() ;
			manualPassthrough() ;	// Allow manual control while starting up
			startTelemetry = 1 ;
			break ;
		}
		default: {
			// otherwise, there is not anything to do
			manualPassthrough() ;	// Allow manual control while starting up
			break ;
		}
	}
	
	// count down the startup counter to 0
	if ( calibcount > 0 ) calibcount-- ;

	
	// count down the startup counter to 0
	gps_startup_sequence(gpscount) ;

	if ( gpscount > 0 ) gpscount-- ;
	
	return ;
}

void manualPassthrough( void )
{
	roll_control = pitch_control = yaw_control = altitude_control = 0 ;
	servoMix() ;
	
	return ;
}

