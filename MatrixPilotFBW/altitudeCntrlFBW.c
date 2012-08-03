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

#include "../MatrixPilot/defines.h"
#include "fbw_options.h"
#include "fbwCntrl.h"
#include "inputCntrl.h"
#include "airspeedCntrl.h"


#include "airspeedCntrl.h"

union longww throttleFiltered = { 0 } ;

#define THROTTLEFILTSHIFT 12

#define MAXTHROTTLE			(2.0*SERVORANGE*ALT_HOLD_THROTTLE_MAX)
#define FIXED_WP_THROTTLE	(2.0*SERVORANGE*RACING_MODE_WP_THROTTLE)

#define THROTTLEHEIGHTGAIN (((ALT_HOLD_THROTTLE_MAX - ALT_HOLD_THROTTLE_MIN )*2.0*SERVORANGE )/(HEIGHT_MARGIN*2.0))

#define PITCHATMAX (ALT_HOLD_PITCH_MAX*(RMAX/57.3))
#define PITCHATMIN (ALT_HOLD_PITCH_MIN*(RMAX/57.3))
#define PITCHATZERO (ALT_HOLD_PITCH_HIGH*(RMAX/57.3))


int pitchAltitudeAdjust = 0 ;
boolean filterManual = false;

int desiredHeight ;

void normalAltitudeCntrl(void) ;
void manualThrottle(int throttleIn) ;
void hoverAltitudeCntrl(void) ;

// External variables
int height_margin					= HEIGHT_MARGIN;
fractional alt_hold_throttle_min	= ALT_HOLD_THROTTLE_MIN * RMAX;
fractional alt_hold_throttle_max	= ALT_HOLD_THROTTLE_MAX * RMAX;

// Internal computed variables.  Values defined above.
int max_throttle			= MAXTHROTTLE;
int throttle_height_gain 	= THROTTLEHEIGHTGAIN;


// Initialize to the value from options.h.  Allow updating this value from LOGO/MavLink/etc.
// Stored in 10ths of meters per second
int desiredSpeed = (DESIRED_SPEED*10) ;

// Get the desired altitude for guided mode only.
inline long get_guided_desired_altitude(void);


// Excess energy height.  Positive is too fast.
long excess_energy_height(int targetAspd, int actualAspd) // computes (1/2gravity)*( actual_speed^2 - desired_speed^2 )
{
	union longww accum;
	union longww height ;

	// targetAspd * 6 / 10 
	// 1/10 to scale from cm/s to dm/s
	// 6 is ~1/(2*g) with adjustments for x8 multiply later

	accum.WW = __builtin_mulsu ( actualAspd , 37877 ) ;
	height.WW = __builtin_mulss ( accum._.W1 , accum._.W1 ) ;

	accum.WW = __builtin_mulsu ( targetAspd , 37877 ) ;
	height.WW -= (__builtin_mulss ( accum._.W1 , accum._.W1 )) ;

	return height.WW;
}


void altitudeCntrl(void)
{
//	if ( canStabilizeHover() && current_orientation == F_HOVER )
//	{
//		hoverAltitudeCntrl() ;
//	}
//	else
//	{
		normalAltitudeCntrl() ;
//	}
//	
	return ;
}


void set_throttle_control(fractional throttle)
{	
	if ( flags._.altitude_hold_throttle || flags._.altitude_hold_pitch || filterManual )
	{
		ap_cntrls[AP_CNTRL_THROTTLE] = throttle;
		throttle_control = throttle;
	}
	else
	{
		ap_cntrls[AP_CNTRL_THROTTLE] = 0;
		throttle_control = in_cntrls[IN_CNTRL_THROTTLE];
	}
	
	return ;
}

inline boolean get_throttle_manual_lockout()
{
	return ( flags._.altitude_hold_throttle || flags._.altitude_hold_pitch || filterManual );
}


void setTargetAltitude(int targetAlt)
{
	desiredHeight = targetAlt ;
	return ;
}

long speed_height = 0 ;


inline long get_speed_height(void)
{
	return speed_height;
}


inline long get_guided_desired_altitude(void)
{
	if ( desired_behavior._.takeoff || desired_behavior._.altitude )
	{
		return goal.height ;
	}
	else
	{
		return ( goal.fromHeight + (((goal.height - goal.fromHeight) * (long)progress_to_goal)>>12) ) ;
	}
}

void normalAltitudeCntrl(void)
{
	union longww throttleAccum ;
	union longww pitchAccum ;
//	int throttleIn ;
//	int throttleInOffset ;
	union longww heightError = { 0 } ;

	union longww temp ;

	temp.WW = __builtin_mulss(alt_hold_throttle_max , 2.0 * SERVORANGE );
	temp.WW <<= 2;
	if(temp._.W0 & 0x8000) temp._.W1 ++;
	max_throttle =	temp._.W1;

	temp.WW = __builtin_mulss( (alt_hold_throttle_max - alt_hold_throttle_min ) , 2.0 * SERVORANGE );
	temp.WW <<= 2;
	if(temp._.W0 & 0x8000) temp._.W1++;
	temp._.W0 = temp._.W1;
	temp._.W1 = 0;
	throttle_height_gain =	__builtin_divsd(temp.WW, (height_margin << 1) );
	throttle_height_gain <<= 1;


	int height_marginx8 = height_margin << 3;

	speed_height = excess_energy_height(target_airspeed, air_speed_3DIMU) ; // equivalent height of the airspeed

	switch(ap_state())
	{
	case AP_STATE_MANUAL:
		set_throttle_control(in_cntrls[IN_CNTRL_THROTTLE]);
		break;
	case AP_STATE_STABILIZED:
		desiredHeight = get_fbw_demand_altitude();
		break;
	case AP_STATE_GUIDED:
		desiredHeight = get_guided_desired_altitude();
		break;
	default:
		set_throttle_control(in_cntrls[IN_CNTRL_THROTTLE]);
	}



//	if ( flags._.altitude_hold_throttle || flags._.altitude_hold_pitch )
//	{
//
//		if ( flags._.GPS_steering )
//		{
//		}
//		else
//		{

//		if ( throttleInOffset < (int)( DEADBAND ) && udb_flags._.radio_on )
//		{
//			pitchAltitudeAdjust = 0 ;
//			throttleAccum.WW  = 0 ;
//		}
//		else
//		{
//
//			heightError._.W1 = - desiredHeight ;
//			heightError.WW = ( heightError.WW + IMUlocationz.WW + speed_height ) >> 13 ;
//			if ( heightError._.W0 < -height_marginx8 )
//			{
//				throttleAccum.WW = (int)(max_throttle) ;
//			}
//			else if (  heightError._.W0 > height_marginx8 )
//			{
//				throttleAccum.WW = 0 ;
//			}
//			else
//			{
//				throttleAccum.WW = (int)(max_throttle) + (__builtin_mulss( throttle_height_gain, ( -heightError._.W0 - height_marginx8 ) )>>3) ;
//				if ( throttleAccum.WW > (int)(max_throttle) ) throttleAccum.WW = (int)(max_throttle) ;
//			}	
//

//		
//#if (RACING_MODE == 1)
//			if ( flags._.GPS_steering )
//			{
//				throttleAccum.WW = (long)(FIXED_WP_THROTTLE) ;
//			}
//#endif
//		}
//		
//		if ( !flags._.altitude_hold_throttle )
//		{
//			manualThrottle(throttleIn) ;
//		}
//		else if ( flags._.GPS_steering && desired_behavior._.land )
//		{
//			// place a ceiling, in other words, go down, but not up.
//			if ( pitchAltitudeAdjust > 0 )
//			{
//				pitchAltitudeAdjust = 0 ;
//			}
//			
//			throttleFiltered.WW += (((long)(udb_pwTrim[THROTTLE_INPUT_CHANNEL] - throttleFiltered._.W1 ))<<THROTTLEFILTSHIFT ) ;
//			set_throttle_control(throttleFiltered._.W1 - throttleIn) ;
//		}
//		else
//		{
//			// Servo reversing is handled in servoMix.c
//			int throttleOut = udb_servo_pulsesat( udb_pwTrim[THROTTLE_INPUT_CHANNEL] + throttleAccum.WW ) ;
//			throttleFiltered.WW += (((long)( throttleOut - throttleFiltered._.W1 )) << THROTTLEFILTSHIFT ) ;
//			set_throttle_control(throttleFiltered._.W1 - throttleIn) ;
//		}
//		
//		if ( !flags._.altitude_hold_pitch )
//		{
//			pitchAltitudeAdjust = 0 ;
//		}
//		
//		filterManual = true;
//	}
//	else
//	{
//		pitchAltitudeAdjust = 0 ;
//		manualThrottle() ;
//	}

	
	return ;
}



//fractional airspeed_pitch_adjust(void)
//{
//	union longww pitchAccum ;
//	union longww heightError = { 0 } ;
//    fractional airspeedAltitudeAdjust ;
//
//	heightError.WW = speed_height >> 13 ;
//	if ( heightError._.W0 < -height_marginx8 )
//	{
//		airspeedAltitudeAdjust = (int)(pitch_at_max) ;
//	}
//	else if (  heightError._.W0 > height_marginx8 )
//	{
//		airspeedAltitudeAdjust = (int)( pitch_at_zero ) ;
//	}
//	else
//	{
//		pitchAccum.WW = __builtin_mulss( (int)(pitch_height_gain) , - heightError._.W0 - height_marginx8)>>3 ;
//		airspeedAltitudeAdjust = (int)(pitch_at_max) + pitchAccum._.W0 ;
//	}
//
//	return airspeedAltitudeAdjust;
//}

void manualThrottle( fractional throttleIn )
{
	int throttle_control_pre ;
	
	throttleFiltered.WW += (((long)( throttleIn - throttleFiltered._.W1 )) << THROTTLEFILTSHIFT ) ;
	
	if (filterManual) {
		// Continue to filter the throttle control value in manual mode to avoid large, instant
		// changes to throttle value, which can burn out a brushed motor.  But after fading over
		// to the new throttle value, stop applying the filter to the throttle out to allow
		// faster control.
		throttle_control_pre = throttleFiltered._.W1 - throttleIn ;
		if (throttle_control_pre < 10) filterManual = false ;
	}
	else {
		throttle_control_pre = 0 ;
	}
	
	set_throttle_control(throttle_control_pre) ;
	
	return ;
}


// For now, hovering does not attempt to control the throttle, and instead
// gives manual throttle control back to the pilot.
//void hoverAltitudeCntrl(void)
//{
//	int throttle_control_pre ;
//	int throttleIn = ( udb_flags._.radio_on == 1 ) ? udb_pwIn[THROTTLE_INPUT_CHANNEL] : udb_pwTrim[THROTTLE_INPUT_CHANNEL] ;
//	
//	throttleFiltered.WW += (((long)( throttleIn - throttleFiltered._.W1 )) << THROTTLEFILTSHIFT ) ;
//	
//	if (filterManual) {
//		// Continue to filter the throttle control value in manual mode to avoid large, instant
//		// changes to throttle value, which can burn out a brushed motor.  But after fading over
//		// to the new throttle value, stop applying the filter to the throttle out to allow
//		// faster control.
//		throttle_control_pre = throttleFiltered._.W1 - throttleIn ;
//		if (throttle_control_pre < 10) filterManual = false ;
//	}
//	else {
//		throttle_control_pre = 0 ;
//	}
//	
//	set_throttle_control(throttle_control_pre) ;
//	
//	return ;
//}

