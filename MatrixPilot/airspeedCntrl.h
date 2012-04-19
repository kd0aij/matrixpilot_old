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
extern long 	airspeed2;
extern int 		groundspeed;
extern long 	groundspeed2;
extern int 		target_airspeed;
extern int 		airspeedError;
extern int		airspeedDelta;		// Filtered change in airspeed over period ASPD_BUFF_SIZE
extern int		groundspeedDelta;
extern int		airspeedFadeout;	// Gain for fadeout of controls with airspeed

extern int 		lastAirspeed;
extern int 		lastGroundspeed;

extern int minimum_groundspeed;
extern int minimum_airspeed;
extern int maximum_airspeed;
extern int airspeed_adj_range;

extern fractional airspeed_pitch_kp;
extern fractional airspeed_pitch_kd;
extern fractional groundspeed_pitch_kd;

void calc_airspeed(void);
void calc_groundspeed(void);
void calc_target_airspeed(void);
void calc_airspeed_gain(void);

#endif

