// SEE END OF FILE FOR LICENSE TERMS

typedef	enum	
{		
	ID_NULL	 = 0,
	ID_EVENT,

	ID_CLOCK_TICK,

	ID_FLAGS,
	ID_UDB_FLAGS,
	ID_DCM_FLAGS,

	ID_DESIRED_BEHAVOIR,
	ID_ORIENTATION,

	ID_RADIO_INPUTS,
	ID_SERVO_OUTPUTS,
	ID_SERVO_TRIMS,

	ID_RMAT,
	ID_OMEGA,
	ID_OMEGA_GYRO,
	ID_OMEGA_ACCUM,

	ID_GPS_LOCATION,
	ID_GPS_VELOCITY,
	ID_VELOCITY_THRU_AIR,
	ID_ESTIMATED_WIND,

	ID_IMU_LOCATIONX,
	ID_IMU_LOCATIONY,
	ID_IMU_LOCATIONZ,

	ID_IMU_VELOCITYX,
	ID_IMU_VELOCITYY,
	ID_IMU_VELOCITYZ,

	ID_HEADING_CALC,
	ID_GPS_DATA_AGE,
	ID_VELOCITY_MAG,
	ID_AIRSPEED_MAG,

	ID_GPS_LAT,
	ID_GPS_LONG,
	ID_GPS_ALT,

	ID_ORIGIN_LAT,
	ID_ORIGIN_LONG,
	ID_ORIGIN_ALT,

	ID_ACTUAL_DIR,
	ID_VELOCITY_PREVIOUS,

	ID_GPS_DIR_OVER_GND,
	ID_RMAT_DIR_OVER_GND,

	ID_ACCELERATION,

	ID_MAG_FIELD_EARTH,
	ID_LOC_ERROR_EARTH,
	
	ID_GPS_TOW,
	ID_GPS_VARS,
	ID_GPS_VARS2,
	ID_GPS_HDOP,

	ID_GPS_XPG,
	ID_GPS_YPG,
	ID_GPS_ZPG,

	ID_GPS_XVG,
	ID_GPS_YVG,
	ID_GPS_ZVG,

	ID_GPS_MODES,
		
} DATA_ID_REFS;		


typedef	enum	
{
	ID_EVENT_NULL = 0,
	ID_AUTOPILOT_DCM_TELEMETRY_COMPLETE,
	ID_AUTOPILOT_NAV_TELEMETRY_COMPLETE,
} EVENT_ID_REFS;


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
