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
