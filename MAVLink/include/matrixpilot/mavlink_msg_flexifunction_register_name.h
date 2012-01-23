// MESSAGE FLEXIFUNCTION_REGISTER_NAME PACKING

#define MAVLINK_MSG_ID_FLEXIFUNCTION_REGISTER_NAME 155

typedef struct __mavlink_flexifunction_register_name_t
{
 uint8_t target_system; ///< System ID
 uint8_t target_component; ///< Component ID
 uint16_t register_index; ///< Register index
 uint16_t register_name_length; ///< Register name length
 uint8_t register_name[16]; ///< Register name
} mavlink_flexifunction_register_name_t;

#define MAVLINK_MSG_ID_FLEXIFUNCTION_REGISTER_NAME_LEN 22
#define MAVLINK_MSG_ID_155_LEN 22

#define MAVLINK_MSG_FLEXIFUNCTION_REGISTER_NAME_FIELD_REGISTER_NAME_LEN 16

#define MAVLINK_MESSAGE_INFO_FLEXIFUNCTION_REGISTER_NAME { \
	"FLEXIFUNCTION_REGISTER_NAME", \
	5, \
	{  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_flexifunction_register_name_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_flexifunction_register_name_t, target_component) }, \
         { "register_index", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_flexifunction_register_name_t, register_index) }, \
         { "register_name_length", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_flexifunction_register_name_t, register_name_length) }, \
         { "register_name", NULL, MAVLINK_TYPE_UINT8_T, 16, 6, offsetof(mavlink_flexifunction_register_name_t, register_name) }, \
         } \
}


/**
 * @brief Pack a flexifunction_register_name message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param register_index Register index
 * @param register_name_length Register name length
 * @param register_name Register name
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_flexifunction_register_name_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t target_component, uint16_t register_index, uint16_t register_name_length, const uint8_t *register_name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[22];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint16_t(buf, 2, register_index);
	_mav_put_uint16_t(buf, 4, register_name_length);
	_mav_put_uint8_t_array(buf, 6, register_name, 16);
        memcpy(_MAV_PAYLOAD(msg), buf, 22);
#else
	mavlink_flexifunction_register_name_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.register_index = register_index;
	packet.register_name_length = register_name_length;
	memcpy(packet.register_name, register_name, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD(msg), &packet, 22);
#endif

	msg->msgid = MAVLINK_MSG_ID_FLEXIFUNCTION_REGISTER_NAME;
	return mavlink_finalize_message(msg, system_id, component_id, 22);
}

/**
 * @brief Pack a flexifunction_register_name message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param register_index Register index
 * @param register_name_length Register name length
 * @param register_name Register name
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_flexifunction_register_name_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t target_component,uint16_t register_index,uint16_t register_name_length,const uint8_t *register_name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[22];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint16_t(buf, 2, register_index);
	_mav_put_uint16_t(buf, 4, register_name_length);
	_mav_put_uint8_t_array(buf, 6, register_name, 16);
        memcpy(_MAV_PAYLOAD(msg), buf, 22);
#else
	mavlink_flexifunction_register_name_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.register_index = register_index;
	packet.register_name_length = register_name_length;
	memcpy(packet.register_name, register_name, sizeof(uint8_t)*16);
        memcpy(_MAV_PAYLOAD(msg), &packet, 22);
#endif

	msg->msgid = MAVLINK_MSG_ID_FLEXIFUNCTION_REGISTER_NAME;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 22);
}

/**
 * @brief Encode a flexifunction_register_name struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param flexifunction_register_name C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_flexifunction_register_name_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_flexifunction_register_name_t* flexifunction_register_name)
{
	return mavlink_msg_flexifunction_register_name_pack(system_id, component_id, msg, flexifunction_register_name->target_system, flexifunction_register_name->target_component, flexifunction_register_name->register_index, flexifunction_register_name->register_name_length, flexifunction_register_name->register_name);
}

/**
 * @brief Send a flexifunction_register_name message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param register_index Register index
 * @param register_name_length Register name length
 * @param register_name Register name
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_flexifunction_register_name_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t register_index, uint16_t register_name_length, const uint8_t *register_name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[22];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint16_t(buf, 2, register_index);
	_mav_put_uint16_t(buf, 4, register_name_length);
	_mav_put_uint8_t_array(buf, 6, register_name, 16);
	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FLEXIFUNCTION_REGISTER_NAME, buf, 22);
#else
	mavlink_flexifunction_register_name_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.register_index = register_index;
	packet.register_name_length = register_name_length;
	memcpy(packet.register_name, register_name, sizeof(uint8_t)*16);
	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FLEXIFUNCTION_REGISTER_NAME, (const char *)&packet, 22);
#endif
}

#endif

// MESSAGE FLEXIFUNCTION_REGISTER_NAME UNPACKING


/**
 * @brief Get field target_system from flexifunction_register_name message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_flexifunction_register_name_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from flexifunction_register_name message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_flexifunction_register_name_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field register_index from flexifunction_register_name message
 *
 * @return Register index
 */
static inline uint16_t mavlink_msg_flexifunction_register_name_get_register_index(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Get field register_name_length from flexifunction_register_name message
 *
 * @return Register name length
 */
static inline uint16_t mavlink_msg_flexifunction_register_name_get_register_name_length(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field register_name from flexifunction_register_name message
 *
 * @return Register name
 */
static inline uint16_t mavlink_msg_flexifunction_register_name_get_register_name(const mavlink_message_t* msg, uint8_t *register_name)
{
	return _MAV_RETURN_uint8_t_array(msg, register_name, 16,  6);
}

/**
 * @brief Decode a flexifunction_register_name message into a struct
 *
 * @param msg The message to decode
 * @param flexifunction_register_name C-struct to decode the message contents into
 */
static inline void mavlink_msg_flexifunction_register_name_decode(const mavlink_message_t* msg, mavlink_flexifunction_register_name_t* flexifunction_register_name)
{
#if MAVLINK_NEED_BYTE_SWAP
	flexifunction_register_name->target_system = mavlink_msg_flexifunction_register_name_get_target_system(msg);
	flexifunction_register_name->target_component = mavlink_msg_flexifunction_register_name_get_target_component(msg);
	flexifunction_register_name->register_index = mavlink_msg_flexifunction_register_name_get_register_index(msg);
	flexifunction_register_name->register_name_length = mavlink_msg_flexifunction_register_name_get_register_name_length(msg);
	mavlink_msg_flexifunction_register_name_get_register_name(msg, flexifunction_register_name->register_name);
#else
	memcpy(flexifunction_register_name, _MAV_PAYLOAD(msg), 22);
#endif
}
