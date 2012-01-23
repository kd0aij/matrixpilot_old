// MESSAGE FLEXIFUNCTION_COMMIT_BUFFER PACKING

#define MAVLINK_MSG_ID_FLEXIFUNCTION_COMMIT_BUFFER 153

typedef struct __mavlink_flexifunction_commit_buffer_t
{
 uint8_t target_system; ///< System ID
 uint8_t target_component; ///< Component ID
 uint16_t register_count; ///< Number of registers
 uint16_t function_count; ///< Number of functions
 uint16_t buffer_checksum; ///< Buffer checksum for commit
} mavlink_flexifunction_commit_buffer_t;

#define MAVLINK_MSG_ID_FLEXIFUNCTION_COMMIT_BUFFER_LEN 8
#define MAVLINK_MSG_ID_153_LEN 8



#define MAVLINK_MESSAGE_INFO_FLEXIFUNCTION_COMMIT_BUFFER { \
	"FLEXIFUNCTION_COMMIT_BUFFER", \
	5, \
	{  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_flexifunction_commit_buffer_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_flexifunction_commit_buffer_t, target_component) }, \
         { "register_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_flexifunction_commit_buffer_t, register_count) }, \
         { "function_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_flexifunction_commit_buffer_t, function_count) }, \
         { "buffer_checksum", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_flexifunction_commit_buffer_t, buffer_checksum) }, \
         } \
}


/**
 * @brief Pack a flexifunction_commit_buffer message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param register_count Number of registers
 * @param function_count Number of functions
 * @param buffer_checksum Buffer checksum for commit
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_flexifunction_commit_buffer_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t target_component, uint16_t register_count, uint16_t function_count, uint16_t buffer_checksum)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[8];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint16_t(buf, 2, register_count);
	_mav_put_uint16_t(buf, 4, function_count);
	_mav_put_uint16_t(buf, 6, buffer_checksum);

        memcpy(_MAV_PAYLOAD(msg), buf, 8);
#else
	mavlink_flexifunction_commit_buffer_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.register_count = register_count;
	packet.function_count = function_count;
	packet.buffer_checksum = buffer_checksum;

        memcpy(_MAV_PAYLOAD(msg), &packet, 8);
#endif

	msg->msgid = MAVLINK_MSG_ID_FLEXIFUNCTION_COMMIT_BUFFER;
	return mavlink_finalize_message(msg, system_id, component_id, 8);
}

/**
 * @brief Pack a flexifunction_commit_buffer message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param register_count Number of registers
 * @param function_count Number of functions
 * @param buffer_checksum Buffer checksum for commit
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_flexifunction_commit_buffer_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t target_component,uint16_t register_count,uint16_t function_count,uint16_t buffer_checksum)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[8];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint16_t(buf, 2, register_count);
	_mav_put_uint16_t(buf, 4, function_count);
	_mav_put_uint16_t(buf, 6, buffer_checksum);

        memcpy(_MAV_PAYLOAD(msg), buf, 8);
#else
	mavlink_flexifunction_commit_buffer_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.register_count = register_count;
	packet.function_count = function_count;
	packet.buffer_checksum = buffer_checksum;

        memcpy(_MAV_PAYLOAD(msg), &packet, 8);
#endif

	msg->msgid = MAVLINK_MSG_ID_FLEXIFUNCTION_COMMIT_BUFFER;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 8);
}

/**
 * @brief Encode a flexifunction_commit_buffer struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param flexifunction_commit_buffer C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_flexifunction_commit_buffer_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_flexifunction_commit_buffer_t* flexifunction_commit_buffer)
{
	return mavlink_msg_flexifunction_commit_buffer_pack(system_id, component_id, msg, flexifunction_commit_buffer->target_system, flexifunction_commit_buffer->target_component, flexifunction_commit_buffer->register_count, flexifunction_commit_buffer->function_count, flexifunction_commit_buffer->buffer_checksum);
}

/**
 * @brief Send a flexifunction_commit_buffer message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param register_count Number of registers
 * @param function_count Number of functions
 * @param buffer_checksum Buffer checksum for commit
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_flexifunction_commit_buffer_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t register_count, uint16_t function_count, uint16_t buffer_checksum)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[8];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint16_t(buf, 2, register_count);
	_mav_put_uint16_t(buf, 4, function_count);
	_mav_put_uint16_t(buf, 6, buffer_checksum);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FLEXIFUNCTION_COMMIT_BUFFER, buf, 8);
#else
	mavlink_flexifunction_commit_buffer_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.register_count = register_count;
	packet.function_count = function_count;
	packet.buffer_checksum = buffer_checksum;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FLEXIFUNCTION_COMMIT_BUFFER, (const char *)&packet, 8);
#endif
}

#endif

// MESSAGE FLEXIFUNCTION_COMMIT_BUFFER UNPACKING


/**
 * @brief Get field target_system from flexifunction_commit_buffer message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_flexifunction_commit_buffer_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from flexifunction_commit_buffer message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_flexifunction_commit_buffer_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field register_count from flexifunction_commit_buffer message
 *
 * @return Number of registers
 */
static inline uint16_t mavlink_msg_flexifunction_commit_buffer_get_register_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field function_count from flexifunction_commit_buffer message
 *
 * @return Number of functions
 */
static inline uint16_t mavlink_msg_flexifunction_commit_buffer_get_function_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field buffer_checksum from flexifunction_commit_buffer message
 *
 * @return Buffer checksum for commit
 */
static inline uint16_t mavlink_msg_flexifunction_commit_buffer_get_buffer_checksum(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Decode a flexifunction_commit_buffer message into a struct
 *
 * @param msg The message to decode
 * @param flexifunction_commit_buffer C-struct to decode the message contents into
 */
static inline void mavlink_msg_flexifunction_commit_buffer_decode(const mavlink_message_t* msg, mavlink_flexifunction_commit_buffer_t* flexifunction_commit_buffer)
{
#if MAVLINK_NEED_BYTE_SWAP
	flexifunction_commit_buffer->target_system = mavlink_msg_flexifunction_commit_buffer_get_target_system(msg);
	flexifunction_commit_buffer->target_component = mavlink_msg_flexifunction_commit_buffer_get_target_component(msg);
	flexifunction_commit_buffer->register_count = mavlink_msg_flexifunction_commit_buffer_get_register_count(msg);
	flexifunction_commit_buffer->function_count = mavlink_msg_flexifunction_commit_buffer_get_function_count(msg);
	flexifunction_commit_buffer->buffer_checksum = mavlink_msg_flexifunction_commit_buffer_get_buffer_checksum(msg);
#else
	memcpy(flexifunction_commit_buffer, _MAV_PAYLOAD(msg), 8);
#endif
}
