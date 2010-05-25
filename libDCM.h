#include "libUDB.h"
#include "libDCM_defines.h"

// Functions
void dcm_callback_location_updated(void) ;		// Callback

boolean gps_nav_valid(void) ;
void estimateWind(void) ;
void rxMagnetometer(void) ;


// Vars
extern struct waypoint3D GPSlocation ;
extern struct velocity3D GPSvelocity ;
extern struct relative2D velocity_thru_air ; // derived horizontal velocity relative to air in cm/sec
extern int    estimatedWind[3] ;			// wind velocity vectors in cm / sec

extern union longbbbb lat_gps , long_gps , alt_sl_gps , tow ;
extern union intbb    sog_gps , cog_gps , climb_gps, week_no ;
extern unsigned char  hdop ;
extern union longbbbb xpg , ypg , zpg ;
extern union intbb    xvg , yvg , zvg ;
extern unsigned char  mode1 , mode2 , svs, hdop ;

extern unsigned char  	lat_cir ;
extern int				cos_lat ;

extern signed char  calculated_heading ; // takes into account wind velocity
extern int gps_data_age ;

extern int velocity_magnitude ;
extern int forward_acceleration  ;
extern int air_speed_magnitude;




// Internal
extern signed char	actual_dir ;
extern int velocity_previous  ;
