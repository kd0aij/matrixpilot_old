#include "libUDB.h"
#include "libDCM_defines.h"


// libDCM.h defines the API for accessing the location and orientation information
// from the DCM algorithm and GPS.
// 
// Requires libUDB


// Functions
void dcm_callback_location_updated(void) ;					// Callback
void dcm_enable_yaw_drift_correction(boolean enabled) ;		// Allows disabling yaw drift estimation
void dcm_calibrate(void) ;

// Is our gps data good enough for navigation?
boolean gps_nav_valid(void) ;


// Rotation utility functions
int cosine ( signed char angle ) ;
int sine ( signed char angle ) ;
signed char rect_to_polar ( struct relative2D *xy ) ;
void rotate( struct relative2D *xy , signed char angle ) ;


// Vars
extern union dcm_fbts_byte { struct dcm_flag_bits _ ; char b ; } dcm_flags ;

// Outside of libDCM, these should be treated as read-only
extern fractional rmat[] ;
extern fractional omegaAccum[] ;
extern fractional omegagyro[] ;

extern struct relative3D GPSlocation ;
extern struct relative3D GPSvelocity ;
extern struct relative2D velocity_thru_air ; // derived horizontal velocity relative to air in cm/sec
extern int    estimatedWind[3] ;			// wind velocity vectors in cm / sec

extern union longww IMUvelocityx , IMUvelocityy , IMUvelocityz ;
extern union longww IMUlocationx , IMUlocationy , IMUlocationz ;

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
