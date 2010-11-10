// SEE END OF FILE FOR LICENSE TERMS

#include "../libUDB/libUDB.h"

#ifndef TELEMETRY_MANAGER_H
#define TELEMETRY_MANAGER_H

// A collection of all elements required for telemetry

typedef struct tagTELEMETRY_DATA
{
	unsigned int	byteSize;		// Size of the data
	unsigned int	identifier;		// Data identifier
	unsigned int	arrayOffset;	// Data array offset
	unsigned char*	pData;			// Pointer to the data or buffer
} TELEMETRY_DATA;


typedef struct tagTELEMETRY_LIST_ENTRY
{
	unsigned int 	identifier;		// Data identifier
	unsigned int 	arrayOffset;	// offset into the data array
} TELEMETRY_LIST_ENTRY;

#define TELEMETRY_LIST_COUNT 3

// An list of pointers to ID_NULL terminated list of identifiers to send for telemetry
extern const TELEMETRY_LIST_ENTRY* ptelemetryLists[TELEMETRY_LIST_COUNT];

// A const list of request cycles requried to trigger each of the telemetry queues
extern const unsigned int telemetryAutoRequestCycles[TELEMETRY_LIST_COUNT];

// Intitalise telemetry manager
void initTelemetryManager(void);

// Increment counters for automatic telemetry requests and check if any are due.
//  If a telemetry request is due, set the request flag and reset the counter.
//   Return true if one of the requests is flagged.
boolean requestAutoTelemetrySend(void);

// Set a flag requesting that the given telemetry queue be started
extern void requestTelemetrySend(unsigned char queueNo);

// Get the next telemetry data to send
// return true if data is filled, return false if no remaing data to send
boolean get_next_telemetry_data(TELEMETRY_DATA* pteleData);

// Parse incoming telemtry data
// Return true if parsed ok. Return false if not ok
boolean parse_telemetry_data(const TELEMETRY_DATA* pteleData);

// Process a event send with data identifier ID_EVENT
extern void processEvent(TELEMETRY_DATA* pteleData);

// Get the data pointer to a variable from its identifier and array offset
// The array offset acts as a index into array variables
unsigned char* get_variable_from_identifier(unsigned int identifier, unsigned int arrayOffset, unsigned int* pbyteSize);

// Same as get_variable_from_identifier but for variables specific to node
unsigned char* get_node_variable_from_identifier(unsigned int identifier, unsigned int arrayOffset, unsigned int* pbyteSize);

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
