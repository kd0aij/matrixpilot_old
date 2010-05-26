#include "libDCM.h"

void estYawDrift(void) ;
void estimateWind(void) ;

void dcm_run_imu_step(void) ;	// This needs to be run every 25ms
void rxMagnetometer(void) ;		// This should be called every 250ms


extern signed char	actual_dir ;
extern int velocity_previous  ;
extern boolean skipYawDrift ;

extern fractional dirovergndHRmat[] ;
extern fractional dirovergndHGPS[] ;
extern fractional omega[] ;
