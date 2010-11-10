// SEE END OF FILE FOR LICENSE TERMS

#include "CANTelemetryManager.h"
#include "CANDataIDRefs.h"

// A list of the number of cycles requried to trigger a telemetry send
// One value is required per entry in the telemetry list
const unsigned int telemetryAutoRequestCycles[TELEMETRY_LIST_COUNT] = 
	{
		1,
		5,
		40
	};


const TELEMETRY_LIST_ENTRY DCMRateList[] = 
	{
			{ID_CLOCK_TICK, 1},
			{ID_NULL, 0}
	};

const TELEMETRY_LIST_ENTRY NavRateList[] = 
	{
			{ID_NULL, 0}
	};

const TELEMETRY_LIST_ENTRY BackgroundRateList[] = 
	{
			{ID_NULL, 0}
	};

const TELEMETRY_LIST_ENTRY* ptelemetryLists[TELEMETRY_LIST_COUNT] = 
	{
			&DCMRateList[0],
			&NavRateList[0],
			&BackgroundRateList[0]
	};


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
