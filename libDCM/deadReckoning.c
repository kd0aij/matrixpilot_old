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


#include "libDCM_internal.h"

#define DR_PERIOD (int)((40/GPS_RATE)+4 )

#define TIMESTEP 0.025
#define MAX16 (4.0*RMAX)

#define ACCEL2DELTAV ((TIMESTEP*GRAVITYM*MAX16)/GRAVITY)
#define VELOCITY2LOCATION (TIMESTEP*.01*MAX16*16.0)
//	The factor of 16 is so that the gain is more precise.
//	There is a subsequent right shift by 4 to cancel the multiply by 16.

#define DR_FILTER_GAIN (int) (TIMESTEP*MAX16)

extern fractional accelEarth[] ;

int dead_reckon_clock = DR_PERIOD ;

//      velocity, as estimated by the IMU
union longww IMUvelocityx =  { 0 }  ;
union longww IMUvelocityy =  { 0 }  ;
union longww IMUvelocityz =  { 0 }  ;

//      location, as estimated by the IMU
union longww IMUlocationx =  { 0 }  ;
union longww IMUlocationy =  { 0 }  ;
union longww IMUlocationz =  { 0 }  ;

//      filtered IMU velocity
//		This mimics the dynamics of the GPS
//union longww filteredIMUvelocityx =  { 0 }  ;
//union longww filteredIMUvelocityy =  { 0 }  ;
//union longww filteredIMUvelocityz =  { 0 }  ;

//      filtered IMU location
//		This mimics the dynamics of the GPS
//union longww filteredIMUlocationx =  { 0 }  ;
//union longww filteredIMUlocationy =  { 0 }  ;
//union longww filteredIMUlocationz =  { 0 }  ;

//	GPSlocation - IMUlocation
fractional locationErrorEarth[] = { 0 , 0 , 0 } ;
//	GPSvelocity - IMUvelocity
fractional velocityErrorEarth[] = { 0 , 0 , 0 } ;

extern int errorYawground[] ;

void dead_reckon(void)
{
	if ( dcm_flags._.dead_reckon_enable == 1 )  // wait for startup of GPS
	{
		//	integrate the accelerometers to update IMU velocity
		IMUvelocityx.WW += __builtin_mulss( ((int)(ACCEL2DELTAV)) ,  accelEarth[0] ) ;
		IMUvelocityy.WW += __builtin_mulss( ((int)(ACCEL2DELTAV)) ,  accelEarth[1] ) ;
		IMUvelocityz.WW += __builtin_mulss( ((int)(ACCEL2DELTAV)) ,  accelEarth[2] ) ;

		//	integrate IMU velocity to update the IMU location	
		IMUlocationx.WW += ( __builtin_mulss( ((int)(VELOCITY2LOCATION)) ,  IMUvelocityx._.W1 )>>4 ) ;
		IMUlocationy.WW += ( __builtin_mulss( ((int)(VELOCITY2LOCATION)) ,  IMUvelocityy._.W1 )>>4 ) ;
		IMUlocationz.WW += ( __builtin_mulss( ((int)(VELOCITY2LOCATION)) ,  IMUvelocityz._.W1 )>>4 ) ;

		if ( dead_reckon_clock > 0 )
		//	apply drift adjustments only while valid GPS data is in force.
		//  This is done with a countdown clock that gets reset each time new data comes in.
		{
			dead_reckon_clock -- ;

			IMUvelocityx.WW += __builtin_mulss( DR_FILTER_GAIN ,  velocityErrorEarth[0] ) ;
			IMUvelocityy.WW += __builtin_mulss( DR_FILTER_GAIN ,  velocityErrorEarth[1] ) ;
			IMUvelocityz.WW += __builtin_mulss( DR_FILTER_GAIN ,  velocityErrorEarth[2] ) ;
	
			IMUlocationx.WW += __builtin_mulss( DR_FILTER_GAIN ,  locationErrorEarth[0] ) ;
			IMUlocationy.WW += __builtin_mulss( DR_FILTER_GAIN ,  locationErrorEarth[1] ) ;
			IMUlocationz.WW += __builtin_mulss( DR_FILTER_GAIN ,  locationErrorEarth[2] ) ;
		}
		else
		{
			errorYawground[0] = errorYawground[1] = errorYawground[2] = 0 ;
		}
	
		if ( gps_nav_valid() && ( dcm_flags._.reckon_req == 1 ) )
		{
			//	compute error indications and restart the dead reckoning clock to apply them
			dcm_flags._.reckon_req = 0 ;
			dead_reckon_clock = DR_PERIOD ;
			locationErrorEarth[0] = GPSlocation.x - IMUlocationx._.W1 ;
			locationErrorEarth[1] = GPSlocation.y - IMUlocationy._.W1 ;
			locationErrorEarth[2] = GPSlocation.z - IMUlocationz._.W1 ;
			velocityErrorEarth[0] = GPSvelocity.x - IMUvelocityx._.W1 ;
			velocityErrorEarth[1] = GPSvelocity.y - IMUvelocityy._.W1 ;
			velocityErrorEarth[2] = GPSvelocity.z - IMUvelocityz._.W1 ;
		}
	}
	else
	{
		IMUvelocityx.WW = 0 ;
		IMUvelocityy.WW = 0 ;
		IMUvelocityz.WW = 0 ;
	
		IMUlocationx.WW = 0 ;
		IMUlocationy.WW = 0 ;
		IMUlocationz.WW = 0 ;
	}
	return ;
}


