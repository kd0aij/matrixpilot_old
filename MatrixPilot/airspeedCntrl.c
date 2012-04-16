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


#include "defines.h"
#include "airspeedCntrl.h"

int 	airspeed		= 0;
long 	airspeed2 		= 0;
int 	groundspeed		= 0;
long 	groundspeed2 	= 0;
int 	airspeedError	= 0;
int		airspeedDelta		= 0;
int		groundspeedDelta	= 0;

// Last speeds recorded for doing differential control
int 	lastAirspeed 	= 0;
int 	lastGroundspeed	= 0;

int minimum_groundspeed		= MINIMUM_GROUNDSPEED;
int minimum_airspeed		= MINIMUM_AIRSPEED;
int maximum_airspeed		= MAXIMUM_AIRSPEED;
int airspeed_adj_range		= AIRSPEED_ADJ_RANGE;

// Previous target airspeed. Caution, this is in cm/s
int previous_target_airspeed	= 0;

int	target_speed_as_groundspeed 	= TARGET_SPEED_AS_GROUNDSPEED;

int maximum_target_airspeed_rate	= MAXIMUM_TARGET_AIRSPEED_RATE;

fractional airspeed_pitch_kp 	= AIRSPEED_PITCH_KP * RMAX;
fractional airspeed_pitch_kd 	= AIRSPEED_PITCH_KD * RMAX;
fractional groundspeed_pitch_kd = GROUNDSPEED_PITCH_KD * RMAX;

#define ASPD_BUFF_SIZE 20
int airspeed_buff[ASPD_BUFF_SIZE];
unsigned char	aspd_buff_pos;


void calc_airspeed(void)
{
	int speed_component ;
	union longww accum ;
	long fwdapsd2 = 0;

	lastAirspeed = airspeed;
	lastGroundspeed = groundspeed;

	speed_component = IMUvelocityx._.W1 - estimatedWind[0] ;
	accum.WW = __builtin_mulsu ( speed_component , 37877 ) ;
	fwdapsd2 += __builtin_mulss ( accum._.W1 , accum._.W1 ) ;

	speed_component = IMUvelocityy._.W1 - estimatedWind[1] ;
	accum.WW = __builtin_mulsu ( speed_component , 37877 ) ;
	fwdapsd2 += __builtin_mulss ( accum._.W1 , accum._.W1 ) ;

	speed_component = IMUvelocityz._.W1 - estimatedWind[2] ;
	accum.WW = __builtin_mulsu ( speed_component , 37877 ) ;
	fwdapsd2 += __builtin_mulss ( accum._.W1 , accum._.W1 ) ;

	airspeed >>= 1;
	airspeed  += (sqrt_long(fwdapsd2)) >> 1;
	airspeed2 = fwdapsd2;

	// Airspeed deltas with filtering
	airspeed_buff[aspd_buff_pos] = airspeed;
	aspd_buff_pos++;
	if(aspd_buff_pos >= ASPD_BUFF_SIZE) aspd_buff_pos = 0;
	airspeedDelta >>= 1;
	airspeedDelta += (airspeed - airspeed_buff[aspd_buff_pos]) >> 1;
}

void calc_groundspeed(void) // computes (1/2gravity)*( actual_speed^2 - desired_speed^2 )
{
	long ground_speed2_ = 0;
	union longww accum ;

	accum.WW = __builtin_mulsu ( IMUvelocityx._.W1 , 37877 ) ;
	ground_speed2_ += __builtin_mulss ( accum._.W1 , accum._.W1 ) ;

	accum.WW = __builtin_mulsu ( IMUvelocityy._.W1 , 37877 ) ;
	ground_speed2_ += __builtin_mulss ( accum._.W1 , accum._.W1 ) ;

	accum.WW = __builtin_mulsu ( IMUvelocityz._.W1 , 37877 ) ;
	ground_speed2_ += __builtin_mulss ( accum._.W1 , accum._.W1 ) ;

	groundspeed 	= sqrt_long(ground_speed2_);
	groundspeed2 	= ground_speed2_;

//	groundspeedDelta = (groundspeedDelta >> 1) + ((groundspeed- lastGroundspeed) >> 1);
}

void calc_target_airspeed(void)
{
	target_airspeed = desiredSpeed * 10;

	if(groundspeed < minimum_groundspeed)
		target_airspeed += (minimum_groundspeed - groundspeed);
	
	// WARNING: UNTESTED
	if(target_speed_as_groundspeed == 1)
	{
		if(groundspeed < desiredSpeed)
			target_airspeed += (desiredSpeed - groundspeed);
	}

	// 	TODO: Check for maximum target airspeed rate change here
//	if(previous_target_airspeed

	if(target_airspeed > maximum_airspeed)
		target_airspeed = maximum_airspeed;

	if(target_airspeed < minimum_airspeed)
		target_airspeed = minimum_airspeed;

	//Some airspeed error filtering
	airspeedError = airspeedError >>=1;
	airspeedError += (target_airspeed - airspeed) >>1;

}
