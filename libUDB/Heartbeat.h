// See end of file for license

#include "libUDB.h"
#include "events.h"

#ifndef HEARTBEAT_H
#define HEARTBEAT_H

// Make this inline
unsigned int getHeartbeatTick(void);

// Callback to the radio input with the current clock tick
extern void radio_heartbeat_callback(unsigned int tick);

typedef struct tagTIMER
{
	unsigned int 	hEvent;		// a handle to the event triggered by timer
	unsigned int 	timeout;	// When the timer ends
	unsigned int	repeat;		// Timer repeat period
	boolean			active;		// Timer is active
} TIMER;

unsigned int register_timer(unsigned int hEvent);

// Setup a timer and activate it
void set_timer(unsigned int hTimer, unsigned int period, boolean repeat );

#endif

/****************************************************************************/
// This is part of the servo and radio interface software
//
// ServoInterface source code
//	http://code.google.com/p/rc-servo-interface
//
// Copyright 2010 ServoInterface Team
// See the AUTHORS.TXT file for a list of authors of ServoInterface.
//
// ServoInterface is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ServoInterface is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with ServoInterface.  If not, see <http://www.gnu.org/licenses/>.
//
// Many parts of ServoInterface use either modified or unmodified code
// from the MatrixPilot pilot project.
// The project also contains code for modifying MatrixPilot to operate
// with ServoInterface.
// For details, credits and licenses of MatrixPilot see the AUTHORS.TXT file.
// or see this website: http://code.google.com/p/gentlenav
/****************************************************************************/
