#include "libUDB.h"

void gps_startup_sequence(int gpscount) ;
boolean gps_nav_valid(void) ;

void init_T3(void) ;
void init_states(void) ;
void init_behavior( void ) ;

void setup_origin_2D_location(void) ;
void navigate(void) ;
int determine_navigation_deflection(char navType);

void estimateWind(void) ;
void rxMagnetometer(void) ;

void state_machine(void) ;
void filterInputs(void) ;

void yawCntrl(void) ;
void rollCntrl(void) ;
void pitchCntrl(void) ;
void altitudeCntrl(void) ;
void cameraCntrl(void) ;
void mixServos(void) ;
void setBehavior(int newBehavior) ;
void updateBehavior(void) ;
void updateTriggerAction(void) ;

void serial_output( char* format, ... ) ;
void serial_output_4hz(void) ;

void processwaypoints(void) ;
void init_waypoints( int waypointSetIndex ) ;


struct waypoint2D { long x ; long y ; } ;
struct waypoint3D { long x ; long y ; int z ; } ;
struct waypointDef { struct waypoint3D loc ; int flags ; struct waypoint3D viewpoint ; } ;

extern struct waypoint3D GPSlocation ;
extern struct waypoint3D GPSvelocity ;
extern struct relative2D velocity_thru_air ; // derived horizontal velocity relative to air in cm/sec
extern struct relative2D vector_to_origin ;
extern struct relative2D togoal ;
extern struct relative2D vector_to_waypoint;
extern struct relative2D vector_to_steer ;
extern int    estimatedWind[3] ;			// wind velocity vectors in cm / sec

extern struct waypoint3D camera_view ;
extern union longww IMUlocationx , IMUlocationy , IMUlocationz   ;
extern struct waypoint3D IMUvelocity ;
struct waypointparameters { int x ; int y ; int cosphi ; int sinphi ; signed char phi ; int height ; int fromHeight; int legDist; } ;


extern int pitch_control, roll_control, yaw_control, altitude_control ;

extern int dutycycle ;	// used to compute PWM duty cycle
extern int firstsamp ;	// used on startup to detect first A/D sample
extern int calibcount ;	// number of PWM pulses before control is turned on

extern union longbbbb lat_gps , long_gps , alt_sl_gps , tow ;
extern union intbb    sog_gps , cog_gps , climb_gps, week_no ;
extern unsigned char  hdop ;
extern union longbbbb xpg , ypg , zpg ;
extern union intbb    xvg , yvg , zvg ;
extern unsigned char  mode1 , mode2 , svs, hdop ;

extern unsigned char  	lat_cir ;
extern int				cos_lat ;

extern union longbbbb lat_origin , long_origin , alt_origin ;
extern union longbbbb x_origin , y_origin , z_origin ;

extern signed char	desired_dir , actual_dir ;
extern signed char  calculated_heading ; // takes into account wind velocity
extern signed char  bearing_to_origin ;

extern int tofinish_line ;
extern int progress_to_goal ; // Fraction of the way to the goal in the range 0-4096 (2^12)
extern int height ;

extern int waggle, calib_timer, standby_timer ;
extern int gps_data_age ;

extern union longww throttleFiltered ;
extern int pitchAltitudeAdjust ;

extern signed char GPS_pitch  ;

extern int velocity_magnitude ;
extern int forward_acceleration  ;
extern int velocity_previous  ;
extern int air_speed_magnitude;


// Choose the type of air frame by setting AIRFRAME_TYPE in options.h
// See options.h for a description of each type
#define AIRFRAME_STANDARD			0
#define AIRFRAME_VTAIL				1
#define AIRFRAME_DELTA				2
#define AIRFRAME_HELI				3


// Serial Output Format
#define SERIAL_NONE			0	// No serial data is sent
#define SERIAL_DEBUG		1	// UAV Dev Board debug info
#define SERIAL_ARDUSTATION	2	// Compatible with ArduStation
#define SERIAL_UDB			3	// Pete's efficient UAV Dev Board format
#define SERIAL_OSD_REMZIBI	4	// Output data formatted to use as input to a Remzibi OSD (only works with GPS_UBX)
#define SERIAL_OSD_IF		5	// Output data formatted to use as input to a IF OSD (only works with GPS_UBX)
#define SERIAL_MAGNETOMETER	6	// Debugging the magnetometer
#define SERIAL_UDB_EXTRA	7	// Extra Telemetry beyond that provided by SERIAL_UDB for higher bandwidth connections


// GPS Type
#define GPS_STD				1
#define GPS_UBX_2HZ			2
#define GPS_UBX_4HZ			4

#define GPS_RATE			GPS_TYPE //Hah hah, this works for now

// Failsafe Type
#define FAILSAFE_RTL		1
#define FAILSAFE_WAYPOINTS	2

// AltitudeHold type
#define AH_NONE				0
#define AH_PITCH_ONLY		1
#define AH_FULL				3

// If GPS data has not been received for this many state machine cycles, consider the GPS lock to be lost.
#define GPS_DATA_MAX_AGE	9


// Negate VALUE if NEEDS_REVERSING is true
#define REVERSE_IF_NEEDED(NEEDS_REVERSING, VALUE)		((NEEDS_REVERSING) ? (-(VALUE)) : (VALUE))


#define LONGDEG_2_BYTECIR 305 // = (256/360)*((256)**4)/(10**7)
#define COURSEDEG_2_BYTECIR 466 // = (256/360)*((256)**2)/(10**2)
#define CALIB_PAUSE 12
#define STANDBY_PAUSE 48 // pause for 16 seconds of runs through the state machine
#define NUM_WAGGLES 4 // waggle 4 times during the end of the standby pause (this number must be less than STANDBY_PAUSE)
#define WAGGLE_SIZE 300

#define SERVORANGE (int) (SERVOSAT*1000)
#define SERVOMAX 3000 + SERVORANGE
#define SERVOMIN 3000 - SERVORANGE

struct behavior_flag_bits {
			unsigned int takeoff		: 1 ;				// unimplemented
			unsigned int inverted		: 1 ;	// fly iverted
			unsigned int hover			: 1 ;	// hover the plane
			unsigned int rollLeft		: 1 ;				// unimplemented
			unsigned int rollRight		: 1 ;				// unimplemented
			unsigned int trigger		: 1 ;	// trigger action
			unsigned int loiter			: 1 ;	// stay on the current waypoint
			unsigned int land			: 1 ;	// throttle off
			unsigned int absolute		: 1 ;	// absolute waypoint
			unsigned int altitude		: 1 ;	// climb/descend to goal altitude
			unsigned int unused			: 6 ;
			} ;

#define F_NORMAL						0
#define F_TAKEOFF						1
#define F_INVERTED						2
#define F_HOVER							4
#define F_ROLL_LEFT						8
#define F_ROLL_RIGHT					16
#define F_TRIGGER						32
#define F_LOITER						64
#define F_LAND							128
#define F_ABSOLUTE						256
#define F_ALTITUDE_GOAL					512

union bfbts_word { struct behavior_flag_bits _ ; int W ; };

extern int current_orientation ;
extern union bfbts_word desired_behavior ;


#define TRIGGER_TYPE_NONE				0
#define TRIGGER_TYPE_SERVO				1
#define TRIGGER_TYPE_DIGITAL			2

#define TRIGGER_PULSE_HIGH				4
#define TRIGGER_PULSE_LOW				8
#define TRIGGER_TOGGLE					16
#define TRIGGER_REPEATING				32


#define WIND_NAV_AIR_SPEED_MIN			200		// Minimum airspeed in cm/sec for wind navigation to apply

#define CAM_VIEW_LAUNCH					{ 0, 0, 0 }

