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




// The Coordinate Frame and Dimensional Units of Mavlink are
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
#include "gain_variables.h"
#include "../libDCM/libDCM_internal.h" // Needed for access to internal DCM value
#include "../MAVLink/include/matrixpilot_mavlink_bridge_header.h"
#include "../MAVLink/include/common/mavlink.h"



#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)

#define 	SERIAL_BUFFER_SIZE 	MAVLINK_MAX_PACKET_LEN
#define 	BYTE_CIR_16_TO_RAD  ((2.0 * 3.14159265) / 65536.0 ) // Conveert 16 bit byte circular to radians
#define 	MAVLINK_FRAME_FREQUENCY	40

//void (* sio_parse ) ( unsigned char inchar ) = &sio_newMsg ;
void mavlink_msg_recv(unsigned char);
void (* sio_parse ) ( unsigned char inchar ) = &mavlink_msg_recv ;
void send_text(uint8_t text[]) ;
void handleMessage(mavlink_message_t* msg) ;
boolean is_this_the_moment_to_send( unsigned char counter, unsigned char max_counter ) ;
boolean mavlink_frequency_send( unsigned char transmit_frequency, unsigned char counter) ;

union intbb voltage_milis = {0} ;
unsigned char counter_40hz = 0 ;
uint64_t usec = 0 ;			// A measure of time in microseconds (should be from Unix Epoch).

int sb_index = 0 ;
int end_index = 0 ;
unsigned char serial_buffer[SERIAL_BUFFER_SIZE] ;

float previous_earth_pitch  = 0.0 ;
float previous_earth_roll   = 0.0 ;
float previous_earth_yaw    = 0.0 ;

unsigned char streamRateRawSensors      = 0 ;
unsigned char streamRateRCChannels      = 0 ;

#if (  SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )
unsigned char send_variables_counter = 0;
extern unsigned int maxstack ;
mavlink_message_t msg ;
mavlink_status_t  r_mavlink_status ;

// unsigned char streamRateExtendedStatus  = 0 ; 
// unsigned char streamRateRawController   = 0 ;
// unsigned char streamRateRawSensorFusion = 0 ;
// unsigned char streamRatePosition        = 0 ;
// unsigned char streamRateExtra1          = 0 ;
// unsigned char streamRateExtra2          = 0 ; 
// unsigned char streamRateExtra3          = 0 ;

uint8_t   mavlink_debug[] = "Parsed a message\r\n" ; 
uint16_t  mavlink_debug_len = 18 ;

void uart1_send(uint8_t buf[], uint16_t len) ;

void mavlink_msg_recv( unsigned char inchar )
{
	if (mavlink_parse_char(0, inchar, &msg, &r_mavlink_status ))
    {
		uart1_send( mavlink_debug, mavlink_debug_len ) ;
		handleMessage(&msg) ;
	}
	return ;
}

// Portions of the following code (handlesmessage())are templated off source code written by James Goppert for the
// ArdupilotMega, and are used by his kind permission and also in accordance with the GPS V3 licensing
// of that code.

void handleMessage(mavlink_message_t* msg)
{
	send_text( (unsigned char*) "Handling message ID ..");
	uart1_transmit(( msg->msgid >> 4 ) + 0x30 ) ;
	uart1_transmit(( msg->msgid & 0x0f ) + 0x30 ) ;
	send_text( (unsigned char*) "\r\n");

	switch (msg->msgid)	
	{
	    case MAVLINK_MSG_ID_REQUEST_DATA_STREAM:  
	    {
	        // decode
	        mavlink_request_data_stream_t packet;
	        mavlink_msg_request_data_stream_decode(msg, &packet);
			send_text((unsigned char*) "Action: Request data stream\r\n");
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        int freq = 0; // packet frequency
	
	        if (packet.start_stop == 0) freq = 0; // stop sending
	        else if (packet.start_stop == 1) freq = packet.req_message_rate; // start sending
	        else break;
	
	        switch(packet.req_stream_id)
	        {
	        case MAV_DATA_STREAM_ALL:
	            streamRateRawSensors = freq ; 
	            // streamRateExtendedStatus = freq; 
	            streamRateRCChannels = freq; 
	            // streamRateRawController = freq; 
	            // streamRateRawSensorFusion = freq; 
	            // streamRatePosition = freq; 
	            // streamRateExtra1 = freq; 
	            // streamRateExtra2 = freq; 
	            // streamRateExtra3 = freq; 
	            break;
	        case MAV_DATA_STREAM_RAW_SENSORS:
				send_text((unsigned char*) "Action: Request Raw Sensors\r\n");
	            streamRateRawSensors = freq ;  
	            break;
	        case MAV_DATA_STREAM_EXTENDED_STATUS:
	            // streamRateExtendedStatus = freq; 
	            break;
	        case MAV_DATA_STREAM_RC_CHANNELS:
	            streamRateRCChannels = freq; 
	            break;
	        case MAV_DATA_STREAM_RAW_CONTROLLER:
	            // streamRateRawController = freq; 
	            break;
	        case MAV_DATA_STREAM_RAW_SENSOR_FUSION:
	            // streamRateRawSensorFusion = freq; 
	            break;
	        case MAV_DATA_STREAM_POSITION:
	            // streamRatePosition = freq; 
	            break;
	        case MAV_DATA_STREAM_EXTRA1:
	            // streamRateExtra1 = freq; 
	            break;
	        case MAV_DATA_STREAM_EXTRA2:
	            // streamRateExtra2 = freq; 
	            break;
	        case MAV_DATA_STREAM_EXTRA3:
	            // streamRateExtra3 = freq; 
	            break;
	        default:
	            break;
	        }
	    }
	    case MAVLINK_MSG_ID_ACTION:
	    {
			send_text((unsigned char*) "Action: Specific Action Required\r\n");
	        // decode
	        mavlink_action_t packet;
	        mavlink_msg_action_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target,packet.target_component)) break;
			
	        switch(packet.action)
	        {
	
	            case MAV_ACTION_LAUNCH:
					send_text((unsigned char*) "Action: Launch !\r\n");
	                //set_mode(TAKEOFF);
						
	                break;
	
	            case MAV_ACTION_RETURN:
					send_text((unsigned char*) "Action: Return !\r\n");
	                //set_mode(RTL);
	                break;
	
	            case MAV_ACTION_EMCY_LAND:
					send_text((unsigned char*) "Action: Emergency Land !\r\n");
	                //set_mode(LAND);
	                break;
	
	            case MAV_ACTION_HALT: 
					send_text((unsigned char*) "Action: Halt !\r\n");
	                //loiter_at_location();
	                break;
	
	            // can't implement due to APM configuration
	            // just setting to manual to be safe
	            case MAV_ACTION_MOTORS_START:
	            case MAV_ACTION_CONFIRM_KILL:
	            case MAV_ACTION_EMCY_KILL:
	            case MAV_ACTION_MOTORS_STOP:
	            case MAV_ACTION_SHUTDOWN: 
	                //set_mode(MANUAL);
	                break;
	
	            case MAV_ACTION_CONTINUE:
	                //process_next_command();
	                break;
	
	            case MAV_ACTION_SET_MANUAL: 
	                //set_mode(MANUAL);
	                break;
	
	            case MAV_ACTION_SET_AUTO:
	                //set_mode(AUTO);
	                break; 
	
	            case MAV_ACTION_STORAGE_READ:
					send_text((unsigned char*) "Action: Storage Read\r\n");
					// udb_flags._.mavlink_send_variables = 1 ;
	                break; 
	
	            case MAV_ACTION_STORAGE_WRITE:
					send_text((unsigned char*) "Action: Storage Write\r\n");
	                break;
	
	            case MAV_ACTION_CALIBRATE_RC:
					send_text((unsigned char*) "Action: Calibrate RC\r\n"); 
	                break;
	            
	            case MAV_ACTION_CALIBRATE_GYRO:
	            case MAV_ACTION_CALIBRATE_MAG: 
	            case MAV_ACTION_CALIBRATE_ACC: 
	            case MAV_ACTION_CALIBRATE_PRESSURE:
	            case MAV_ACTION_REBOOT: 
	                //startup_IMU_ground();     
	                break; 
	
	            case MAV_ACTION_REC_START: break; 
	            case MAV_ACTION_REC_PAUSE: break; 
	            case MAV_ACTION_REC_STOP: break; 
	
	            case MAV_ACTION_TAKEOFF:
					send_text((unsigned char*) "Action: Take Off !\r\n");
	                //set_mode(TAKEOFF);
	                break; 
	
	            case MAV_ACTION_NAVIGATE:
					send_text((unsigned char*) "Action: Navigate !\r\n");
	                //set_mode(AUTO);
	                break; 
	
	            case MAV_ACTION_LAND:
	                //set_mode(LAND);
	                break; 
	
	            case MAV_ACTION_LOITER:
	                //set_mode(LOITER);
	                break; 
	
	            default: break;
	        }
	    }
	    break;
	
	    case MAVLINK_MSG_ID_WAYPOINT_REQUEST_LIST:
	    {
			send_text((unsigned char*) "waypoint request list\r\n");
	
	        // decode
	        //mavlink_waypoint_request_list_t packet;
	        //mavlink_msg_waypoint_request_list_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // Start sending waypoints
	        //mavlink_msg_waypoint_count_send(chan,msg->sysid,
	                                        //msg->compid,get(PARAM_WP_TOTAL));
	        //global_data.waypoint_timelast_send = millis();
	        //global_data.waypoint_sending = true;
	        //global_data.waypoint_receiving = false;
	        //global_data.waypoint_dest_sysid = msg->sysid;
	        //global_data.waypoint_dest_compid = msg->compid;
	
	    }
	    break;
	
	    case MAVLINK_MSG_ID_WAYPOINT_REQUEST:
	    {
			send_text((unsigned char*)"waypoint request\r\n");
	
	        // Check if sending waypiont
	        //if (!global_data.waypoint_sending) break;
	
	        // decode
	        //mavlink_waypoint_request_t packet;
	        //mavlink_msg_waypoint_request_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // send waypoint
	        //tell_command = get_wp_with_index(packet.seq);
	
	        // set frame of waypoint
	        //uint8_t frame = MAV_FRAME_GLOBAL; // reference frame 
	        //uint8_t action = MAV_ACTION_NAVIGATE; // action
	        //uint8_t orbit_direction = 0; // clockwise(0), counter-clockwise(1)
	        //float orbit = 0; // loiter radius
	        //float param1 = 0, param2 = 0;
	
	        //switch(tell_command.id)
	        //{
	
	        //case CMD_WAYPOINT: // navigate
	            //action = MAV_ACTION_NAVIGATE; // action
	            //break;
	
	       // case CMD_LOITER_TIME: // loiter
	            //orbit = get(PARAM_WP_RADIUS); // XXX setting loiter radius as waypoint acceptance radius
	            //action = MAV_ACTION_LOITER; // action
	            //param1 = get(PARAM_WP_RADIUS);
	            //param2 = tell_command.p1*100; // loiter time
	            //break;
	
	       // case CMD_TAKEOFF: // takeoff
	            //action = MAV_ACTION_TAKEOFF;
	            //break;
	
	        //case CMD_LAND: // land
	            //action = MAV_ACTION_LAND;
	            //break; 
	
	        //defaut:
				//gcs.send_text("command not handled");
	            //break;
	        //}
	
	        // time that the mav should loiter in milliseconds
	        //uint8_t current = 0; // 1 (true), 0 (false)
	        //if (packet.seq == get(PARAM_WP_INDEX)) current = 1;
	        //float yaw_dir = 0; // yaw orientation in radians, 0 = north XXX: what does this do?
	        //uint8_t autocontinue = 1; // 1 (true), 0 (false)
	        //float x = tell_command.lng/1.0e7; // local (x), global (longitude)
	        //float y = tell_command.lat/1.0e7; // local (y), global (latitude)
	        //float z = tell_command.alt/1.0e2; // local (z), global (altitude)
	        // note XXX: documented x,y,z order does not match with gps raw
	        //mavlink_msg_waypoint_send(chan,msg->sysid,
	                                  //msg->compid,packet.seq,frame,action,
	                                  //orbit,orbit_direction,param1,param2,current,x,y,z,yaw_dir,autocontinue);
	
	        // update last waypoint comm stamp
	        //global_data.waypoint_timelast_send = millis();
	    }
	    break;
	
	    case MAVLINK_MSG_ID_WAYPOINT_ACK:
	    {
			send_text((unsigned char*)"waypoint ack\r\n");
	
	        // decode
	        //mavlink_waypoint_ack_t packet;
	        //mavlink_msg_waypoint_ack_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // check for error
	        //uint8_t type = packet.type; // ok (0), error(1)
	
	        // turn off waypoint send
	        //global_data.waypoint_sending = false;
	    }
	    break;
	
	    case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
	    {
			send_text((unsigned char*)"param request list\r\n");
	
	        // decode
	        //mavlink_param_request_list_t packet;
	        //mavlink_msg_param_request_list_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // Start sending parameters
	        udb_flags._.mavlink_send_variables = 1 ;
	    }
	    break;
	
	    case MAVLINK_MSG_ID_WAYPOINT_CLEAR_ALL:
	    {
			send_text((unsigned char*)"waypoint clear all\r\n");
	
	        // decode
	        //mavlink_waypoint_clear_all_t packet;
	        //mavlink_msg_waypoint_clear_all_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // clear all waypoints
	        //uint8_t type = 0; // ok (0), error(1)
	        //set(PARAM_WP_TOTAL,0);
	
	        // send acknowledgement 3 times to makes sure it is received
	        //for (int i=0;i<3;i++) mavlink_msg_waypoint_ack_send(chan,msg->sysid,msg->compid,type);
	
	        break;
	    }
	
	    case MAVLINK_MSG_ID_WAYPOINT_SET_CURRENT:
	    {
			send_text((unsigned char*)"waypoint set current\r\n");
	
	        // decode
	        //mavlink_waypoint_set_current_t packet;
	        //mavlink_msg_waypoint_set_current_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // set current waypoint
	        //set(PARAM_WP_INDEX,packet.seq);
			//{
				//Location temp;	// XXX this is gross
				//temp = get_wp_with_index(packet.seq);
				//set_next_WP(&temp);
			//}
	        //mavlink_msg_waypoint_current_send(chan,get(PARAM_WP_INDEX));
	        break;
	    }
	
	    case MAVLINK_MSG_ID_WAYPOINT_COUNT:
	    {
			send_text((unsigned char*)"waypoint count\r\n");
	
	        // decode
	        //mavlink_waypoint_count_t packet;
	        //mavlink_msg_waypoint_count_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // start waypoint receiving
	        //set(PARAM_WP_TOTAL,packet.count);
	        //if (get(PARAM_WP_TOTAL) > MAX_WAYPOINTS)
	            //set(PARAM_WP_TOTAL,MAX_WAYPOINTS);
	        //global_data.waypoint_timelast_receive = millis();
	        //global_data.waypoint_receiving = true;
	        //global_data.waypoint_sending = false;
	        //global_data.waypoint_request_i = 0;
	        break;
	    }
	
	    case MAVLINK_MSG_ID_WAYPOINT:
	    {
			send_text((unsigned char*)"waypoint\r\n");
	        // Check if receiving waypiont
	        //if (!global_data.waypoint_receiving) break;
	
	        // decode
	        //mavlink_waypoint_t packet;
	        //mavlink_msg_waypoint_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // check if this is the requested waypoint
	        //if (packet.seq != global_data.waypoint_request_i) break;
	
	        // store waypoint
	       // uint8_t loadAction = 0; // 0 insert in list, 1 exec now
	
	        //switch (packet.frame)
	        //{
	            //case MAV_FRAME_GLOBAL:
	            //{
	                //tell_command.lng = 1.0e7*packet.x;
	                //tell_command.lat = 1.0e7*packet.y;
	                //tell_command.alt = packet.z*1.0e2;
	               // break;
	            //}
	
	            //case MAV_FRAME_LOCAL: // local (relative to home position)
	            //{
	                //tell_command.lng = 1.0e7*ToDeg(packet.x/
	                        //(radius_of_earth*cos(ToRad(home.lat/1.0e7)))) + home.lng;
	                //tell_command.lat = 1.0e7*ToDeg(packet.y/radius_of_earth) + home.lat;
	                //tell_command.alt = -packet.z*1.0e2 + home.alt;
	                //break;
	            //}
	        //}
	
	        // defaults
	        //tell_command.id = CMD_BLANK;
	
	       // switch (packet.action)
	        //{
	        
	            //case MAV_ACTION_TAKEOFF:
	            //{
	                //tell_command.id = CMD_TAKEOFF;
	                //break;
	           // } 
	            //case MAV_ACTION_LAND:
	            //{
	                //tell_command.id = CMD_LAND;
	                //break;
	            //}
	
	            //case MAV_ACTION_NAVIGATE:
	            //{
	                //tell_command.id = CMD_WAYPOINT;
	               // break;
	            //}
	
	            //case MAV_ACTION_LOITER:
	            //{
	                //tell_command.id = CMD_LOITER_TIME;
	               // tell_command.p1 = packet.param2/1.0e2;
	               // break;
	            //}
	        //}
	
	        // save waypoint
	        //set_wp_with_index(tell_command, packet.seq);
	
	        // update waypoint receiving state machine
	        //global_data.waypoint_timelast_receive = millis();
	        //global_data.waypoint_request_i++;
	
	        //if (global_data.waypoint_request_i == get(PARAM_WP_TOTAL))
	        //{
				//gcs.send_text("flight plane received");
	            //uint8_t type = 0; // ok (0), error(1)
	            //mavlink_msg_waypoint_ack_send(chan,msg->sysid,msg->compid,type);
	            //global_data.waypoint_receiving = false;
	           	// XXX ignores waypoint radius for individual waypoints, can
				// only set WP_RADIUS parameter
	        //}
	        //break;
	    }
	
	    case MAVLINK_MSG_ID_PARAM_SET:
	    {
	        // decode
			send_text((unsigned char*)"Param Set\r\n");
	        //mavlink_param_set_t packet;
	        //mavlink_msg_param_set_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component))
	            //break;
	
	        // set parameter
	        //const char * key = (const char*) packet.param_id;
	
	        // iterate known parameters
	        // XXX linear search; would be better to sort params & use a binary search
	        //for (uint16_t i = 0; i < global_data.param_count; i++) {
	
	            // compare key with parameter name
	            //if (!strcmp_P(key, getParamName(i))) {
	
	                // sanity-check the new parameter
	                //if (!isnan(packet.param_value) &&						// not nan
						//!isinf(packet.param_value)) {						// not inf
	
	                    //setParamAsFloat(i,packet.param_value);
	
	                    // Report back new value
	                    //char param_name[ONBOARD_PARAM_NAME_LENGTH];			/// XXX HACK
	                    //strcpy_P(param_name, getParamName(i));	/// XXX HACK
	                    //mavlink_msg_param_value_send(chan,
	                                                 //(int8_t*)param_name,
	                                                 //getParamAsFloat(i),
													 //global_data.param_count,i);
						// call load if required
						//if (i >= PARAM_RLL2SRV_P && i <= PARAM_RLL2SRV_IMAX) pidServoRoll.load_gains();
						//if (i >= PARAM_PTCH2SRV_P && i <= PARAM_PTCH2SRV_IMAX) pidServoPitch.load_gains();
						//if (i >= PARAM_YW2SRV_P && i <= PARAM_YW2SRV_IMAX) pidServoRudder.load_gains();
						//if (i >= PARAM_HDNG2RLL_P && i <= PARAM_HDNG2RLL_IMAX) pidNavRoll.load_gains();
						//if (i >= PARAM_ARSPD2PTCH_P && i <= PARAM_ARSPD2PTCH_IMAX) pidNavPitchAirspeed.load_gains();
						//if (i >= PARAM_ALT2PTCH_P && i <= PARAM_ALT2PTCH_IMAX) pidNavPitchAltitude.load_gains();
						//if (i >= PARAM_ENRGY2THR_P && i <= PARAM_ENRGY2THR_IMAX) pidTeThrottle.load_gains();
						//if (i >= PARAM_ALT2THR_P && i <= PARAM_ALT2THR_IMAX) pidAltitudeThrottle.load_gains();
	                //}
	                //break;
	            //}
	        //}
	        //break;
	    } // end case
  	} // end switch
} // end handle mavlink





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

//  udb_serial_set_rate(19200) ;
//	udb_serial_set_rate(38400) ;
	udb_serial_set_rate(57600) ;
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

void send_text(uint8_t text[])
{
	uint16_t index = 0;
	while ( text[index++] != 0 && index < 80)
	{
		; // Do nothing
	}
	uart1_send(text, index - 1) ;
}

void init_mavlink( void )
{
	mavlink_system.sysid = 100 ; // System ID, 1-255
	mavlink_system.compid = 50 ; // Component/Subsystem ID, 1-255
#if ( SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )
	streamRateRCChannels = 0 ;
	streamRateRawSensors = 0 ;
#else 
	streamRateRCChannels = 2 ;
	streamRateRawSensors = 4 ;
#endif
}

const unsigned char mavlink_freq_table[] = { 0,40,20,13,10,8,7,6 } ;

boolean is_this_the_moment_to_send( unsigned char counter, unsigned char max_counter )
{
	if ( counter % max_counter == 0 )
	{
		return true ;
	}
	else
	{
		return false;
	}	
}

boolean mavlink_frequency_send( unsigned char frequency, unsigned char counter)
// Decide whether it the correct moment to send a given telemetry update, depending on requested frequency
{
	unsigned char max_counter ;
	if ( frequency == 0 )
	{
		return false ;
	}
	else if ( frequency > 0 && frequency < 8 )
	{
		max_counter = mavlink_freq_table[frequency] ;
		return is_this_the_moment_to_send( counter, max_counter ) ;
	}	 
	else if ( frequency > 7 && frequency < 14 )
	{
		max_counter = 4 ;
		return is_this_the_moment_to_send( counter,max_counter ) ;
	}
	else if (frequency > 13 && frequency < 17)
	{
		max_counter = 3 ;
		return is_this_the_moment_to_send( counter,max_counter ) ;
	}
	else if (frequency > 16 && frequency < 24 )
	{
		max_counter = 2 ;
		return is_this_the_moment_to_send( counter,max_counter ) ;
	}
	else if ( frequency > 23 )
	{
		return true ; // send data on every call
	}
	else
	{
		return false ; // should never reach this line
	}
}

void mavlink_output_40hz( void )
{
	struct relative2D matrix_accum ;
	float earth_pitch ;		// pitch in radians with respect to earth 
	float earth_roll ;		// roll in radians of the plane with respect to earth frame
	float earth_yaw ;		// yaw in radians with respect to earth frame
	float earth_pitch_velocity ; // radians / sec with respect to earth
	float earth_roll_velocity ;  // radians / sec with respect to earth
	float earth_yaw_velocity ;   // radians / sec with respect to earth
	int accum ;
	long accum_long ;
	uint8_t mode; ///< System mode, see MAV_MODE ENUM in mavlink/include/mavlink_types.h
	unsigned char spread_transmission_load = 0; // Used to spread sending of different message types over a period of 1 second.

    if ( ++counter_40hz == 40) counter_40hz = 0 ;
	
	usec = usec + 25000 ; // Frequency sensitive code

	// Note that message types are arranged in order of importance so that if the serial buffer fills up,
	// critical message types are more likely to still be transmitted.

	// HEARTBEAT
	spread_transmission_load = 0;
	if ( mavlink_frequency_send( 4, counter_40hz + spread_transmission_load)) 
	{	
		mavlink_msg_heartbeat_send(MAVLINK_COMM_0, MAV_FIXED_WING, MAV_AUTOPILOT_ARDUPILOTMEGA) ;
	}

	// GLOBAL POSITION - derived from fused sensors
	// Note: This code assumes that Dead Reckoning is running.
	spread_transmission_load = 6 ;
	if (mavlink_frequency_send( 8 , counter_40hz + spread_transmission_load))
	{ 
		
		float lat_float, lon_float, alt_float = 0.0 ;
		accum_long = IMUlocationy._.W1 + ( lat_origin.WW / 90 ) ; //  meters North from Equator
		lat_float  =  ( accum_long * 90 ) / 10000000.0 ;          // degrees North from Equator 
		lon_float =   (long_origin.WW  + ((( IMUlocationx._.W1 * 90 )) / ( float )( cos_lat / 16384.0 ))) / 10000000.0 ;
		alt_float = (float) (((((int) (IMUlocationz._.W1)) * 100) + alt_origin._.W0) / 100.0) ;
		mavlink_msg_global_position_send(MAVLINK_COMM_0, usec, 
			lat_float , lon_float, alt_float ,
			(float) IMUvelocityx._.W1, (float) IMUvelocityy._.W1, (float) IMUvelocityz._.W1 ) ; // meters per second
	
	}

	// ATTITUDE
	//  Roll: Earth Frame of Reference
	spread_transmission_load = 12 ;
	#define     MAVLINK_FREQ_ATTITUDE			8 // Be careful if you change this. Requested frequency may not be actual freq.
	if (mavlink_frequency_send( MAVLINK_FREQ_ATTITUDE , counter_40hz + spread_transmission_load))
	{ 
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

		// Beginning of frequency sensitive code
		earth_pitch_velocity = ( earth_pitch - previous_earth_pitch ) * MAVLINK_FREQ_ATTITUDE ; 
		earth_roll_velocity  = ( earth_roll  - previous_earth_roll  ) * MAVLINK_FREQ_ATTITUDE ;
		earth_yaw_velocity   = ( earth_yaw   - previous_earth_yaw   ) * MAVLINK_FREQ_ATTITUDE ;
		// End of frequency sensitive code

		previous_earth_pitch = earth_pitch ;
		previous_earth_roll  = earth_roll  ;
		previous_earth_yaw   = earth_yaw   ;

		mavlink_msg_attitude_send(MAVLINK_COMM_0,usec, earth_roll, earth_pitch, earth_yaw, 
				                  earth_roll_velocity, earth_pitch_velocity, earth_yaw_velocity ) ;
	}

	// SYSTEM STATUS
	spread_transmission_load = 18 ;
	if (mavlink_frequency_send( 4, counter_40hz + spread_transmission_load)) 
	{
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
		    (uint16_t) (udb_cpu_load()) * 10, 
			(uint16_t)  10000,  // Battery voltage in mV
			(uint8_t)   0,      // 0 Motor free to turn off, 1 Motor Blocked from turning on
#if ( SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )
			(uint16_t)  r_mavlink_status.packet_rx_drop_count) ;    // Not tested yet, may not be correct.
#else
			(uint16_t) 0 ) ; 
#endif
	}

	// RC CHANNELS
	// Channel values shifted left by 1, to divide by two, so values reflect PWM pulses in microseconds.
	// mavlink_msg_rc_channels_raw_send(mavlink_channel_t chan, uint16_t chan1_raw, uint16_t chan2_raw,
	//    uint16_t chan3_raw, uint16_t chan4_raw, uint16_t chan5_raw, uint16_t chan6_raw, uint16_t chan7_raw,
	//    uint16_t chan8_raw, uint8_t rssi)
	spread_transmission_load = 24 ;
	if (mavlink_frequency_send( streamRateRCChannels, counter_40hz + spread_transmission_load)) 
	{			
	 	mavlink_msg_rc_channels_raw_send(MAVLINK_COMM_0,
			 (uint16_t)(udb_pwOut[1]>>1),  (uint16_t) (udb_pwOut[2]>>1), (uint16_t) (udb_pwOut[3]>>1), (uint16_t) (udb_pwOut[4]>>1),
			 (uint16_t) (udb_pwOut[5]>>1), (uint16_t) (udb_pwOut[6]>>1), (uint16_t) (udb_pwOut[7]>>1), (uint16_t) (udb_pwOut[8]>>1),
			 (uint8_t) 0); // last item, RSSI currently not measured on UDB.
	}

	// RAW SENSORS - ACCELOREMETERS and GYROS
	// The values sent are raw with no offsets, scaling, and sign correction
	// It is expected that these values are graphed to allow users to check basic sensor operation,
	// and to graph noise on the signals.
	spread_transmission_load = 30 ;
	if (mavlink_frequency_send( streamRateRawSensors , counter_40hz + spread_transmission_load))
	{ 				
#if ( MAG_YAW_DRIFT == 1 )
		
		extern int magFieldRaw[] ;
		mavlink_msg_raw_imu_send(MAVLINK_COMM_0, usec,
					 (int16_t)   udb_yaccel.input,
					 (int16_t) - udb_xaccel.input,
					 (int16_t)   udb_zaccel.input, 
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

	}
#if ( SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )
#define NO_OF_VARIABLES_TO_SEND		1
	// SEND VALUES OF VARIABLES IF THEY HAVE BEEN REQUESTED
	if 	( udb_flags._.mavlink_send_variables == 1 )
	{
		send_variables_counter++ ;
		switch (send_variables_counter)	
		{
	    	case 1:  
	    	{
				const int8_t rollkp_name[MAVLINK_MSG_PARAM_VALUE_FIELD_PARAM_ID_LEN] = { 'R','O','L','L','K','P',0 };
				// static inline void mavlink_msg_param_value_send(mavlink_channel_t chan, const int8_t* param_id,
			    // float param_value, uint16_t param_count, uint16_t param_index)
				mavlink_msg_param_value_send( MAVLINK_COMM_0, rollkp_name , (float) (rollkp / 16384.0 ),NO_OF_VARIABLES_TO_SEND	, 0 ) ;
				break ;
			}
			case 2:
			{
				const int8_t rollkp_name[MAVLINK_MSG_PARAM_VALUE_FIELD_PARAM_ID_LEN] = { 'M','A','X','S','T','A','C','K',0 } ;
				mavlink_msg_param_value_send( MAVLINK_COMM_0, rollkp_name , (float) (4096 - maxstack) ,NO_OF_VARIABLES_TO_SEND	, 0 ) ;
			}
			default :
			{
				udb_flags._.mavlink_send_variables = 0 ;
				send_variables_counter = 0 ;
				break ;
			}
		}
	}				
#endif		
	return ;
}

/*
#if ( SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )
// void (* sio_parse ) ( unsigned char inchar ) = &mavlink_msg_recv ;

const struct mavlink_parameters {
	char* parameter_name[MAVLINK_MSG_PARAM_VALUE_FIELD_PARAM_ID_LEN] ;
    float max_value ;
    float min_value ;
	boolean read_only ;
    void ( * mavlink_set_value) (char index) ;
	} ;

struct mavlink_parameters rollkp_param = { { 'M','A','X','S','T','A','C','K',0 }, 1.0, 0.0, false, &set_pid())

const struct mavlink_parameters list_of_mavlink_parameters[] =
			{ rollkp_param, maxstack_param } ;

void mavlink_get_parameter( char index )
{	
}

char * mavlink_get_parameter_name( char index)
{
	return list_of_mavlink_parameters[index].parameter)name ;
}

void set_parameter_value(char index, float value)
{
}


#endif  //	( SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )	
*/

#endif  // ( SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK )
