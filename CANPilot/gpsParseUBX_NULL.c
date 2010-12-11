// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009, 2010 MatrixPilot Team
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


#include "../libDCM/libDCM_internal.h"
#include "../libCAN/libCAN.h"


#if ( GPS_TYPE == GPS_UBX_2HZ || GPS_TYPE == GPS_UBX_4HZ )

//	Parse the GPS messages, using the binary interface.
//	The parser uses a state machine implemented via a pointer to a function.
//	Binary values received from the GPS are directed to program variables via a table
//	of pointers to the variable locations.
//	Unions of structures are used to be able to access the variables as long, ints, or bytes.


union intbb payloadlength ;
union intbb checksum;
unsigned int msg_class;
unsigned int msg_id;
unsigned int ack_class;
unsigned int ack_id;
unsigned int ack_type;
unsigned char CK_A;
unsigned char CK_B;


#if ( HILSIM == 1 )
	void msg_BODYRATES( unsigned char inchar ) ;
#endif

void msg_MSGU( unsigned char inchar ) ;

void msg_ACK_CLASS( unsigned char inchar );
void msg_ACK_ID( unsigned char inchar );

// void bin_out( char outchar );

const unsigned int  set_rate_length = 14 ;
const unsigned int  enable_NAV_SOL_length = 16 ;
const unsigned int  enable_NAV_POSLLH_length = 16 ;
const unsigned int  enable_NAV_VELNED_length = 16 ;
const unsigned int  enable_NAV_DOP_length = 16 ;
const unsigned int  enable_UBX_only_length = 28;
const unsigned int  enable_SBAS_length = 16;
const unsigned int  config_NAV5_length = 44;


unsigned char un ;

union longbbbb 	xpg_ , ypg_ , zpg_ ;
union longbbbb  xvg_ , yvg_ , zvg_ ;
unsigned char  	mode1_ , mode2_ , svs_, nav_valid_ ;
union longbbbb 	lat_gps_ , long_gps_ , alt_sl_gps_ ;
union longbbbb  sog_gps_ , cog_gps_ , climb_gps_ , tow_ ;
union intbb   	hdop_ , week_no_ ;

#if ( HILSIM == 1 )
	union intbb		u_dot_sim_, v_dot_sim_, w_dot_sim_ ;
	union intbb		u_dot_sim, v_dot_sim, w_dot_sim ;
	union intbb		p_sim_, q_sim_, r_sim_ ;
	union intbb		p_sim, q_sim, r_sim ;
	

#endif

unsigned char svsmin = 24 ;
unsigned char svsmax = 0 ;


void gps_startup_sequence(int gpscount)
{
	return ;
}


boolean gps_nav_valid(void)
{
	return IMU_gps_nav_valid();
}


//	The parsing routines follow. Each routine is named for the state in which the routine is applied.
//	States correspond to the portions of the binary messages.
//	For example, msg_B3 is the routine that is applied to the byte received after a B3 is received.
//	If an A0 is received, the state machine transitions to the A0 state.

void nmea_passthru ( unsigned char gpschar)
{
	return;
}



int frame_errors = 0 ;

void commit_gps_data(void) 
{
	return ;
}



#endif

