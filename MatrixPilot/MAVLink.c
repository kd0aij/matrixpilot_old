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




// The Coordiante Frame and Dimensional Units of Mavlink are
// explained in detail at this web URL:-
// http://pixhawk.ethz.ch/wiki/software/coordinate_frame
// An abreviated summary is:
// Mavlink Aviation  X Axis is the UDB Aviation Y axis which is the fuselage axis.
// Mavlink Avitation Y axis is out of the right wing, and so is the negative of the UDB X Axis
// Mavlink Aviation  Z axis is downward from the plane, ans so is the same as UDB Z axis.
// Mavlink Yaw is positive to the right (same as UDB)
// Pitch is positive when the front of the plane pitches up from horizontal (opposite of UDB)
// Roll is possitive to the right of the plane (same as UDB)
// So angles follow the "right hand rule"

#include <string.h>
#include "defines.h"
#include "options.h"
#include "../libDCM/libDCM_internal.h" // Needed for access to internal DCM value
#include "../MAVLink/include/matrixpilot_mavlink_bridge_header.h"
#include "../MAVLink/include/common/mavlink.h"


#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)

#define 	SERIAL_BUFFER_SIZE 	MAVLINK_MAX_PACKET_LEN
#define 	BYTE_CIR_16_TO_RAD  ((2.0 * 3.14159265) / 65536.0 ) // Conveert 16 bit byte circular to radians

//void (* sio_parse ) ( unsigned char inchar ) = &sio_newMsg ;
void mavlink_msg_recv(unsigned char);
void (* sio_parse ) ( unsigned char inchar ) = &mavlink_msg_recv ;

union intbb voltage_milis = {0} ;
int skip = 0 ;
uint64_t usec = 0 ;			// A measure of time

int sb_index = 0 ;
int end_index = 0 ;
unsigned char serial_buffer[SERIAL_BUFFER_SIZE] ;

float previous_earth_pitch  = 0.0 ;
float previous_earth_roll   = 0.0 ;
float previous_earth_yaw    = 0.0 ;


#if (  SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )

mavlink_message_t msg;
mavlink_status_t  r_mavlink_status;

uint8_t   mavlink_debug[] = "Parsed a message\n" ; 
uint16_t  mavlink_debug_len = 17 ;

void uart1_send(uint8_t buf[], uint16_t len) ;

void mavlink_msg_recv( unsigned char inchar )
{
	if (mavlink_parse_char(0, inchar, &msg, &r_mavlink_status ))
    {
		uart1_send( mavlink_debug, mavlink_debug_len ) ;
		// Note: serial_output chews up a lof RAM because inserts vsnprintf() library function
		//serial_output("Received message with ID %d, sequence: %d from component %d of system %d\n\n"); //,
		// msg.msgid, msg.seq, msg.compid, msg.sysid);
	}
}

#else

void mavlink_msg_recv( unsigned char inchar )
{
	return;  // Do nothing with the character
}

#endif	// ( SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )


void init_serial()
{
#if ( SERIAL_OUTPUT_FORMAT == SERIAL_OSD_REMZIBI )
dcm_flags._.nmea_passthrough = 1;
#endif

udb_serial_set_rate(19200) ;
//	udb_serial_set_rate(38400) ;
//	udb_serial_set_rate(57600) ;
//	udb_serial_set_rate(115200) ;
//	udb_serial_set_rate(230400) ;
//	udb_serial_set_rate(460800) ;
//	udb_serial_set_rate(921600) ; // yes, it really will work at this rate

return ;
}


////////////////////////////////////////////////////////////////////////////////
// 
// Receive Serial Commands
//

void udb_serial_callback_received_char(char rxchar)
{
	(* sio_parse) ( rxchar ) ; // parse the input byte
	return ;
}

int udb_serial_callback_get_char_to_send(void) 
// routine returns an integer so as to allow sending binary code (including 0x00) over serial
{ 
	if ( sb_index < end_index && sb_index < SERIAL_BUFFER_SIZE ) // ensure never end up racing thru memory.
	{
		unsigned char txchar = serial_buffer[ sb_index++ ] ;
		return (int) txchar ;
	}
	else
	{
		sb_index = 0 ;
		end_index = 0 ;
	}
	
	return -1 ;
}


void uart1_send(uint8_t buf[], uint16_t len)
// len is the number of bytes in the buffer
{
	int start_index = end_index ;
	int remaining = SERIAL_BUFFER_SIZE - start_index ;
	if ( len > remaining )
	{
		//length = remaining ;
		len = remaining ;
	}
	if (remaining > 1)
	{
		memcpy(&serial_buffer[start_index], buf, len);
		end_index = start_index + len ;
	}	
	if (sb_index == 0)
	{
		udb_serial_start_sending();
	}
	return ;
}

void uart1_transmit(uint8_t ch) 
{
	uart1_send(&ch, 1);
}


void serial_output_8hz( void )
{

	struct relative2D matrix_accum ;
	float earth_pitch ;		// pitch in binary angles with respect to earth ( 0-255 is 360 degreres)
	float earth_roll ;		// roll of the plane with respect to earth frame
	float earth_yaw ;		// yaw with respect to earth frame
	int accum ;
	long accum_long ;
	uint8_t mode; ///< System mode, see MAV_MODE ENUM in mavlink/include/mavlink_types.h

	//if (++skip == 2) // Be careful about changing. There is frequency sensitve code below.
	{
		skip = 0;
		usec++ ;

		mavlink_system.sysid = 100; // System ID, 1-255
		mavlink_system.compid = 50; // Component/Subsystem ID, 1-255
		
		// HEARTBEAT
		mavlink_msg_heartbeat_send(MAVLINK_COMM_0, MAV_FIXED_WING, MAV_AUTOPILOT_ARDUPILOTMEGA) ;

		// SYSTEM STATUS
		if (flags._.GPS_steering == 0 && flags._.pitch_feedback == 0)
				 mode = MAV_MODE_MANUAL ;
		else if (flags._.GPS_steering == 0 && flags._.pitch_feedback == 1) 
				 mode = MAV_MODE_GUIDED ;
		else if (flags._.GPS_steering == 1 && flags._.pitch_feedback == 1 && udb_flags._.radio_on == 1)
				 mode = MAV_MODE_AUTO ;
		else if (flags._.GPS_steering == 1 && flags._.pitch_feedback == 1 && udb_flags._.radio_on == 0)
				 mode = MAV_MODE_TEST1 ; // Return to Landing (lost contact with transmitter)
		else
				 mode = MAV_MODE_TEST1 ; // Unknown state 

		mavlink_msg_sys_status_send(MAVLINK_COMM_0, mode, MAV_NAV_WAYPOINT, MAV_STATE_ACTIVE, 
			( uint16_t) 1000 , 	// (uint16_t) (udb_cpu_load()) * 10, 
			(uint16_t)  10000,  // Battery voltage in mV
			(uint8_t)   0,      // 0 Motor free to turn off, 1 Motor Blocked from turning on
			(uint16_t)  0) ;    // Packet Loss in uplink, 0 Until MatrixPilot supports uplink.
		
		// RC CHANNELS
		// Channel values shifted left by 1, to divide by two, so values reflect PWM pulses in microseconds.
		// mavlink_msg_rc_channels_raw_send(mavlink_channel_t chan, uint16_t chan1_raw, uint16_t chan2_raw,
		//    uint16_t chan3_raw, uint16_t chan4_raw, uint16_t chan5_raw, uint16_t chan6_raw, uint16_t chan7_raw,
		//    uint16_t chan8_raw, uint8_t rssi)
 		mavlink_msg_rc_channels_raw_send(MAVLINK_COMM_0,(uint16_t)(udb_pwOut[0]>>1),  (uint16_t) (udb_pwOut[1]>>1), 
			 (uint16_t) (udb_pwOut[2]>>1), (uint16_t) (udb_pwOut[3]>>1), (uint16_t) (udb_pwOut[4]>>1),
			 (uint16_t) (udb_pwOut[5]>>1), (uint16_t)                 0,                 (uint16_t) 0, 
			 (uint8_t) 0); // last item, RSSI currently not measured on UDB.
	
		// ATTITUDE
		//  Roll: Earth Frame of Reference
		matrix_accum.x = rmat[8] ;
		matrix_accum.y = rmat[6] ;
		accum = rect_to_polar16(&matrix_accum) ;			// binary angle (0 to 65536 = 360 degrees)
		earth_roll = ( - accum ) * BYTE_CIR_16_TO_RAD ;		// Convert to Radians
		
		//  Pitch: Earth Frame of Reference
		//  Note that we are using the matrix_accum.x
		//  left over from previous rect_to_polar in this calculation.
		//  so this Pitch calculation must follow the Roll calculation
		matrix_accum.y = rmat[7] ;
		accum = rect_to_polar16(&matrix_accum) ;			// binary angle (0 to 65536 = 360 degrees)
		earth_pitch = ( accum) * BYTE_CIR_16_TO_RAD ;		// Convert to Radians
		
		// Yaw: Earth Frame of Reference
		
		matrix_accum.x = rmat[4] ;
		matrix_accum.y = rmat[1] ;
		accum = rect_to_polar16(&matrix_accum) ;			// binary angle (0 to 65536 = 360 degrees)
		earth_yaw = ( - accum * BYTE_CIR_16_TO_RAD) ;			// Convert to Radians

		mavlink_msg_attitude_send(MAVLINK_COMM_0,usec, earth_roll, earth_pitch, earth_yaw, 
				(earth_roll - previous_earth_roll)     * 8 , // Note: This is Time / Frequency sensitive Code
				(earth_pitch - previous_earth_pitch)   * 8 , // Muliply by 4, to have radians / sec 
                (earth_yaw - previous_earth_yaw)       * 8 ) ;

		// RAW SENSORS - ACCELOREMETERS and GYROS
		// The values sent are raw with no offsets, scaling, and sign correction
		// It is expected that these values are graphed to allow users to check basic sensor operation,
		// and to graph noise on the signals.
#if ( MAG_YAW_DRIFT == 1 )
		
		extern int magFieldRaw[] ;
		mavlink_msg_raw_imu_send(MAVLINK_COMM_0, usec,
				 (int16_t)   udb_yaccel.input,
				 (int16_t) - udb_xaccel.input, (int16_t) udb_zaccel.input, 
				 (int16_t)   ( udb_yrate.input + 32768 ),
                 (int16_t) - ( udb_xrate.input + 32768 ),
                 (int16_t)   ( udb_zrate.input + 32768 ), 
				  (int16_t) magFieldRaw[0], (int16_t) magFieldRaw[1], (int16_t) magFieldRaw[2]) ;
#else
		mavlink_msg_raw_imu_send(MAVLINK_COMM_0, usec,
				      udb_yaccel.input, - udb_xaccel.input, udb_zaccel.input,
				    ( udb_yrate.input + 32768 ), - ( udb_xrate.input + 32768 ), ( udb_zrate.input + 32768 ), 
				      0, 0, 0) ; // MagFieldRaw[] zero as mag not connected.
#endif
		// GLOBAL POSITION - derived from fused sensors 
		float lat_float, lon_float, alt_float = 0.0 ;
		accum_long = IMUlocationy._.W1 + ( lat_origin.WW / 90 ) ; //  meters North from Equator
		lat_float  =  ( accum_long * 90 ) / 10000000.0 ;          // degrees North from Equator 
		lon_float =   (long_origin.WW  + ((( IMUlocationx._.W1 * 90 )) / ( float )( cos_lat / 16384.0 ))) / 10000000.0 ;
		alt_float = (float) (((((int) (IMUlocationz._.W1)) * 100) + alt_origin._.W0)) / 100.0 ;
		mavlink_msg_global_position_send(MAVLINK_COMM_0, usec, 
			lat_float , lon_float, alt_float ,
			(float) IMUvelocityx._.W1, (float) IMUvelocityy._.W1, (float) IMUvelocityz._.W1 ) ; // meters per second
	}
	return ;
}




#endif  // ( SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK )
