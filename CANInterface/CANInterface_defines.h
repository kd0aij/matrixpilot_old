// SEE END OF FILE FOR LICENSE TERMS

#include "../CANInterface/CANInterfaceOptions.h"
#include "../libUDB/libUDB.h"

#ifndef CAN_INTERFACE_DEFINES_H
#define CAN_INTERFACE_DEFINES_H


typedef struct
{
	unsigned int passthrough 	:1;		// In passthrough mode
	unsigned int failsafe_rx	:1;		// Failsafe received in frame flag.
	unsigned int failsafe_ok	:1;		// Failsafe connected ok
	unsigned int frame_ok		:1;		// Complete servo frame received ok
	unsigned int cntrl_comm_ok	:1;		// Control communication ok (servo control)
	unsigned 					:11;	// Not defined yet
} OP_STATE;

typedef struct
{
	unsigned pwm_active		:1;		// In passthrough mode
	unsigned 				:11;	// Not defined yet
} OP_CONTROL;

extern OP_STATE 	op_status;
extern OP_CONTROL 	op_control;

// Servo data buffers for interface
extern unsigned int RxTimeouts;

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
