// MESSAGE FLEXIFUNCTION_STATISTICS PACKING

#define MAVLINK_MSG_ID_FLEXIFUNCTION_STATISTICS 154

typedef struct __mavlink_flexifunction_statistics_t
{
 uint8_t target_system; ///< System ID
 uint8_t target_component; ///< Component ID
 uint16_t register_count; ///< Number of registers
 uint16_t function_count; ///< Number of functions
 uint16_t register_max_count; ///< Maximum number of registers
 uint16_t function_max_count; ///< Maximum number of functions
 uint16_t function_byte_size; ///< Size of function in bytes
 uint16_t buffer_checksum; ///< Buffer checksum for commit
} mavlink_flexifunction_statistics_t;

#define MAVLINK_MSG_ID_FLEXIFUNCTION_STATISTICS_LEN 14
#define MAVLINK_MSG_ID_154_LEN 14



#define MAVLINK_MESSAGE_INFO_FLEXIFUNCTION_STATISTICS { \
	"FLEXIFUNCTION_STATISTICS", \
	8, \
	{  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_flexifunction_statistics_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_flexifunction_statistics_t, target_component) }, \
         { "register_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_flexifunction_statistics_t, register_count) }, \
         { "function_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_flexifunction_statistics_t, function_count) }, \
         { "register_max_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_flexifunction_statistics_t, register_max_count) }, \
         { "function_max_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_flexifunction_statistics_t, function_max_count) }, \
         { "function_byte_size", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_flexifunction_statistics_t, function_byte_size) }, \
         { "buffer_checksum", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_flexifunction_statistics_t, buffer_checksum) }, \
         } \
}


/**
 * @brief Pack a flexifunction_statistics message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param register_count Number of registers
 * @param function_count Number of functions
 * @param register_max_count Maximum number of registers
 * @param function_max_count Maximum number of functions
 * @param function_byte_size Size of function in bytes
 * @param buffer_checksum Buffer checksum for commit
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_flexifunction_statistics_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t target_component, uint16_t register_count, uint16_t function_count, uint16_t register_max_count, uint16_t function_max_count, uint16_t function_byte_size, uint16_t buffer_checksum)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[14];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint16_t(buf, 2, register_count);
	_mav_put_uint16_t(buf, 4, function_count);
	_mav_put_uint16_t(buf, 6, register_max_count);
	_mav_put_uint16_t(buf, 8, function_max_count);
	_mav_put_uint16_t(buf, 10, function_byte_size);
	_mav_put_uint16_t(buf, 12, buffer_checksum);

        memcpy(_MAV_PAYLOAD(msg), buf, 14);
#else
	mavlink_flexifunction_statistics_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.register_count = register_count;
	packet.function_count = function_count;
	packet.register_max_count = register_max_count;
	packet.function_max_count = function_max_count;
	packet.function_byte_size = function_byte_size;
	packet.buffer_checksum = buffer_checksum;

        memcpy(_MAV_PAYLOAD(msg), &packet, 14);
#endif

	msg->msgid = MAVLINK_MSG_ID_FLEXIFUNCTION_STATISTICS;
	return mavlink_finalize_message(msg, system_id, component_id, 14);
}

/**
 * @brief Pack a flexifunction_statistics message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param register_count Number of registers
 * @param function_count Number of functions
 * @param register_max_count Maximum number of registers
 * @param function_max_count Maximum number of functions
 * @param function_byte_size Size of function in bytes
 * @param buffer_checksum Buffer checksum for commit
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_flexifunction_statistics_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t target_component,uint16_t register_count,uint16_t function_count,uint16_t register_max_count,uint16_t function_max_count,uint16_t function_byte_size,uint16_t buffer_checksum)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[14];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint16_t(buf, 2, register_count);
	_mav_put_uint16_t(buf, 4, function_count);
	_mav_put_uint16_t(buf, 6, register_max_count);
	_mav_put_uint16_t(buf, 8, function_max_count);
	_mav_put_uint16_t(buf, 10, function_byte_size);
	_mav_put_uint16_t(buf, 12, buffer_checksum);

        memcpy(_MAV_PAYLOAD(msg), buf, 14);
#else
	mavlink_flexifunction_statistics_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.register_count = register_count;
	packet.function_count = function_count;
	packet.register_max_count = register_max_count;
	packet.function_max_count = function_max_count;
	packet.function_byte_size = function_byte_size;
	packet.buffer_checksum = buffer_checksum;

        memcpy(_MAV_PAYLOAD(msg), &packet, 14);
#endif

	msg->msgid = MAVLINK_MSG_ID_FLEXIFUNCTION_STATISTICS;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 14);
}

/**
 * @brief Encode a flexifunction_statistics struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param flexifunction_statistics C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_flexifunction_statistics_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_flexifunction_statistics_t* flexifunction_statistics)
{
	return mavlink_msg_flexifunction_statistics_pack(system_id, component_id, msg, flexifunction_statistics->target_system, flexifunction_statistics->target_component, flexifunction_statistics->register_count, flexifunction_statistics->function_count, flexifunction_statistics->register_max_count, flexifunction_statistics->function_max_count, flexifunction_statistics->function_byte_size, flexifunction_statistics->buffer_checksum);
}

/**
 * @brief Send a flexifunction_statistics message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param register_count Number of registers
 * @param function_count Number of functions
 * @param register_max_count Maximum number of registers
 * @param function_max_count Maximum number of functions
 * @param function_byte_size Size of function in bytes
 * @param buffer_checksum Buffer checksum for commit
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_flexifunction_statistics_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t register_count, uint16_t function_count, uint16_t register_max_count, uint16_t function_max_count, uint16_t function_byte_size, uint16_t buffer_checksum)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[14];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint16_t(buf, 2, register_count);
	_mav_put_uint16_t(buf, 4, function_count);
	_mav_put_uint16_t(buf, 6, register_max_count);
	_mav_put_uint16_t(buf, 8, function_max_count);
	_mav_put_uint16_t(buf, 10, function_byte_size);
	_mav_put_uint16_t(buf, 12, buffer_checksum);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FLEXIFUNCTION_STATISTICS, buf, 14);
#else
	mavlink_flexifunction_statistics_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.register_count = register_count;
	packet.function_count = function_count;
	packet.register_max_count = register_max_count;
	packet.function_max_count = function_max_count;
	packet.function_byte_size = function_byte_size;
	packet.buffer_checksum = buffer_checksum;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FLEXIFUNCTION_STATISTICS, (const char *)&packet, 14);
#endif
}

#endif

// MESSAGE FLEXIFUNCTION_STATISTICS UNPACKING


/**
 * @brief Get field target_system from flexifunction_statistics message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_flexifunction_statistics_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from flexifunction_statistics message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_flexifunction_statistics_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field register_count from flexifunction_statistics message
 *
 * @return Number of registers
 */
static inline uint16_t mavlink_msg_flexifunction_statistics_get_register_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field function_count from flexifunction_statistics message
 *
 * @return Number of functions
 */
static inline uint16_t mavlink_msg_flexifunction_statistics_get_function_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field register_max_count from flexifunction_statistics message
 *
 * @return Maximum number of registers
 */
static inline uint16_t mavlink_msg_flexifunction_statistics_get_register_max_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Get field function_max_count from flexifunction_statistics message
 *
 * @return Maximum number of functions
 */
static inline uint16_t mavlink_msg_flexifunction_statistics_get_function_max_count(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field function_byte_size from flexifunction_statistics message
 *
 * @return Size of function in bytes
 */
static inline uint16_t mavlink_msg_flexifunction_statistics_get_function_byte_size(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  10);
}

/**
 * @brief Get field buffer_checksum from flexifunction_statistics message
 *
 * @return Buffer checksum for commit
 */
static inline uint16_t mavlink_msg_flexifunction_statistics_get_buffer_checksum(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Decode a flexifunction_statistics message into a struct
 *
 * @param msg The message to decode
 * @param flexifunction_statistics C-struct to decode the message contents into
 */
static inline void mavlink_msg_flexifunction_statistics_decode(const mavlink_message_t* msg, mavlink_flexifunction_statistics_t* flexifunction_statistics)
{
#if MAVLINK_NEED_BYTE_SWAP
	flexifunction_statistics->target_system = mavlink_msg_flexifunction_statistics_get_target_system(msg);
	flexifunction_statistics->target_component = mavlink_msg_flexifunction_statistics_get_target_component(msg);
	flexifunction_statistics->register_count = mavlink_msg_flexifunction_statistics_get_register_count(msg);
	flexifunction_statistics->function_count = mavlink_msg_flexifunction_statistics_get_function_count(msg);
	flexifunction_statistics->register_max_count = mavlink_msg_flexifunction_statistics_get_register_max_count(msg);
	flexifunction_statistics->function_max_count = mavlink_msg_flexifunction_statistics_get_function_max_count(msg);
	flexifunction_statistics->function_byte_size = mavlink_msg_flexifunction_statistics_get_function_byte_size(msg);
	flexifunction_statistics->buffer_checksum = mavlink_msg_flexifunction_statistics_get_buffer_checksum(msg);
#else
	memcpy(flexifunction_statistics, _MAV_PAYLOAD(msg), 14);
#endif
}
