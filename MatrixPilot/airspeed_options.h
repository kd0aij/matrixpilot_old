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


#ifndef AIRSPEED_OPTIONS_H
#define AIRSPEED_OPTIONS_H

// Airspeeds in m/s
#define MINIMUM_GROUNDSPEED 	3.0
#define MINIMUM_AIRSPEED		7.0
#define MAXIMUM_AIRSPEED		20.0
#define CRUISE_AIRSPEED			12.0

// Airspeed to pitch proportional and differential control terms
#define AIRSPEED_PITCH_KP		0.0
#define AIRSPEED_PITCH_KD		0.0

// Pitch feedforward for airspeed
// linnearly interpolated from cruise airspeed to min and max airspeed
#define AIRSPEED_PITCH_MIN_ASPD		2.5
#define AIRSPEED_PITCH_MAX_ASPD		-10.0

// Fraction of actual airspeed across which linear control is made.
#define AIRSPEED_ADJ_RANGE		0.2

// Maximum airspeed delta/sec for linear response
//#define AIRSPEED_ACCEL_MAX		500

// Always fly at groundspeed, not airspeed
#define TARGET_SPEED_AS_GROUNDSPEED		0

// Maximum rate of target airspeed change in cm/s
#define MAXIMUM_TARGET_AIRSPEED_RATE 	1000

// The maximum airspeed above which the throttle can be used
// Above this airspeed the throttle is reduced to zero
// Set to the maximum pitch speed of your engine/propeller combination
#define MAXIMUM_AIRSPEED_ON_THROTTLE 2500

// Number of frame cycles over which the delta airspeed is measured.
#define ASPD_BUFF_SIZE 20

#endif

