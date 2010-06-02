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

extern union longbbbb tow ;
extern union intbb    sog_gps , cog_gps , climb_gps, week_no ;
extern unsigned char  hdop ;
extern union longbbbb xpg , ypg , zpg ;
extern union intbb    xvg , yvg , zvg ;
extern unsigned char  mode1 , mode2 , svs, hdop ;

extern int forward_acceleration  ;

extern unsigned char  	lat_cir ;
extern int				cos_lat ;
