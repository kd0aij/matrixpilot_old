#include "libUDB_internal.h"
#include "CANInterfaceOptions.h"

#ifndef CAN_INTERFACE_DEFINES_H
#define CAN_INTERFACE_DEFINES_H


typedef enum
{
	OS_PASSTHROUGH 	= 1,
	OS_RX_OK	 	= 2,
	OS_CTRL_COMM_OK	= 4
}OP_STATES;


typedef struct
{
	unsigned passthrough 	:1;		// In passthrough mode
	unsigned mode_ok		:1;		// Mode connected ok
	unsigned failsafe_ok	:1;		// Failsafe connected ok
	unsigned rx_ok			:1;		// Receiver connected ok
	unsigned cntrl_comm_ok	:1;		// Control communication ok (servo control)
	unsigned frame_ok		:1;		// Complete servo frame received ok
	unsigned 				:11;	// Not defined yet
} OP_STATE;

extern OP_STATE op_status;

void init_cntrl_comms(void);
void init_canbus_comms(void);

void init_heartbeat(void);

//void init_states(void);

extern unsigned int uiServosFound;	// Record of which servos have been found
extern boolean		frameComplete;	// Flag for frame complete

void send_radio_data(void);			// Interface send data to autopilot
void receive_servo_data(void);		// Interface receive data from autopilot

void send_servo_outputs(void);		// Autopilot send servo data to interface
void receive_servo_inputs(void);	// Autopilot recieve servo data from interface

// Servo data buffers for interface
extern unsigned int ServoOutDataBuff[8];
extern unsigned int ServoInDataBuff[8];

extern unsigned int RxTimeouts;

int pulsesat(long) ;

extern unsigned int rise[MAX_INPUTS+1] ;	// rising edge clock capture for radio inputs

extern int pwIn[MAX_INPUTS+1] ;	// pulse widths of radio inputs
extern int pwOut[MAX_OUTPUTS+1] ;	// pulse widths for servo outputs


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
