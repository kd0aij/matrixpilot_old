#include "libDCM_internal.h"
#include "defines.h"


struct relative3D GPSlocation 		  = { 0 , 0 , 0 } ;
struct relative3D GPSvelocity 		  = { 0 , 0 , 0 } ;
struct relative2D velocity_thru_air   = { 0 , 0 } ;

union longbbbb lat_gps , long_gps , alt_sl_gps, tow ;  	// latitude, longitude, altitude
union intbb    sog_gps , cog_gps , climb_gps, week_no ;	// speed over ground, course over ground, climb
unsigned char  hdop ;									// horizontal dilution of precision

union longbbbb lat_origin , long_origin , alt_origin ;

union longbbbb xpg , ypg , zpg ;						// gps x, y, z position
union intbb    xvg , yvg , zvg ;						// gps x, y, z velocity 
unsigned char  mode1 , mode2 , svs ;					// gps mode1, mode2, and number of satellites

unsigned char  	lat_cir ;
int				cos_lat = 0 ;

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
	union longbbbb accum_nav ;
		
	estYawDrift() ;
	
	if ( gps_nav_valid() )
	{
		gps_data_age = 0 ;
		
		accum_nav.WW = ((lat_origin.WW - lat_gps.WW)/90) ; // in meters, range is about 20 miles
		GPSlocation.y = accum_nav._.W0 ;
		
		//	multiply the longitude delta by the cosine of the latitude
		accum_nav.WW = ((long_origin.WW - long_gps.WW)/90) ; // in meters
		accum_nav.WW = ((__builtin_mulss ( cos_lat , accum_nav._.W0 )<<2)) ;
		GPSlocation.x = accum_nav._.W1 ;
		
		GPSlocation.z = ( alt_sl_gps.WW - alt_origin.WW)/100 ; // height in meters
	
		dcm_callback_gps_location_updated() ;
		estimateWind() ;
	}
	else
	{
		gps_data_age = GPS_DATA_MAX_AGE+1 ;
	}
	
	return ;
}
