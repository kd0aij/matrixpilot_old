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


#include "../libDCM/libDCM_internal.h"

#if ( GPS_TYPE == GPS_STD )
#define GPS_TAU 1.25

#elif ( GPS_TYPE == GPS_UBX_2HZ )
#define GPS_TAU 1.25

#elif ( GPS_TYPE == GPS_UBX_4HZ )
#define GPS_TAU 1.25

#else
#define GPS_TAU 1.25
#endif

#define DR_PERIOD (int)(40/GPS_RATE)

#define TIMESTEP 0.025
#define MAX16 (4.0*RMAX)

#define ACCEL2DELTAV ((TIMESTEP*GRAVITYM*MAX16)/GRAVITY)
#define VELOCITY2LOCATION (TIMESTEP*.01*MAX16*16.0)
//	The factor of 16 is so that the gain is more precise.
//	There is a subsequent right shift by 4 to cancel the multiply by 16.

#define GPS_FILTER_GAIN (int) (TIMESTEP*MAX16/GPS_TAU)
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
union longww filteredIMUvelocityx =  { 0 }  ;
union longww filteredIMUvelocityy =  { 0 }  ;
union longww filteredIMUvelocityz =  { 0 }  ;

//      filtered IMU location
//		This mimics the dynamics of the GPS
union longww filteredIMUlocationx =  { 0 }  ;
union longww filteredIMUlocationy =  { 0 }  ;
union longww filteredIMUlocationz =  { 0 }  ;

//	GPSlocation - IMUlocation
fractional locationErrorEarth[] = { 0 , 0 , 0 } ;
//	GPSvelocity - IMUvelocity
fractional velocityErrorEarth[] = { 0 , 0 , 0 } ;

void dead_reckon(void)
{
}


