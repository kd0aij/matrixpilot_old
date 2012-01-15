/** @file
 *	@brief MAVLink comm protocol testsuite generated from matrixpilot.xml
 *	@see http://qgroundcontrol.org/mavlink/
 */
#ifndef MATRIXPILOT_TESTSUITE_H
#define MATRIXPILOT_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_matrixpilot(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_common(system_id, component_id, last_msg);
	mavlink_test_matrixpilot(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"


static void mavlink_test_flexifunction_set(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_flexifunction_set_t packet_in = {
		5,
	72,
	17339,
	17,
	84,
	17547,
	{ 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76 },
	};
	mavlink_flexifunction_set_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        	packet1.func_index = packet_in.func_index;
        	packet1.function_type = packet_in.function_type;
        	packet1.Action = packet_in.Action;
        	packet1.out_index = packet_in.out_index;
        
        	memcpy(packet1.settings_data, packet_in.settings_data, sizeof(int8_t)*48);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_set_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_flexifunction_set_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_set_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.func_index , packet1.function_type , packet1.Action , packet1.out_index , packet1.settings_data );
	mavlink_msg_flexifunction_set_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_set_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.func_index , packet1.function_type , packet1.Action , packet1.out_index , packet1.settings_data );
	mavlink_msg_flexifunction_set_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_flexifunction_set_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_set_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.func_index , packet1.function_type , packet1.Action , packet1.out_index , packet1.settings_data );
	mavlink_msg_flexifunction_set_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_flexifunction_data(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_flexifunction_data_t packet_in = {
		5,
	72,
	17339,
	17,
	84,
	17547,
	{ 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76 },
	};
	mavlink_flexifunction_data_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        	packet1.func_index = packet_in.func_index;
        	packet1.function_type = packet_in.function_type;
        	packet1.Action = packet_in.Action;
        	packet1.out_index = packet_in.out_index;
        
        	memcpy(packet1.settings_data, packet_in.settings_data, sizeof(int8_t)*48);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_data_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_flexifunction_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_data_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.func_index , packet1.function_type , packet1.Action , packet1.out_index , packet1.settings_data );
	mavlink_msg_flexifunction_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_data_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.func_index , packet1.function_type , packet1.Action , packet1.out_index , packet1.settings_data );
	mavlink_msg_flexifunction_data_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_flexifunction_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_data_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.func_index , packet1.function_type , packet1.Action , packet1.out_index , packet1.settings_data );
	mavlink_msg_flexifunction_data_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_flexifunction_read_req(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_flexifunction_read_req_t packet_in = {
		5,
	72,
	17339,
	};
	mavlink_flexifunction_read_req_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        	packet1.func_index = packet_in.func_index;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_read_req_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_flexifunction_read_req_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_read_req_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.func_index );
	mavlink_msg_flexifunction_read_req_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_read_req_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.func_index );
	mavlink_msg_flexifunction_read_req_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_flexifunction_read_req_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_read_req_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.func_index );
	mavlink_msg_flexifunction_read_req_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_flexifunction_read_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_flexifunction_read_all_t packet_in = {
		5,
	72,
	};
	mavlink_flexifunction_read_all_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_read_all_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_flexifunction_read_all_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_read_all_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component );
	mavlink_msg_flexifunction_read_all_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_read_all_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component );
	mavlink_msg_flexifunction_read_all_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_flexifunction_read_all_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_read_all_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component );
	mavlink_msg_flexifunction_read_all_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_matrixpilot(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_flexifunction_set(system_id, component_id, last_msg);
	mavlink_test_flexifunction_data(system_id, component_id, last_msg);
	mavlink_test_flexifunction_read_req(system_id, component_id, last_msg);
	mavlink_test_flexifunction_read_all(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MATRIXPILOT_TESTSUITE_H
