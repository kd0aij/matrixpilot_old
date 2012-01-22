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
	};
	mavlink_flexifunction_set_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_set_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_flexifunction_set_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_set_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component );
	mavlink_msg_flexifunction_set_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_set_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component );
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
	mavlink_msg_flexifunction_set_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component );
	mavlink_msg_flexifunction_set_decode(last_msg, &packet2);
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
	17443,
	};
	mavlink_flexifunction_read_req_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        	packet1.read_req_type = packet_in.read_req_type;
        	packet1.data_index = packet_in.data_index;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_read_req_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_flexifunction_read_req_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_read_req_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.read_req_type , packet1.data_index );
	mavlink_msg_flexifunction_read_req_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_read_req_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.read_req_type , packet1.data_index );
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
	mavlink_msg_flexifunction_read_req_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.read_req_type , packet1.data_index );
	mavlink_msg_flexifunction_read_req_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_flexifunction_set_buffer_function(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_flexifunction_set_buffer_function_t packet_in = {
		5,
	72,
	17339,
	17,
	84,
	17547,
	{ 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76 },
	};
	mavlink_flexifunction_set_buffer_function_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        	packet1.func_index = packet_in.func_index;
        	packet1.function_type = packet_in.function_type;
        	packet1.Action = packet_in.Action;
        	packet1.out_index = packet_in.out_index;
        
        	memcpy(packet1.settings_data, packet_in.settings_data, sizeof(int8_t)*48);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_set_buffer_function_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_flexifunction_set_buffer_function_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_set_buffer_function_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.func_index , packet1.function_type , packet1.Action , packet1.out_index , packet1.settings_data );
	mavlink_msg_flexifunction_set_buffer_function_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_set_buffer_function_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.func_index , packet1.function_type , packet1.Action , packet1.out_index , packet1.settings_data );
	mavlink_msg_flexifunction_set_buffer_function_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_flexifunction_set_buffer_function_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_set_buffer_function_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.func_index , packet1.function_type , packet1.Action , packet1.out_index , packet1.settings_data );
	mavlink_msg_flexifunction_set_buffer_function_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_flexifunction_commit_buffer(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_flexifunction_commit_buffer_t packet_in = {
		5,
	72,
	17339,
	17443,
	17547,
	};
	mavlink_flexifunction_commit_buffer_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        	packet1.register_count = packet_in.register_count;
        	packet1.function_count = packet_in.function_count;
        	packet1.buffer_checksum = packet_in.buffer_checksum;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_commit_buffer_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_flexifunction_commit_buffer_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_commit_buffer_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.register_count , packet1.function_count , packet1.buffer_checksum );
	mavlink_msg_flexifunction_commit_buffer_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_commit_buffer_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.register_count , packet1.function_count , packet1.buffer_checksum );
	mavlink_msg_flexifunction_commit_buffer_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_flexifunction_commit_buffer_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_commit_buffer_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.register_count , packet1.function_count , packet1.buffer_checksum );
	mavlink_msg_flexifunction_commit_buffer_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_flexifunction_statistics(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_flexifunction_statistics_t packet_in = {
		5,
	72,
	17339,
	17443,
	17547,
	17651,
	17755,
	17859,
	};
	mavlink_flexifunction_statistics_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        	packet1.register_count = packet_in.register_count;
        	packet1.function_count = packet_in.function_count;
        	packet1.register_max_count = packet_in.register_max_count;
        	packet1.function_max_count = packet_in.function_max_count;
        	packet1.function_byte_size = packet_in.function_byte_size;
        	packet1.buffer_checksum = packet_in.buffer_checksum;
        
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_statistics_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_flexifunction_statistics_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_statistics_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.register_count , packet1.function_count , packet1.register_max_count , packet1.function_max_count , packet1.function_byte_size , packet1.buffer_checksum );
	mavlink_msg_flexifunction_statistics_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_statistics_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.register_count , packet1.function_count , packet1.register_max_count , packet1.function_max_count , packet1.function_byte_size , packet1.buffer_checksum );
	mavlink_msg_flexifunction_statistics_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_flexifunction_statistics_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_statistics_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.register_count , packet1.function_count , packet1.register_max_count , packet1.function_max_count , packet1.function_byte_size , packet1.buffer_checksum );
	mavlink_msg_flexifunction_statistics_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_flexifunction_register_name(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
	mavlink_flexifunction_register_name_t packet_in = {
		5,
	72,
	17339,
	17443,
	{ 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166 },
	};
	mavlink_flexifunction_register_name_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        	packet1.target_system = packet_in.target_system;
        	packet1.target_component = packet_in.target_component;
        	packet1.register_index = packet_in.register_index;
        	packet1.register_name_length = packet_in.register_name_length;
        
        	memcpy(packet1.register_name, packet_in.register_name, sizeof(uint8_t)*16);
        

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_register_name_encode(system_id, component_id, &msg, &packet1);
	mavlink_msg_flexifunction_register_name_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_register_name_pack(system_id, component_id, &msg , packet1.target_system , packet1.target_component , packet1.register_index , packet1.register_name_length , packet1.register_name );
	mavlink_msg_flexifunction_register_name_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_register_name_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target_system , packet1.target_component , packet1.register_index , packet1.register_name_length , packet1.register_name );
	mavlink_msg_flexifunction_register_name_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
        	comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
	mavlink_msg_flexifunction_register_name_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
	mavlink_msg_flexifunction_register_name_send(MAVLINK_COMM_1 , packet1.target_system , packet1.target_component , packet1.register_index , packet1.register_name_length , packet1.register_name );
	mavlink_msg_flexifunction_register_name_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
}

static void mavlink_test_matrixpilot(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
	mavlink_test_flexifunction_set(system_id, component_id, last_msg);
	mavlink_test_flexifunction_read_req(system_id, component_id, last_msg);
	mavlink_test_flexifunction_set_buffer_function(system_id, component_id, last_msg);
	mavlink_test_flexifunction_commit_buffer(system_id, component_id, last_msg);
	mavlink_test_flexifunction_statistics(system_id, component_id, last_msg);
	mavlink_test_flexifunction_register_name(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MATRIXPILOT_TESTSUITE_H
