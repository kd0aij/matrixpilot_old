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


#include "defines.h"
#include "../libDCM/libDCM_internal.h"


#if (USE_OSD == OSD_REMZIBI)

#include <string.h>
#include "osd_layout.h"

#if ((USE_OSD == OSD_REMZIBI) && (OSD_REMZIBI_CLS_TIME == 0))
	#error("OSD_REMZIBI_CLS_TIME must be greatner that zero")
#endif

enum MP_MODE
{
	MODE_UNDEFINED,
	MODE_UNKNOWN,
	MODE_MANUAL,
	MODE_STABLE,
	MODE_WAYPOINT,
	MODE_RTH_HOLD,
	MODE_RTH      
};

enum PLANE_FLIGHT_MODE
{
	PLANE_ON_GROUND,
	PLANE_IN_FLIGHT,
	PLANE_LANDED
};

extern int waypointIndex ;

#if ( GPS_TYPE == GPS_MTEK )	extern union longbbbb date_gps_, time_gps_;
#endif

static int telemetry_counter = 0 ;
static int home_saved = false;
static int mp_mode = 0;

static int max_dist = 0;
static int max_height = 0;
static int max_speed = 0;
static int on_ground_cnt = 0;
static long distance = 0;

static long last_lat = 0;
static long last_long = 0;

static int flight_mode = PLANE_ON_GROUND;
static int in_flight_counter = 0;

static const char* mp_mode_name[] = {
		"?",
		"?",
		"M",
		"S",
		"W",
		"H",
		"R"
};

void init_serial()
{
	udb_serial_set_rate(33600) ;
}

const char* ltoa(long val, char digits)
{
	static char conversion_buffer[10+1+1];	// max digits for long + sign + eos

	boolean neg = false;

	if (val < 0)
	{
		val = -val;
		neg = true;
	}

	unsigned char n = sizeof(conversion_buffer) -1;
	conversion_buffer[n--] = 0;

	do
	{
		conversion_buffer[n--] = val % 10 + '0';
		val /= 10;
		--digits;
	}
	while (val != 0);

	while (digits > 0)
	{
		conversion_buffer[n--] = '0';
		--digits;
	}
 
	if (neg)
	{
		conversion_buffer[n--] = '-';
	}

	return conversion_buffer + n + 1;
}
 
void serial_send_coord(long coord)
{
	coord /= 10;
	serial_output("%i.", (int)(coord / 1000000L));
	serial_output((char*)ltoa(coord / 1000000L, 6));
}

static void serial_send_location(int loc)
{
	//$M,x,y,L,E,text,<CRLF>
	//  where:
    //        x - is char value of x coordinate (ex. 12 are ASCII two bytes 31,32 , or 5 is ASCII one byte 35)
    //        y - is char value of y coordinate
    //        L - is char value of Leading character (ex. 178 is ASCII bytes 31 37 38)
    //        E - is char value of Ending character
    //        text - is text to type as normal ASCII chars  
   	//  notice that coma "," at end of message must be as well as after M  
	int row = loc / 30;
	int col = loc % 30;
	if (row > 512)
	{
		row -= 512;
		col += 128;
	}
	serial_output("$M,%i,%i,", col, row);
}

static void serial_send_string(const char* str, unsigned char leading, unsigned char tailing)
{
	if (leading != 0)
	{
		serial_output("%i", leading);
	}

	serial_output(",");

	if (tailing != 0)
	{
		serial_output("%i", tailing);
	}

	serial_output(",");
	serial_output((char*)str);
	serial_output(",\r\n");
}

static void serial_send_int(int num, unsigned char leading, unsigned char tailing)
{
	if (leading != 0)
	{
		serial_output("%i", leading);
	}

	serial_output(",");

	if (tailing != 0)
	{
		serial_output("%i", tailing);
	}

	serial_output(",");
	serial_output("%i", num);
	serial_output(",\r\n");
}

static void serial_send_long(long int num, unsigned char leading, unsigned char tailing)
{
	if (leading != 0)
	{
		serial_output("%i", leading);
	}

	serial_output(",");

	if (tailing != 0)
	{
		serial_output("%i", tailing);
	}

	serial_output(",");
	serial_output("%li", num);
	serial_output(",\r\n");
}

void update_coords()
{
	unsigned int ground_speed_3DIMU = 
			vector3_mag ( 	IMUvelocityx._.W1 ,
							IMUvelocityy._.W1 ,
							IMUvelocityz._.W1   ) ;


	struct relative2D curHeading ;
	curHeading.x = -rmat[1] ;
	curHeading.y = rmat[4] ;
	signed char earth_yaw = rect_to_polar(&curHeading) ;// -128 - +127 (0=East,  ccw)

	int angle = (earth_yaw * 180 + 64) >> 7 ;			// -180 - +180 (0=East,  ccw) negative angle is reversed!!
	angle = -angle + 90;
	int azimuth = angle;
	if (azimuth < 0)
	{
		azimuth += 360;
	}

	struct relative2D toGoal;
	toGoal.x = 0 - IMUlocationx._.W1;
	toGoal.y = 0 - IMUlocationy._.W1;

	//int dir_to_goal = rect_to_polar ( &toGoal ) - earth_yaw ;
	rect_to_polar ( &toGoal );
	int dist_to_home = toGoal.x ;
	int dist_to_goal ;

	if (flags._.GPS_steering)
	{
		//dir_to_goal = desired_dir - earth_yaw ;
		dist_to_goal = abs(tofinish_line) ;
	}
	else 
	{
		dist_to_goal = dist_to_home;
	}

	//int angle = (dir_to_goal * 180 + 64) >> 7 ;			// 0-359 (0=East,  ccw)
	//angle = -angle + 90;

	long date = 0;
	long time = 0;

#if ( GPS_TYPE == GPS_MTEK )
	date = date_gps_.WW;
	time = time_gps_.WW / 1000;#endif
	
	/*
		GPS data :
		
		$A,lat,lng,numSV,[dist],alt,speed,course,[azimuth],gpsDate,gpsTime,<CRLF>
		
		Notice that comas must be after A and at end of message 
		[dist] and [azimuth] can be empty , I mean  two empty comas ,,
		Lat and lon format as float ex. -121.123456 
		dist - as integer 
		alt - as integer
		course as degree - as integer , range -180 to 180 
	*/
	serial_output("$A,");
	serial_send_coord(lat_gps.WW);
	serial_output(",");
	serial_send_coord(long_gps.WW);

	serial_output(",%i,%i,%i,%i,%i,%i,%li,%li,\r\n",
		(int)svs,
		dist_to_home,
		IMUlocationz._.W1,		
		(int)(ground_speed_3DIMU/51),  // OSD expects speed in knots !!  
		azimuth,			// we could also put here angle to goal
		azimuth,
		date,
		time
	);

#if (OSD_LOC_REMZIBI_DEBUG != OSD_LOC_DISABLED)
	serial_send_location(OSD_LOC_REMZIBI_DEBUG);
	serial_output(",,%li %li %i %i,\r\n", lat_gps.WW, long_gps.WW, dist_to_home, azimuth);
#endif

#if (OSD_LOC_AP_MODE != OSD_LOC_DISABLED)
	serial_send_location(OSD_LOC_AP_MODE);
	//serial_output("$M,131,4,");
	serial_send_string((char*)mp_mode_name[mp_mode], 0, 0);
#endif

#if (OSD_LOC_DIST_TO_GOAL != OSD_LOC_DISABLED)
	serial_send_location(OSD_LOC_DIST_TO_GOAL);
	if (mp_mode >= MODE_WAYPOINT)
	{
		serial_send_int(dist_to_goal, 0, 0x97);
	} 
	else
	{
		serial_send_string("     ", 0, 0);
	}
#endif

	// save max_values
	if (max_speed < ground_speed_3DIMU)
	{
		max_speed = ground_speed_3DIMU;
	}

	if (max_height < IMUlocationz._.W1)
	{
		max_height = IMUlocationz._.W1;
	}

	if (max_dist < dist_to_home)
	{
		max_dist = dist_to_home;
	}

	// called every 0.25 sec
	// speed in cm/s
	// dist is stored in dm (0.1m = 10cm)
	if (flight_mode == PLANE_IN_FLIGHT)
	{
		distance += ground_speed_3DIMU / 40;
	}
}

void get_mp_mode()
{
	if (!home_saved)
		mp_mode =  MODE_UNDEFINED;
	else if (!flags._.pitch_feedback)
		mp_mode =  MODE_MANUAL;
	else if (!flags._.GPS_steering)
		mp_mode =  MODE_STABLE;
	else if (udb_flags._.radio_on && !flags._.rtl_hold)
		mp_mode =  MODE_WAYPOINT;
	else if (flags._.rtl_hold && udb_flags._.radio_on)
		mp_mode =  MODE_RTH_HOLD;						// H : RTL Hold, has signal
	else if (!udb_flags._.radio_on)
		mp_mode =  MODE_RTH;
	else
		mp_mode =  MODE_UNKNOWN; // Unknown
}

static void update_flight_time()
{
#if (OSD_LOC_FLIGHT_TIME != OSD_LOC_DISABLED)
	serial_send_location(OSD_LOC_FLIGHT_TIME);
	serial_output("232,,");
	int mm = (in_flight_counter / 2) / 60;
	int ss = (in_flight_counter / 2) % 60;
	serial_output("%02i:%02i,\r\n", 
		mm,
		ss
	);
#endif


#if (OSD_LOC_DISTANCE != OSD_LOC_DISABLED)
	serial_send_location(OSD_LOC_DISTANCE);

	#if OSD_USE_METRIC_UNITS
		serial_send_long(distance / 10, 0xA8, 0xB1);
	#else
		long dist = 33 * distance;
		serial_send_long(dist / 100, 0xA8, 0xAA);
	#endif

#endif

#if (OSD_LOC_OSD_LOC_WP_NO != OSD_LOC_DISABLED)
	serial_send_location(OSD_LOC_WP_NO);
	if (mp_mode >= MODE_WAYPOINT)
	{
		serial_send_int(waypointIndex, 0, 0);
	} 
	else
	{
		serial_send_string("  ", 0, 0);
	}
#endif
}

void serial_show_AH()
{
#if OSD_SHOW_HORIZON
	struct relative2D matrix_accum ;
	long earth_pitch ;		// pitch in binary angles ( 0-255 is 360 degreres)
	long earth_roll ;		// roll of the plane with respect to earth frame
	//  Roll
	//  Earth Frame of Reference
	matrix_accum.x = rmat[8] ;
	matrix_accum.y = rmat[6] ;
	earth_roll = rect_to_polar(&matrix_accum) ;					// binary angle (0 - 256 = 360 degrees)
	earth_roll = (-earth_roll * BYTECIR_TO_DEGREE) >> 16 ;		// switch polarity, convert to -180 - 180 degrees
	earth_roll >>= 1;

#if OSD_HORIZON_ROLL_REVERSED
	earth_roll = -earth_roll;
#endif
	
	//  Pitch
	//  Earth Frame of Reference
	//  Note that we are using the matrix_accum.x
	//  left over from previous rect_to_polar in this calculation.
	//  so this Pitch calculation must follow the Roll calculation
	matrix_accum.y = rmat[7] ;
	earth_pitch = rect_to_polar(&matrix_accum) ;				// binary angle (0 - 256 = 360 degrees)
	earth_pitch = (-earth_pitch * BYTECIR_TO_DEGREE) >> 16 ;	// switch polarity, convert to -180 - 180 degrees
	earth_pitch >>= 1;

#if OSD_HORIZON_PITCH_REVERSED
	earth_pitch = -earth_pitch;
#endif

	/*
		Artificial Horizon data should be look like that :
		
		$I,roll,pitch,<CRLF>   
		
		ex .  $I,23,-112,CRLF          CRLF -are two bytes termination of line (dec 13 10) (hex 0D 0A) 
		Support graphical artificial horizon and pitch presentation , roll and pitch as integer type as degrees (-180,180)
	*/
	serial_output("$I,%li,%li,\r\n", earth_roll, earth_pitch) ;

#endif
}

void init_sequence()
{
static int init_counter = -1;

	if (init_counter == -1)
	{
		init_counter = 0;
		serial_output("$CLS\r\n");
	}

	if (init_counter == 2)
	{
		update_coords();
	}

	if (init_counter == 6)
	{
		serial_output("$CLS\r\n");
	}

	if (init_counter == 10)
	{
		update_coords();
	}

	if (init_counter == 14)
	{
		serial_output("$CLS\r\n");
		/*
			Save Home command
			$SH<CRLF>
		*/
		serial_output("$SH\r\n");
		home_saved = true;
		telemetry_counter = 0;	// used to run initial cls
	}

	++init_counter;
}

void update_in_flight()
{
static int counter = 0;
/* called every 0.5 sec */
	/*
	simple state machine
		flight_mode = PLANE_ON_GROUND -> if moved 7 meters and throttle > 50% -> PLANE_IN_FLIGHT
	*/
	long lat = lat_gps.WW >> 6;		// cut off unecessary digits, it's about 7 meters
	long log = lat_gps.WW >> 6;

	int throttleIn = udb_pwIn[THROTTLE_INPUT_CHANNEL] ;

	if (flight_mode == PLANE_ON_GROUND)	// we are on ground before flight
	{				// we need 2 secs of movement to decide in flight
		if (last_long != log && last_lat != lat)	// we are moving 
		{
			if (throttleIn < OSD_REMZIBI_MID_THROTTLE)					// but without throttle
			{
				last_long = log;						// save
				last_lat = lat;
			}
			else									// with throttle so we are flying
			{
				flight_mode = PLANE_IN_FLIGHT;
			}
		}
	}
	else if (flight_mode == PLANE_IN_FLIGHT)
	{
		++in_flight_counter;

		if (last_long != log && last_lat != lat)	// we are moving 
		{
			last_long = log;						// save
			last_lat = lat;
			counter = 0;
		}
		else
		{
			counter++;
		}

		if (counter > 20 && throttleIn < OSD_REMZIBI_MIN_THROTTLE)		// no location change for 10 seconds and throttle low
		{
			on_ground_cnt = 0;
			in_flight_counter -= 20;
			flight_mode = PLANE_LANDED;
			serial_output("$CLS\r\n");			// clear AH
		}
	}
	else
	{
		++on_ground_cnt;	// counter for maxes
	}
}					

void serial_output_8hz( void )
{
	if (home_saved)
	{
		if (flight_mode == PLANE_IN_FLIGHT)
		{
			serial_show_AH();
		}

		if (telemetry_counter & 1)
		{
			update_coords();
		}

		if (telemetry_counter % 4 == 0)
		{
			get_mp_mode();

			update_in_flight();		
		}

		if (telemetry_counter % 8 == 0)
		{
			update_flight_time();
		}
	}
	else
	{
		if (gps_nav_valid())
		{
			init_sequence();
		}

		serial_output("$M,11,8,,,MATRIXPILOT,\r\n");		
		serial_output("$M,136,9,,,WAITING FOR GPS,\r\n");	
	}
	
	if (telemetry_counter == 24 || telemetry_counter % (OSD_REMZIBI_CLS_TIME * 8) == 0)	// 3 secs after home save or about every OSD_REMZIBI_CLS_TIME secs
	{
		serial_output("$CLS\r\n");
	}

	if (on_ground_cnt > (OSD_REMZIBI_SUMMARY_DELAY * 2))	// seconds * 2 ticks per second
	{
		// flight summary
		serial_output("$M,2,7,,,MAX,\r\n");
		serial_output("$M,130,8,167,177,%i,\r\n", max_dist);
		serial_output("$M,130,9,166,177,%i,\r\n", max_height);
#if OSD_USE_METRIC_UNITS
		serial_output("$M,130,10,168,222,%i,\r\n", max_speed /28);
		serial_output("$M,130,11,168,177,%i,\r\n", distance / 10);
#else
		serial_output("$M,130,10,168,223,%i,\r\n", max_speed / 51);
		serial_output("$M,130,11,168,170,%i,\r\n", (distance * 33) / 100);
#endif

		int mm = (in_flight_counter / 2) / 60;
		int ss = (in_flight_counter / 2) % 60;
		serial_output("$M,130,12,232,,%02i:%02i,\r\n", 
			mm,
			ss
		);
	}

	++telemetry_counter;

	return ;
}



#endif
