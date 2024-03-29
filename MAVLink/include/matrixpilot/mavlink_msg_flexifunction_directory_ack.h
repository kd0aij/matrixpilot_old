// MESSAGE FLEXIFUNCTION_DIRECTORY_ACK PACKING

#define MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK 156

typedef struct __mavlink_flexifunction_directory_ack_t
{
 uint16_t result; ///< result of acknowledge, 0=fail, 1=good
 uint8_t target_system; ///< System ID
 uint8_t target_component; ///< Component ID
 uint8_t directory_type; ///< 0=inputs, 1=outputs
 uint8_t start_index; ///< index of first directory entry to write
 uint8_t count; ///< count of directory entries to write
} mavlink_flexifunction_directory_ack_t;

#define MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK_LEN 7
#define MAVLINK_MSG_ID_156_LEN 7



#define MAVLINK_MESSAGE_INFO_FLEXIFUNCTION_DIRECTORY_ACK { \
	"FLEXIFUNCTION_DIRECTORY_ACK", \
	6, \
	{  { "result", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_flexifunction_directory_ack_t, result) }, \
         { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_flexifunction_directory_ack_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_flexifunction_directory_ack_t, target_component) }, \
         { "directory_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_flexifunction_directory_ack_t, directory_type) }, \
         { "start_index", NULL, MAVLINK_TYPE_UINT8_T, 0, 5, offsetof(mavlink_flexifunction_directory_ack_t, start_index) }, \
         { "count", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_flexifunction_directory_ack_t, count) }, \
         } \
}


/**
 * @brief Pack a flexifunction_directory_ack message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param directory_type 0=inputs, 1=outputs
 * @param start_index index of first directory entry to write
 * @param count count of directory entries to write
 * @param result result of acknowledge, 0=fail, 1=good
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_flexifunction_directory_ack_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t target_component, uint8_t directory_type, uint8_t start_index, uint8_t count, uint16_t result)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[7];
	_mav_put_uint16_t(buf, 0, result);
	_mav_put_uint8_t(buf, 2, target_system);
	_mav_put_uint8_t(buf, 3, target_component);
	_mav_put_uint8_t(buf, 4, directory_type);
	_mav_put_uint8_t(buf, 5, start_index);
	_mav_put_uint8_t(buf, 6, count);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 7);
#else
	mavlink_flexifunction_directory_ack_t packet;
	packet.result = result;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.directory_type = directory_type;
	packet.start_index = start_index;
	packet.count = count;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 7);
#endif

	msg->msgid = MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK;
	return mavlink_finalize_message(msg, system_id, component_id, 7, 218);
}

/**
 * @brief Pack a flexifunction_directory_ack message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param directory_type 0=inputs, 1=outputs
 * @param start_index index of first directory entry to write
 * @param count count of directory entries to write
 * @param result result of acknowledge, 0=fail, 1=good
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_flexifunction_directory_ack_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t target_component,uint8_t directory_type,uint8_t start_index,uint8_t count,uint16_t result)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[7];
	_mav_put_uint16_t(buf, 0, result);
	_mav_put_uint8_t(buf, 2, target_system);
	_mav_put_uint8_t(buf, 3, target_component);
	_mav_put_uint8_t(buf, 4, directory_type);
	_mav_put_uint8_t(buf, 5, start_index);
	_mav_put_uint8_t(buf, 6, count);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 7);
#else
	mavlink_flexifunction_directory_ack_t packet;
	packet.result = result;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.directory_type = directory_type;
	packet.start_index = start_index;
	packet.count = count;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 7);
#endif

	msg->msgid = MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 7, 218);
}

/**
 * @brief Encode a flexifunction_directory_ack struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param flexifunction_directory_ack C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_flexifunction_directory_ack_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_flexifunction_directory_ack_t* flexifunction_directory_ack)
{
	return mavlink_msg_flexifunction_directory_ack_pack(system_id, component_id, msg, flexifunction_directory_ack->target_system, flexifunction_directory_ack->target_component, flexifunction_directory_ack->directory_type, flexifunction_directory_ack->start_index, flexifunction_directory_ack->count, flexifunction_directory_ack->result);
}

/**
 * @brief Send a flexifunction_directory_ack message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param directory_type 0=inputs, 1=outputs
 * @param start_index index of first directory entry to write
 * @param count count of directory entries to write
 * @param result result of acknowledge, 0=fail, 1=good
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_flexifunction_directory_ack_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t directory_type, uint8_t start_index, uint8_t count, uint16_t result)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[7];
	_mav_put_uint16_t(buf, 0, result);
	_mav_put_uint8_t(buf, 2, target_system);
	_mav_put_uint8_t(buf, 3, target_component);
	_mav_put_uint8_t(buf, 4, directory_type);
	_mav_put_uint8_t(buf, 5, start_index);
	_mav_put_uint8_t(buf, 6, count);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK, buf, 7, 218);
#else
	mavlink_flexifunction_directory_ack_t packet;
	packet.result = result;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.directory_type = directory_type;
	packet.start_index = start_index;
	packet.count = count;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FLEXIFUNCTION_DIRECTORY_ACK, (const char *)&packet, 7, 218);
#endif
}

#endif

// MESSAGE FLEXIFUNCTION_DIRECTORY_ACK UNPACKING


/**
 * @brief Get field target_system from flexifunction_directory_ack message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_flexifunction_directory_ack_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field target_component from flexifunction_directory_ack message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_flexifunction_directory_ack_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field directory_type from flexifunction_directory_ack message
 *
 * @return 0=inputs, 1=outputs
 */
static inline uint8_t mavlink_msg_flexifunction_directory_ack_get_directory_type(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field start_index from flexifunction_directory_ack message
 *
 * @return index of first directory entry to write
 */
static inline uint8_t mavlink_msg_flexifunction_directory_ack_get_start_index(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  5);
}

/**
 * @brief Get field count from flexifunction_directory_ack message
 *
 * @return count of directory entries to write
 */
static inline uint8_t mavlink_msg_flexifunction_directory_ack_get_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field result from flexifunction_directory_ack message
 *
 * @return result of acknowledge, 0=fail, 1=good
 */
static inline uint16_t mavlink_msg_flexifunction_directory_ack_get_result(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Decode a flexifunction_directory_ack message into a struct
 *
 * @param msg The message to decode
 * @param flexifunction_directory_ack C-struct to decode the message contents into
 */
static inline void mavlink_msg_flexifunction_directory_ack_decode(const mavlink_message_t* msg, mavlink_flexifunction_directory_ack_t* flexifunction_directory_ack)
{
#if MAVLINK_NEED_BYTE_SWAP
	flexifunction_directory_ack->result = mavlink_msg_flexifunction_directory_ack_get_result(msg);
	flexifunction_directory_ack->target_system = mavlink_msg_flexifunction_directory_ack_get_target_system(msg);
	flexifunction_directory_ack->target_component = mavlink_msg_flexifunction_directory_ack_get_target_component(msg);
	flexifunction_directory_ack->directory_type = mavlink_msg_flexifunction_directory_ack_get_directory_type(msg);
	flexifunction_directory_ack->start_index = mavlink_msg_flexifunction_directory_ack_get_start_index(msg);
	flexifunction_directory_ack->count = mavlink_msg_flexifunction_directory_ack_get_count(msg);
#else
	memcpy(flexifunction_directory_ack, _MAV_PAYLOAD(msg), 7);
#endif
}
