// SEE END OF FILE FOR LICENSE TERMS

#include "../libDCM/libDCM.h"
#include "../libDCM/libDCM_internal.h"
#include "../MatrixPilot/defines.h"
#include "../libUDB/libUDB_internal.h"

#include "CANTelemetryManager.h"
#include "CANDataIDrefs.h"

// temporary place to put the interface clock variable
unsigned int interfaceClock;


// Get the data pointer to a variable from its identifier and array offset
// The array offset acts as a index into array variables
unsigned char* get_node_variable_from_identifier(unsigned int identifier, unsigned int arrayOffset, unsigned int* pbyteSize)
{
	unsigned char* 	pData;

	switch(identifier)
	{

	case ID_CLOCK_TICK:
		pData = (unsigned char*) &interfaceClock;
		*pbyteSize = 0;	
		break;
	default:
		pData = 0;
		*pbyteSize = 0;
		break;
	}

	return pData;
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
