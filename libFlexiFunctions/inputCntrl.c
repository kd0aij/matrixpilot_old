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

// Responsible for turning tranmitter input values into RMAX scaled values
// with corrected direction.  It is done here so that nowhere else has to do it.

#include "inputCntrl.h"

// RMAX scaled inputs
fractional pitch_input_control		= 0;
fractional roll_input_control		= 0;
fractional yaw_input_control		= 0;
fractional throttle_input_control	= 0;

// Turn PWM into fraction subtracting the offset
fractional PWM_to_frac(int PWM, int offset, boolean reversed)
{
	union longww temp;
	temp.WW = ( (RMAX * 256.0) / ( MIX_PWM_RANGE ) );
	temp.WW = __builtin_mulss( PWM - offset, temp._.W0);  //
	temp.WW >>= 8;
	return (fractional) temp._.W0;
};

// turn PWM inputs into RMAX scaled values with corrected reversing
// Check if radio is on, set to zero if not.
void input_controls( void )
{
	// Scale throttle to 0 to MIX_PWM_RANGE instead of 0 to 2 * MIX_PWM_RANGE
	// This stops the fractional overflowing 2*RMAX
	int tempThrottle = udb_pwIn[THROTTLE_INPUT_CHANNEL] - udb_pwTrim[THROTTLE_INPUT_CHANNEL];
	tempThrottle = tempThrottle >> 1;

	if (udb_flags._.radio_on)
	{
		yaw_input_control = PWM_to_frac(udb_pwIn[RUDDER_INPUT_CHANNEL], udb_pwTrim[RUDDER_INPUT_CHANNEL], RUDDER_CHANNEL_REVERSED);
		roll_input_control = PWM_to_frac(udb_pwIn[AILERON_INPUT_CHANNEL], udb_pwTrim[AILERON_INPUT_CHANNEL], AILERON_CHANNEL_REVERSED);
		pitch_input_control = PWM_to_frac(udb_pwIn[PITCH_INPUT_CHANNEL], udb_pwTrim[PITCH_INPUT_CHANNEL], ELEVATOR_CHANNEL_REVERSED);
		throttle_input_control = PWM_to_frac(tempThrottle, 0, THROTTLE_CHANNEL_REVERSED);
	}
	else
	{
		yaw_input_control = 0;
		roll_input_control = 0;
		pitch_input_control = 0;
		throttle_input_control = 0;
	}
}

