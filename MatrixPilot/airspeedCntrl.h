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

#ifndef AIRSPEEDCNTRL_H
#define AIRSPEEDCNTRL_H

#include "airspeed_options.h"

extern int 		airspeed;
extern int 		groundspeed;

extern int 		minimum_airspeed;
extern int 		maximum_airspeed;
extern int 		target_airspeed;
extern int 		cruise_airspeed;
extern int 		airspeedError;

// Integral of airspeed error
// lower word is underflow.  Upper word is output in degrees of pitch adjustment.
extern union longww airspeed_error_integral;

// Feedforward values of pitch 
extern int 		airspeed_pitch_min_aspd;
extern int 		airspeed_pitch_max_aspd;

// Run all airspeed control calculations and filters
extern void airspeedCntrl(void);

// Calculate the airspeed.
extern int calc_airspeed(void);

// Calculate the groundspeed.
extern int calc_groundspeed(void);

// Calculate the target airspeed in cm/s from desiredSpd in dm/s
extern int calc_target_airspeed(int desiredSpd);

// Calculate the airspeed error vs target airspeed including filtering
extern int calc_airspeed_error(void);

// Calculate the airspeed error integral term with filtering and limits
extern long calc_airspeed_int_error(int aspdError, long aspd_integral);

//Calculate and return pitch target adjustment for target airspeed
// return value is in dcm scale angle 
extern fractional gliding_airspeed_pitch_adjust(void);

#endif

