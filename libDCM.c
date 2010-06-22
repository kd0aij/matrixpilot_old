// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009, 2010 MatrixPilot Team
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


#include "libDCM_internal.h"

union dcm_fbts_byte dcm_flags ;

char dcm_fourHertzCounter = 0 ;
boolean dcm_has_calibrated = false ;

#if ( HILSIM == 1 )
unsigned char SIMservoOutputs[] = {	0xFF, 0xEE,		//sync
									0x03, 0x04,		//S1
									0x05, 0x06,		//S2
									0x07, 0x08,		//S3
									0x09, 0x0A,		//S4
									0x0B, 0x0C,		//S5
									0x0D, 0x0E,		//S6
									0x0F, 0x10		//checksum
									};

void send_HILSIM_outputs( void ) ;
#endif


// Called at 40Hz
void udb_servo_callback_prepare_outputs(void)
{
	// This is a simple counter to do stuff at 4hz
	dcm_fourHertzCounter++ ;
	if ( dcm_fourHertzCounter >= 10 )
	{
		rxMagnetometer() ;
		dcm_fourHertzCounter = 0 ;
	}
	
	if (dcm_has_calibrated) {
		dcm_run_imu_step() ;
	}
	
	dcm_servo_callback_prepare_outputs() ;
	
#if ( HILSIM == 1)
	send_HILSIM_outputs() ;
#endif
	
	return ;
}


void dcm_calibrate(void)
{
	udb_a2d_record_offsets() ;
	dcm_has_calibrated = true ;
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
	lat_cir = accum_nav.__.B2 ;
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
	
	return ;
}


#if ( HILSIM == 1 )
void send_HILSIM_outputs( void )
{
	// Setup outputs for HILSIM
	int i ;
	unsigned char CK_A = 0 ;
	unsigned char CK_B = 0 ;
	int temp ;
	
	for (i=1; i<=NUM_OUTPUTS; i++)
	{
		temp = udb_pwOut[i] ;
		SIMservoOutputs[2*i] = temp >> 8 ;
		SIMservoOutputs[(2*i)+1] = temp & 0xFF ;
	}
	
	for (i=2; i<14; i++)
	{
		CK_A += SIMservoOutputs[i] ;
		CK_B += CK_A ;
	}
	
	SIMservoOutputs[14] = CK_A ;
	SIMservoOutputs[15] = CK_B ;
	
	// Send HILSIM outputs
	for (i=0; i<16; i++)
	{
		udb_gps_send_char(SIMservoOutputs[i]) ;	
	}
}
#endif
