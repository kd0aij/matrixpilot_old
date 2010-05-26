#include "libDCM_internal.h"
#include "defines.h"


struct waypoint3D GPSlocation 		  = { 0 , 0 , 0 } ;
struct relative3D GPSvelocity 		  = { 0 , 0 , 0 } ;
struct relative2D velocity_thru_air   = { 0 , 0 } ;

union longbbbb lat_gps , long_gps , alt_sl_gps, tow ;  	// latitude, longitude, altitude
union intbb    sog_gps , cog_gps , climb_gps, week_no ;	// speed over ground, course over ground, climb
unsigned char  hdop ;									// horizontal dilution of precision

union longbbbb xpg , ypg , zpg ;						// gps x, y, z position
union intbb    xvg , yvg , zvg ;						// gps x, y, z velocity 
unsigned char  mode1 , mode2 , svs ;					// gps mode1, mode2, and number of satellites

unsigned char  	lat_cir ;
int				cos_lat ;

signed char actual_dir ;
int gps_data_age ;

extern void (* msg_parse ) ( unsigned char inchar ) ;


void gpsoutline2(char message[]) // output one NMEA line to the GPS
{
	int index ;
	char outchar ;
	index = 0 ;
	while  (  (outchar = message[index++])  ) 
	{
		udb_gps_send_char(outchar) ;
	}
	return ;
}

void gpsoutbin2(int length , const unsigned char msg[] )  // output a binary message to the GPS
{
	int index = 0 ;
	while ( index < length )
	{
		udb_gps_send_char( msg[index] ) ;
		index++;
	}
	return ;
}


// Got a character from the GPS
void udb_gps_callback_received_char(char rxchar)
{
	//bin_out ( rxchar ) ; // binary out to the debugging USART	
	(* msg_parse) ( rxchar ) ; // parse the input byte
	return ;
}


// Received a full set of GPS messages
void udb_background_callback_triggered(void) 
{
	estYawDrift() ;
	
	if ( gps_nav_valid() )
	{
		gps_data_age = 0 ;
		
		dcm_callback_location_updated() ;
		estimateWind() ;
	}
	else
	{
		gps_data_age = GPS_DATA_MAX_AGE+1 ;
	}
	
	return ;
}
