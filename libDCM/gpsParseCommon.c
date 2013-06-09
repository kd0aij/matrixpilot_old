// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


#include "libDCM_internal.h"
#include <string.h>


struct relative3D GPSlocation 		  = { 0 , 0 , 0 } ;
struct relative3D GPSvelocity 		  = { 0 , 0 , 0 } ;

union longbbbb lat_gps , long_gps , alt_sl_gps, tow ;  	// latitude, longitude, altitude
union intbb    sog_gps , cog_gps , climb_gps, week_no ;	// speed over ground, course over ground, climb
union intbb	   as_sim ;
uint8_t  hdop ;									// horizontal dilution of precision

union longbbbb lat_origin , long_origin , alt_origin ;

//union longbbbb xpg , ypg , zpg ;						// gps x, y, z position
//union intbb    xvg , yvg , zvg ;						// gps x, y, z velocity
//uint8_t  mode1 , mode2 ;						// gps mode1, mode2
uint8_t  svs ;									// number of satellites

uint8_t  	lat_cir ;
int16_t				cos_lat = 0 ;

int16_t gps_data_age ;

uint8_t *gps_out_buffer = 0 ;
int16_t gps_out_buffer_length = 0 ;
int16_t gps_out_index = 0 ;


extern void (* msg_parse ) ( uint8_t inchar ) ;


void gpsoutbin(int16_t length , const uint8_t msg[] )  // output a binary message to the GPS
{
	gps_out_buffer = 0 ; // clear the buffer pointer first, for safety, in case we're interrupted
	gps_out_index = 0 ;
	gps_out_buffer_length = length ;
	gps_out_buffer = (uint8_t*)msg ;
	
	udb_gps_start_sending_data() ;
	
	return ;
}


void gpsoutline(char *message) // output one NMEA line to the GPS
{
	gpsoutbin(strlen(message), (uint8_t*)message) ;
	return ;
}


int16_t udb_gps_callback_get_byte_to_send(void)
{
	if (gps_out_buffer != 0 && gps_out_index < gps_out_buffer_length) {
		// We have a byte to send
		return (uint8_t)(gps_out_buffer[gps_out_index++]) ;
	}
	else
	{
		// No byte to send, so clear the link to the buffer
		gps_out_buffer = 0 ;
	}
	return -1 ;
}


// Got a character from the GPS
void udb_gps_callback_received_byte(uint8_t rxchar)
{
	//bin_out ( rxchar ) ; // binary out to the debugging USART	
	(* msg_parse) ( rxchar ) ; // parse the input byte
	return ;
}

int8_t actual_dir ;
int8_t cog_previous = 64 ;
uint16_t ground_velocity_magnitudeXY = 0 ;
int16_t sog_previous = 0 ;
int16_t climb_rate_previous = 0 ;
int16_t forward_acceleration = 0 ;
uint16_t velocity_previous = 0 ;
uint16_t air_speed_magnitudeXY = 0;
uint16_t air_speed_3DGPS = 0 ;
int8_t calculated_heading ;
int16_t location_previous[] = { 0 , 0 , 0 } ;
union longww GPS_location_previous[3] ;
int16_t GPS_raw_velocity_previous[3] ;
int16_t GPS_consistency[3] = { 0 , 0 , 0 } ;

// Received a full set of GPS messages
void udb_background_callback_triggered(void) 
{
	union longbbbb accum_nav ;
	union longbbbb accum ;
	union longww accum_velocity ;
	int8_t cog_circular ;
	int8_t cog_delta ;
	int16_t sog_delta ;
	int16_t climb_rate_delta ;
	int16_t location[3] ;
	int16_t location_deltaZ ;
	struct relative2D location_deltaXY ;
	struct relative2D velocity_thru_air ;
	int16_t velocity_thru_airz ;
	int16_t GPS_raw_velocity[3] ;
	int16_t GPS_raw_location_delta[3] ;

	dirovergndHRmat[0] = rmat[1] ;
	dirovergndHRmat[1] = rmat[4] ;
	dirovergndHRmat[2] = 0 ;
	
	if ( gps_nav_valid() )
	{
		commit_gps_data() ;

		gps_data_age = 0 ;

		dcm_callback_gps_location_updated() ;

	    // convert GPS course of 360 degrees to a binary model with 256	
		accum.WW = __builtin_muluu ( COURSEDEG_2_BYTECIR , cog_gps.BB ) + 0x00008000 ;
	    // re-orientate from compass (clockwise) to maths (anti-clockwise) with 0 degrees in East 
		cog_circular = -accum.__.B2 + 64 ;

		// perform a GPS consistency check of velocity and change in location

		// compute raw GPS velocity vector in CM/sec

		accum_velocity.WW = ( __builtin_mulss( cosine( cog_circular ) , sog_gps.BB) << 2) + 0x00008000 ;
		GPS_raw_velocity[0]  = accum_velocity._.W1 ;	
		accum_velocity.WW = (__builtin_mulss( sine( cog_circular ) , sog_gps.BB) << 2 ) + 0x00008000 ;
		GPS_raw_velocity[1] = accum_velocity._.W1 ;
		GPS_raw_velocity[2] = climb_gps.BB ;

		if ( dcm_flags._.gps_history_valid )
		{
			// compute change in location in cm
			accum_nav._.W0 = ((long_gps._.W0 - GPS_location_previous[0]._.W0)/9)*10 ;
			accum_nav.WW = ( __builtin_mulss( accum_nav._.W0 , cos_lat ) << 2 ) ; 
			GPS_raw_location_delta[0] =  accum_nav._.W1 ;
			GPS_raw_location_delta[1] = ((lat_gps._.W0 - GPS_location_previous[1]._.W0)/9)*10 ; 
			GPS_raw_location_delta[2] = alt_sl_gps._.W0 - GPS_location_previous[2]._.W0 ;

			GPS_consistency[0] = GPS_raw_location_delta[0] 
								- (  GPS_raw_velocity[0] /(2*GPS_RATE ) +  GPS_raw_velocity_previous[0] /(2*GPS_RATE) ) ;
			GPS_consistency[1] = GPS_raw_location_delta[1] 
								- (  GPS_raw_velocity[1] /(2*GPS_RATE ) +  GPS_raw_velocity_previous[1] /(2*GPS_RATE) ) ;
			GPS_consistency[2] = GPS_raw_location_delta[2] 
								- (  GPS_raw_velocity[2] /(2*GPS_RATE ) +  GPS_raw_velocity_previous[2] /(2*GPS_RATE) ) ;
		}

		GPS_raw_velocity_previous[0] = GPS_raw_velocity[0] ;
		GPS_raw_velocity_previous[1] = GPS_raw_velocity[1] ;
		GPS_raw_velocity_previous[2] = GPS_raw_velocity[2] ;

		GPS_location_previous[0].WW = long_gps.WW ;
		GPS_location_previous[1].WW = lat_gps.WW ;
		GPS_location_previous[2].WW = alt_sl_gps.WW ;

		accum_nav.WW = ((lat_gps.WW - lat_origin.WW)/90) ; // in meters, range is about 20 miles
		location[1] = accum_nav._.W0 ;

		accum_nav.WW = long_scale((long_gps.WW - long_origin.WW)/90 , cos_lat ) ;
		location[0] = accum_nav._.W0 ;	
		
		accum_nav.WW = ( alt_sl_gps.WW - alt_origin.WW)/100 ; // height in meters
		location[2] = accum_nav._.W0 ;

		// compensate for GPS reporting latency.
		// The dynamic model of the EM406 and uBlox is not well known.
		// However, it seems likely much of it is simply reporting latency.
		// This section of the code compensates for reporting latency.
#if ( HILSIM == 1 )
		{
			cog_delta = 0 ;
			sog_delta = 0 ;
			climb_rate_delta = 0 ;
			location_deltaXY.x = 0 ;
			location_deltaXY.y = 0 ;
			location_deltaZ = 0 ;
		}
#else
		if ( dcm_flags._.gps_history_valid )
		{
			cog_delta = cog_circular - cog_previous ;
			sog_delta = sog_gps.BB - sog_previous ;
			climb_rate_delta = climb_gps.BB - climb_rate_previous ;

			location_deltaXY.x = location[0] - location_previous[0] ;
			location_deltaXY.y = location[1] - location_previous[1] ;
			location_deltaZ = location[2] - location_previous[2] ;
		}
		else
		{
			cog_delta = 0 ;
			sog_delta = 0 ;
			climb_rate_delta = 0 ;
			location_deltaXY.x = 0 ;
			location_deltaXY.y = 0 ;
			location_deltaZ = 0 ;
		}
#endif
		dcm_flags._.gps_history_valid = 1 ;
		actual_dir = cog_circular + cog_delta ;
		cog_previous = cog_circular ;

		// Note that all these velocities are in centimeters / second

		ground_velocity_magnitudeXY = sog_gps.BB + sog_delta ;
		sog_previous = sog_gps.BB ;

		GPSvelocity.z = climb_gps.BB + climb_rate_delta ;
		climb_rate_previous = climb_gps.BB ;
		
		accum_velocity.WW = ( __builtin_mulss( cosine( actual_dir ) , ground_velocity_magnitudeXY) << 2) + 0x00008000 ;
		GPSvelocity.x = accum_velocity._.W1 ;
	
		accum_velocity.WW = (__builtin_mulss( sine( actual_dir ) , ground_velocity_magnitudeXY) << 2 ) + 0x00008000 ;
		GPSvelocity.y = accum_velocity._.W1 ;

		rotate ( &location_deltaXY , cog_delta) ; // this is a key step to account for rotation effects!!

		GPSlocation.x = location[0] + location_deltaXY.x ;
		GPSlocation.y = location[1] + location_deltaXY.y ;
		GPSlocation.z = location[2] + location_deltaZ ;

		location_previous[0] = location[0] ;
		location_previous[1] = location[1] ;
		location_previous[2] = location[2] ;

		velocity_thru_air.y = GPSvelocity.y - estimatedWind[1] ;
		velocity_thru_air.x = GPSvelocity.x - estimatedWind[0] ;  
		velocity_thru_airz = GPSvelocity.z - estimatedWind[2] ; 

#if ( HILSIM == 1)
		air_speed_3DGPS = as_sim.BB ; // use Xplane as a pitot
#else
		air_speed_3DGPS = vector3_mag ( velocity_thru_air.x , velocity_thru_air.y , velocity_thru_airz  ) ;
#endif
                                
		calculated_heading  = rect_to_polar( &velocity_thru_air ) ;
		// veclocity_thru_air.x becomes XY air speed as a by product of CORDIC routine in rect_to_polar()
		air_speed_magnitudeXY = velocity_thru_air.x; // in cm / sec

#if ( GPS_RATE == 4 )
		forward_acceleration = (air_speed_3DGPS - velocity_previous) << 2 ; // Ublox enters code 4 times per second
#elif ( GPS_RATE == 2 )
		forward_acceleration = (air_speed_3DGPS - velocity_previous) << 1 ; // Ublox enters code 2 times per second
#else
		forward_acceleration = air_speed_3DGPS - velocity_previous ; // EM406 standard GPS enters code once per second
#endif
	
		velocity_previous = air_speed_3DGPS ;

		estimateWind() ;
		estYawDrift() ;	
		dcm_flags._.yaw_req = 1 ;  // request yaw drift correction 
		dcm_flags._.reckon_req = 1 ; // request dead reckoning correction
		dcm_flags._.rollpitch_req = 1 ;
	
#if ( DEADRECKONING == 0 )
		process_flightplan() ;
#endif	


	}
	else
	{
		gps_data_age = GPS_DATA_MAX_AGE+1 ;
		dirovergndHGPS[0] = dirovergndHRmat[0] ;
		dirovergndHGPS[1] = dirovergndHRmat[1] ;
		dirovergndHGPS[2] = 0 ;
		dcm_flags._.yaw_req = 1 ;  // request yaw drift correction 	
		dcm_flags._.gps_history_valid = 0 ; // gps history has to be restarted
	}
	
	return ;
}
