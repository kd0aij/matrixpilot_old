// SEE END OF FILE FOR LICENSE TERMS


#include "../libUDB/libUDB.h"
#include "CANInterface_defines.h"
#include "heartbeat.h"
#include "../MatrixPilot/defines.h"


OP_STATE 	op_status	= {0,0,0,0,0,0};
OP_CONTROL	op_control  = {0};

unsigned char hstatesTimer;
// State functions
void state_start(void);

// Pointer to function for next state
void (* stateFunc ) ( void ) = &state_start;

// Callback function for events triggering the next state
void states_callback(void);

// Start a timer to callback every 500ms
void init_interface_states(void)
{
	stateFunc = &state_start;
//	hstatesTimer = register_timer(register_event(&states_callback));
//	set_timer(hstatesTimer, 500, true);
}

void states_callback(void)
{
	stateFunc();
}


// Wait for the reciever to be valid
void state_start(void)
{

}



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
