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


#include "../MatrixPilot/defines.h"
#include "../libCAN/libCAN.h"

union fbts_int flags ;
union fbts_int old_rtl_flags ;
int waggle = 0 ;
int calib_timer, standby_timer ;

void startS(void) ;
void calibrateS(void) ;
void acquiringS(void) ;
void stabilizedS(void) ;


//	Implementation of state machine.
//	Examine the state of the radio and GPS and supervisory channel to decide how to control the plane.

void (* stateS ) ( void ) = &startS ;

void init_states(void)
{
	gps_data_age = GPS_DATA_MAX_AGE+1 ;
	dcm_flags._.dead_reckon_enable = 0 ;
	stateS = &startS ;
	return ;
}

void udb_background_callback_periodic(void)
{
	//	Configure the GPS for binary if there is a request to do so.
	//	Determine whether the radio is on.
	
	if (gps_data_age < GPS_DATA_MAX_AGE) gps_data_age++ ;
	
	dcm_flags._.nav_capable = (gps_data_age < GPS_DATA_MAX_AGE) ;
	
	//	Execute the activities for the current state.
	(* stateS) () ;

	CAN_send_flags();
	
	return ;
}

//	Functions that are executed upon first entrance into a state.

//	Auto state provides augmented control. 
void ent_stabilizedS()
{
	flags._.GPS_steering = 0 ;
	flags._.pitch_feedback = 1 ;
	flags._.altitude_hold_throttle = (ALTITUDEHOLD_STABILIZED == AH_FULL) ;
	flags._.altitude_hold_pitch = (ALTITUDEHOLD_STABILIZED == AH_FULL || ALTITUDEHOLD_STABILIZED == AH_PITCH_ONLY) ;
	waggle = 0 ;
#if ( LED_RED_MAG_CHECK == 0 )
	LED_RED = LED_ON ;
#endif
	stateS = &stabilizedS ;
	return ;
}


//	Calibrate state is used to wait for the filters to settle before recording A/D offsets.
void ent_calibrateS()
{
	stateS = &calibrateS ;
	calib_timer = CALIB_PAUSE ;
	return ;
}

//	Acquire state is used to wait for the GPS to achieve lock.
void ent_acquiringS()
{
	// almost ready to turn the control on, save the trims and sensor offsets
	dcm_calibrate() ;
	
	stateS = &acquiringS ;
	standby_timer = STANDBY_PAUSE ;	
	return ;
}


void startS(void)
{
	ent_calibrateS() ;
	return ;
}

void calibrateS(void)
{
	if ( 1 )	//udb_flags._.radio_on
	{
		calib_timer--;
		if (calib_timer <= 0)
			ent_acquiringS() ;
	}
	else
	{
		ent_calibrateS() ;
	}
	return ;
}

void acquiringS(void)
{
	if ( dcm_flags._.nav_capable && ( ( MAG_YAW_DRIFT == 0 ) || ( magMessage == 7 ) ) )
	{
		if ( 1 ) //udb_flags._.radio_on
		{
			if (standby_timer == NUM_WAGGLES+1)
				waggle = WAGGLE_SIZE ;
			else if (standby_timer <= NUM_WAGGLES)
				waggle = - waggle ;
			else
				waggle = 0 ;
			
			standby_timer-- ;
			if ( standby_timer == 6 )
			{
				flags._.save_origin = 1 ;
			}
			else if ( standby_timer == 2 )
			{
				dcm_flags._.dead_reckon_enable = 1 ;
			}
			else if ( standby_timer <= 0)
			{
				ent_stabilizedS() ;
			}
		}
		else {
			waggle = 0 ;
		}
	}
	else
	{
		waggle = 0 ;
	}
	return ;
}


void stabilizedS(void) 
{
	return ;
}
