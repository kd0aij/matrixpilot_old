#ifndef GPSPARSECOMMON_H
#define GPSPARSECOMMON_H


#define GPS_RATE			((GPS_TYPE == GPS_MTEK) ? 4 : GPS_TYPE)

// If GPS data has not been received for this many state machine cycles, consider the GPS lock to be lost.
#define GPS_DATA_MAX_AGE	9


extern struct relative3D GPSlocation ;
extern struct relative3D GPSvelocity ;
extern union longbbbb lat_origin , long_origin , alt_origin ;
extern union longbbbb lat_gps , long_gps , alt_sl_gps, tow ;  	// latitude, longitude, altitude
extern union intbb    sog_gps , cog_gps , climb_gps, week_no ;	// speed over ground, course over ground, climb
extern unsigned char  hdop ;									// horizontal dilution of precision
extern unsigned char  svs ;										// number of satellites

extern int	cos_lat;
extern int gps_data_age;
extern char *gps_out_buffer;
extern int gps_out_buffer_length;
extern int gps_out_index;

extern signed char actual_dir ;
extern unsigned int ground_velocity_magnitudeXY;
extern int forward_acceleration;
extern unsigned int air_speed_magnitudeXY;
extern unsigned int air_speed_3DGPS;
extern signed char calculated_heading ;

extern void (* msg_parse ) ( unsigned char inchar ) ;


void gpsoutbin(int length , const unsigned char msg[]);  // output a binary message to the GPS
void gpsoutline(char message[]); // output one NMEA line to the GPS
int udb_gps_callback_get_byte_to_send(void);
void udb_gps_callback_received_byte(char rxchar);

// Received a full set of GPS messages
void udb_background_callback_triggered(void);

///////////////////////////////////////////////////////////////////////////////
// These functions are implemented by the GPS specific driver modules
void commit_gps_data(void) ;

// FIXME: This should be handled internally, along with DCM calibration
// Count down from 1000 at 40Hz
void gps_startup_sequence( int gpscount ) ;

// Is our gps data good enough for navigation?
boolean gps_nav_valid(void) ;



#endif // GPSPARSECOMMON_H
