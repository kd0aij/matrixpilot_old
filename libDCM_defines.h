#ifndef DCM_DEFINES_H
#define DCM_DEFINES_H


// Types
struct bb { unsigned char B0 ; unsigned char B1 ; } ;
struct bbbb { unsigned char B0 ; unsigned char B1 ; unsigned char B2 ; unsigned char B3 ; } ;
struct ww { int W0 ; int W1 ; } ;

union intbb { int BB ; struct bb _ ; } ;
union longbbbb { long WW ; struct ww _ ; struct bbbb __ ; } ;
union longww { long  WW ; struct ww _ ; } ;

struct relative2D { int x ; int y ; } ;
struct absolute2D { long x ; long y ; } ;
struct relative3D { int x ; int y ; int z ; } ;

struct waypoint3D { long x ; long y ; int z ; } ;
struct waypointDef { struct waypoint3D loc ; int flags ; struct waypoint3D viewpoint ; } ;

struct dcm_flag_bits {
			unsigned int unused					: 4 ;
			unsigned int mag_drift_req			: 1 ;
			unsigned int first_mag_reading		: 1 ;
			unsigned int yaw_req				: 1 ;
			unsigned int nav_capable			: 1 ;
			} ;


// Defines
// GPS Type
#define GPS_STD				1
#define GPS_UBX_2HZ			2
#define GPS_UBX_4HZ			4

#define GPS_RATE			GPS_TYPE //Hah hah, this works for now

// If GPS data has not been received for this many state machine cycles, consider the GPS lock to be lost.
#define GPS_DATA_MAX_AGE	9

#define LONGDEG_2_BYTECIR 305 // = (256/360)*((256)**4)/(10**7)
#define COURSEDEG_2_BYTECIR 466 // = (256/360)*((256)**2)/(10**2)

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

#define WIND_NAV_AIR_SPEED_MIN			200		// Minimum airspeed in cm/sec for wind navigation to apply

#endif
