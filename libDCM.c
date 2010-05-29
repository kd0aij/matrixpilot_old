#include "libDCM_internal.h"

union dcm_fbts_byte dcm_flags ;

char dcm_fourHertzCounter = 0 ;
boolean dcm_has_calibrated = false ;


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
