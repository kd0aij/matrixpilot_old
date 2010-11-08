#include "../libDCM/libDCM.h"
#include "../libDCM/libDCM_internal.h"
#include "../MatrixPilot/defines.h"
#include "../libUDB/libUDB_internal.h"

#include "CANTelemetryManager.h"
#include "CANDataIDrefs.h"

// A buffer for variables aquired by functions.
// THIS ONLY WORKS FOR:
//  single canbus and dual canbus atthe same interrupt priority
unsigned char tempBuffer[8];

// temporary place to put the interface clock variable
unsigned int interfaceClock;


unsigned char* get_variable_from_identifier(unsigned int identifier, unsigned int arrayOffset, unsigned int* pbyteSize)
{
	unsigned char* 	pData;
	unsigned int 	tempint;

	switch(identifier)
	{
	case ID_NULL:
		pData = 0;
		*pbyteSize = 0;
		break;
	case ID_EVENT:
		pData = 0;
		*pbyteSize = 0;
		break;

#if(BOARD_TYPE == CAN_INTERFACE)
	case ID_CLOCK_TICK:
		tempint = getHeartbeatTick();
		memcpy(tempBuffer, &tempint, sizeof(tempint));
		pData = &tempBuffer;
		*pbyteSize = sizeof(tempint);
		break;
#else
	case ID_CLOCK_TICK:
		pData = &interfaceClock;
		*pbyteSize = 0;	
		break;
#endif

	case ID_FLAGS:
		pData = &flags;
		*pbyteSize = sizeof(flags);
		break;
	case ID_UDB_FLAGS:
		pData = &udb_flags;
		*pbyteSize = sizeof(udb_flags);
		break;
	case ID_DCM_FLAGS:
		pData = &dcm_flags;
		*pbyteSize = sizeof(dcm_flags);
		break;
	case ID_DESIRED_BEHAVOIR:
		pData = &desired_behavior;
		*pbyteSize = 2;
		break;
	case ID_ORIENTATION:
		pData = &current_orientation;
		*pbyteSize = 2;
		break;

	case ID_RADIO_INPUTS:
		pData = (unsigned char*) &udb_pwIn[arrayOffset];
		*pbyteSize = 8;
		break;
	case ID_SERVO_OUTPUTS:
		pData = (unsigned char*) &udb_pwOut[arrayOffset];
		*pbyteSize = 8;
		break;
	case ID_SERVO_TRIMS:
		pData = (unsigned char*) &udb_pwTrim[arrayOffset];
		*pbyteSize = 8;
		break;

	case ID_RMAT:
		pData = (unsigned char*) &rmat[arrayOffset];
		*pbyteSize = 6;
		break;
	case ID_OMEGA:
		pData = (unsigned char*) &omega;
		*pbyteSize = 6;
		break;
	case ID_OMEGA_GYRO:
		pData = (unsigned char*) &omegagyro;
		*pbyteSize = 6;
		break;
	case ID_OMEGA_ACCUM:
		pData = (unsigned char*) &omegaAccum;
		*pbyteSize = 6;
		break;

	case ID_GPS_LOCATION:
		pData = (unsigned char*) &GPSlocation;
		*pbyteSize = 6;
		break;
	case ID_GPS_VELOCITY:
		pData = (unsigned char*) &GPSvelocity;
		*pbyteSize = 6;
		break;
	case ID_VELOCITY_THRU_AIR:
		pData = (unsigned char*) &velocity_thru_air;
		*pbyteSize = 6;
		break;
	case ID_ESTIMATED_WIND:
		pData = (unsigned char*) &estimatedWind;
		*pbyteSize = 6;
		break;

	case ID_IMU_LOCATIONX:
		pData = (unsigned char*) &IMUlocationx;
		*pbyteSize = 4;
		break;
	case ID_IMU_LOCATIONY:
		pData = (unsigned char*) &IMUlocationy;
		*pbyteSize = 4;
		break;
	case ID_IMU_LOCATIONZ:
		pData = (unsigned char*) &IMUlocationz;
		*pbyteSize = 4;
		break;

	case ID_IMU_VELOCITYX:
		pData = (unsigned char*) &IMUvelocityx;
		*pbyteSize = 4;
		break;
	case ID_IMU_VELOCITYY:
		pData = (unsigned char*) &IMUvelocityy;
		*pbyteSize = 4;
		break;
	case ID_IMU_VELOCITYZ:
		pData = (unsigned char*) &IMUvelocityz;
		*pbyteSize = 4;
		break;

//	case ID_ACTUAL_DIR:	OBSOLETE
//		pData = (unsigned char*) &actual_dir;
//		*pbyteSize = 1;
		break;	
	case ID_VELOCITY_PREVIOUS:
		pData = (unsigned char*) &velocity_previous;
		*pbyteSize = 2;
		break;

	case ID_GPS_DIR_OVER_GND:
		pData = (unsigned char*) &dirovergndHGPS;
		*pbyteSize = 6;
		break;
	case ID_RMAT_DIR_OVER_GND:
		pData = (unsigned char*) &dirovergndHRmat;
		*pbyteSize = 6;
		break;

	case ID_MAG_FIELD_EARTH:
		pData = (unsigned char*) &magFieldEarth;
		*pbyteSize = sizeof(magFieldEarth);
		break;
	case ID_LOC_ERROR_EARTH:
		pData = (unsigned char*) &locationErrorEarth;
		*pbyteSize = sizeof(locationErrorEarth);
		break;

	case ID_ACCELERATION:
		pData = (unsigned char*) &forward_acceleration;
		*pbyteSize = 2;
		break;


	case ID_GPS_TOW:
		pData = (unsigned char*) &tow;
		*pbyteSize = 4;
		break;
	case ID_GPS_VARS:
		pData = (unsigned char*) &sog_gps;
		*pbyteSize = 8;
		break;
	case ID_GPS_VARS2:
		pData = (unsigned char*) &mode1;
		*pbyteSize = 4;
		break;

	case ID_GPS_HDOP:
		pData = (unsigned char*) &hdop;
		*pbyteSize = 1;
		break;

	case ID_GPS_XPG:
		pData = (unsigned char*) &xpg;
		*pbyteSize = 4;
		break;
	case ID_GPS_YPG:
		pData = (unsigned char*) &ypg;
		*pbyteSize = 4;
		break;
	case ID_GPS_ZPG:
		pData = (unsigned char*) &zpg;
		*pbyteSize = 4;
		break;

	case ID_GPS_XVG:
		pData = (unsigned char*) &xvg;
		*pbyteSize = 4;
		break;
	case ID_GPS_YVG:
		pData = (unsigned char*) &yvg;
		*pbyteSize = 4;
		break;
	case ID_GPS_ZVG:
		pData = (unsigned char*) &zvg;
		*pbyteSize = 4;
		break;

	case ID_GPS_MODES:
		pData = (unsigned char*) &mode1;
		*pbyteSize = 4;
		break;

	case ID_HEADING_CALC:
		pData = (unsigned char*) &calculated_heading;
		*pbyteSize = 1;
		break;
	case ID_GPS_DATA_AGE:
		pData = (unsigned char*) &gps_data_age;
		*pbyteSize = 2;
		break;
	case ID_VELOCITY_MAG:
		pData = (unsigned char*) &velocity_magnitude;
		*pbyteSize = 2;
		break;
	case ID_AIRSPEED_MAG:
		pData = (unsigned char*) &air_speed_magnitude;
		*pbyteSize = 2;
		break;

	case ID_GPS_LAT:
		pData = (unsigned char*) &lat_gps;
		*pbyteSize = 4;
		break;
	case ID_GPS_LONG:
		pData = (unsigned char*) &long_gps;
		*pbyteSize = 4;
		break;
	case ID_GPS_ALT:
		pData = (unsigned char*) &alt_sl_gps;
		*pbyteSize = 4;
		break;

	case ID_ORIGIN_LAT:
		pData = (unsigned char*) &lat_origin ;
		*pbyteSize = 4;
		break;
	case ID_ORIGIN_LONG:
		pData = (unsigned char*) &long_origin;
		*pbyteSize = 4;
		break;
	case ID_ORIGIN_ALT:
		pData = (unsigned char*) &alt_origin;
		*pbyteSize = 4;
		break;

	default:
		pData = 0;
		*pbyteSize = 0;
		break;
	}

	return pData;
}
