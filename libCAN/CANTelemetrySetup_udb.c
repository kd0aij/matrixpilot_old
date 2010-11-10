// SEE END OF FILE FOR LICENSE TERMS

#include "CANTelemetryManager.h"
#include "CANDataIDRefs.h"


const TELEMETRY_LIST_ENTRY DCMRateList[] = 
	{
			{ID_RADIO_INPUTS, 1},
			{ID_RADIO_INPUTS, 5},
			{ID_SERVO_OUTPUTS,1},
			{ID_SERVO_OUTPUTS,5},
			{ID_RMAT,0},
			{ID_RMAT,3},
			{ID_RMAT,6},
			{ID_IMU_LOCATIONX,0},
			{ID_IMU_LOCATIONY,0},
			{ID_IMU_LOCATIONZ,0},
			{ID_IMU_VELOCITYX,0},
			{ID_IMU_VELOCITYY,0},
			{ID_IMU_VELOCITYZ,0},

			{ID_EVENT,ID_AUTOPILOT_DCM_TELEMETRY_COMPLETE},
			{ID_NULL, 0}
	};

const TELEMETRY_LIST_ENTRY NavRateList[] = 
	{
			{ID_GPS_LOCATION,0},
			{ID_LOC_ERROR_EARTH,0},
			{ID_ESTIMATED_WIND,0},

			{ID_GPS_TOW,0},
			{ID_GPS_VARS,0},	// MODE1,MODE2,SVS,NAV_VALID
			{ID_GPS_VARS2,0},	// SOG, COG, CLIMB_GPS, WEEK_NO

			{ID_FLAGS,0},
			{ID_UDB_FLAGS,0},
			{ID_DCM_FLAGS,0},
			{ID_DESIRED_BEHAVOIR,0},
			{ID_ORIENTATION,0},

			{ID_MAG_FIELD_EARTH,0},
			{ID_AIRSPEED_MAG,0},
			{ID_EVENT,ID_AUTOPILOT_NAV_TELEMETRY_COMPLETE},
			{ID_NULL, 0}
	};

const TELEMETRY_LIST_ENTRY BackgroundRateList[] = 
	{
			{ID_ORIGIN_LAT, 0},
			{ID_ORIGIN_LONG, 0},
			{ID_ORIGIN_ALT, 0},
			{ID_EVENT,ID_AUTOPILOT_BACKGROUND_TELEMETRY_COMPLETE},
			{ID_NULL, 0}
	};

const TELEMETRY_LIST_ENTRY* ptelemetryLists[TELEMETRY_LIST_COUNT] = 
	{
			&DCMRateList[0],
			&NavRateList[0],
			&BackgroundRateList[0]
	};



// A list of the number of cycles requried to trigger a telemetry send
// One value is required per entry in the telemetry list
const unsigned int telemetryAutoRequestCycles[TELEMETRY_LIST_COUNT] = 
	{
		1,
		5,
		40
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
