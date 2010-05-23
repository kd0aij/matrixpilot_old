#include "libUDB.h"

#define LONGDEG_2_BYTECIR 305
// = (256/360)*((256)**4)/(10**7)

#define COURSEDEG_2_BYTECIR 466
 // = (256/360)*((256)**2)/(10**2)

#define RADPERSEC ((long long)5632.0/SCALEGYRO)
// one radian per second, in AtoD/2 units

#define GRAVITYM ((long long)980.0) 
// 100 times gravity, meters/sec/sec

#define ACCELSCALE ((long) ( GRAVITY/GRAVITYM ) )

#define CENTRISCALE ((long) (((long long)519168.0)*GRAVITY)/((long long)RADPERSEC*GRAVITYM))
// scale factor in multiplying omega times velocity to get centrifugal acceleration

#define CENTRIFSAT ((long) (GRAVITYM*RADPERSEC)/(GRAVITY*((long long)32)))
// saturation limit for the centrifugal adjustment to avoid numeric overflow


struct ww { int W0 ; int W1 ; } ;
union longww { long  WW ; struct ww _ ; } ;

void imu(void) ;

extern int firstsamp ; // used on startup to detect first A/D sample
extern int calibcount ; // number of PWM pulses before control is turned on

struct relative2D { int x ; int y ; } ;

struct bbbb { unsigned char B0 ; unsigned char B1 ; unsigned char B2 ; unsigned char B3 ; } ;
struct bb { unsigned char B0 ; unsigned char B1 ; } ;

union intbb { int BB ; struct bb _ ; } ;
union longbbbb { long WW ; struct ww _ ; struct bbbb __ ; } ;

void set_gps2(void) ;
void init_T3(void) ;

int cosine ( signed char angle ) ;
int sine ( signed char angle ) ;
signed char rect_to_polar ( struct relative2D *xy ) ;
void rotate( struct relative2D *xy , signed char angle ) ;
void estYawDrift(void) ;
extern fractional dirovergndHRmat[] ;
extern fractional dirovergndHGPS[] ;
extern fractional rmat[] ;
extern fractional omega[] ;
extern fractional omegaAccum[] ;
extern fractional omegagyro[] ;

extern unsigned char  	lat_cir ;
extern int				cos_lat ;

extern union longbbbb lat_origin , long_origin , alt_origin ;
extern union longbbbb x_origin , y_origin , z_origin ;

struct flag_bits {
			unsigned int unused					: 3 ;
			unsigned int mag_drift_req			: 1 ;
			unsigned int first_mag_reading		: 1 ;
			unsigned int yaw_req				: 1 ;
			unsigned int save_origin   			: 1 ;
			unsigned int GPS_steering			: 1 ;
			unsigned int pitch_feedback			: 1 ;
			unsigned int altitude_hold_throttle	: 1 ;
			unsigned int altitude_hold_pitch	: 1 ;
			unsigned int man_req				: 1 ;
			unsigned int auto_req				: 1 ;
			unsigned int home_req				: 1 ;
			unsigned int nav_capable			: 1 ;
			unsigned int servos_set				: 1 ;
			} ;

extern union fbts_int { struct flag_bits _ ; int WW ; } flags ;

extern signed char	desired_dir , actual_dir ;


