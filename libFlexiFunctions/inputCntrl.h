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

#ifndef INPUTCNTRL_H
#define INPUTCNTRL_H

#include "defines.h"

// Fix this to your particular radio at 100% travel
#define MIX_PWM_RANGE 800

// RMAX scaled inputs
extern fractional pitch_input_control;
extern fractional roll_input_control;
extern fractional yaw_input_control;
extern fractional throttle_input_control;

// Turn PWM into fraction subtracting the offset
fractional PWM_to_frac(int PWM, int offset, boolean reversed);

// turn PWM inputs into RMAX scaled values with corrected reversing
void input_controls(void);

#endif

