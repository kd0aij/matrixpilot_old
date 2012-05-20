// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


//#include "libDCM_internal.h"
#include "libDCM.h"
#include "gpsParseCommon.h"
#include "mathlibNAV.h"
#include "../libUDB/magnetometer.h"
#include "../libUDB/barometer.h"
#include "estAltitude.h"
#include "estYawDrift.h"
#include "HILSIM.h"
#include "rmat.h"


union dcm_fbts_word dcm_flags ;

// Calibrate for 10 seconds before moving servos
#define CALIB_COUNT		  400		// 10 seconds at 40 Hz
#define GPS_COUNT		 1000		// 25 seconds at 40 Hz


void dcm_init( void )
{
	dcm_flags.W = 0 ;
	dcm_flags._.first_mag_reading = 1 ;
	
	dcm_init_rmat() ;
	
	return ;
}


void dcm_run_init_step( void )
{
	if (udb_heartbeat_counter == CALIB_COUNT)
	{
		// Finish calibration
		dcm_flags._.calib_finished = 1 ;
		dcm_calibrate() ;
	}
	
	if (udb_heartbeat_counter <= GPS_COUNT)
	{
		gps_startup_sequence( GPS_COUNT-udb_heartbeat_counter ) ; // Counts down from GPS_COUNT to 0
		
		if (udb_heartbeat_counter == GPS_COUNT)
		{
			dcm_flags._.init_finished = 1 ;
		}
	}
	
	return ;
}


void read_sensors(void)
{
	read_gyros() ; // record the average values for both DCM and for offset measurements
	read_accel() ;
	udb_read_gyro_accel_restart();
	
	return ;
}

void do_I2C_stuff(void) // currently called at 40Hz
{
	static int toggle = 0;
	static int counter = 0;

	if (toggle) {
		if (counter++ > 0) {
#if (MAG_YAW_DRIFT == 1)
			rxMagnetometer(udb_magnetometer_callback);
#endif
			counter = 0;
			toggle = 0;
		}
	} else {
#if (BAROMETER_ALTITUDE == 1)
		rxBarometer(udb_barometer_callback);
#endif
		if (counter++ > 6) {
			counter = 0;
			toggle = 1;
		}
	}
}

void udb_callback_40hertz(void)
{
	read_sensors();

	do_I2C_stuff();

//#if (MAG_YAW_DRIFT == 1)
//	// This is a simple counter to do stuff at 4hz
//	if ( udb_heartbeat_counter % 10 == 0 )
//	{
//		rxMagnetometer() ;
//	}
//#endif
		
	if (dcm_flags._.calib_finished) {
		dcm_run_imu_step() ;
	}
	
	dcm_servo_callback_prepare_outputs() ;
	
	if (!dcm_flags._.init_finished)
	{
		dcm_run_init_step() ;
	}
	
	HILSIM_send_outputs() ;
	
	return ;
}


void dcm_calibrate(void)
{
	// Don't allow re/calibrating before the initial calibration period has finished
	if (dcm_flags._.calib_finished)
	{
		udb_a2d_record_offsets() ;
	}
	
	return ;
}


void dcm_set_origin_location(long o_long, long o_lat, long o_alt)
{
	union longbbbb accum_nav ;
	
	lat_origin.WW = o_lat ;
	long_origin.WW = o_long ;
	alt_origin.WW = o_alt;
	
	//	scale the latitude from GPS units to gentleNAV units
	accum_nav.WW = __builtin_mulss( LONGDEG_2_BYTECIR , lat_origin._.W1 ) ;

	unsigned char  	lat_cir ;	lat_cir = accum_nav.__.B2 ;
	//	estimate the cosine of the latitude, which is used later computing desired course
	cos_lat = cosine ( lat_cir ) ;
	
	return ;
}


struct relative3D dcm_absolute_to_relative(struct waypoint3D absolute)
{
	struct relative3D rel ;
	union longww accum_nav ;
	
	rel.z = absolute.z ;
	
	rel.y = (absolute.y - lat_origin.WW)/90 ; // in meters
	
	accum_nav.WW = ((absolute.x - long_origin.WW)/90) ; // in meters
	accum_nav.WW = ((__builtin_mulss ( cos_lat , accum_nav._.W0 )<<2)) ;
	rel.x = accum_nav._.W1 ;
	
	return rel ;
}
