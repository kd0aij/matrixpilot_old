// MESSAGE FLEXIFUNCTION_READ_ALL PACKING

#define MAVLINK_MSG_ID_FLEXIFUNCTION_READ_ALL 153

typedef struct __mavlink_flexifunction_read_all_t
{
 uint8_t target_system; ///< System ID
 uint8_t target_component; ///< Component ID
} mavlink_flexifunction_read_all_t;

#define MAVLINK_MSG_ID_FLEXIFUNCTION_READ_ALL_LEN 2
#define MAVLINK_MSG_ID_153_LEN 2



#define MAVLINK_MESSAGE_INFO_FLEXIFUNCTION_READ_ALL { \
	"FLEXIFUNCTION_READ_ALL", \
	2, \
	{  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_flexifunction_read_all_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_flexifunction_read_all_t, target_component) }, \
         } \
}


/**
 * @brief Pack a flexifunction_read_all message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_flexifunction_read_all_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t target_component)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);

        memcpy(_MAV_PAYLOAD(msg), buf, 2);
#else
	mavlink_flexifunction_read_all_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD(msg), &packet, 2);
#endif

	msg->msgid = MAVLINK_MSG_ID_FLEXIFUNCTION_READ_ALL;
	return mavlink_finalize_message(msg, system_id, component_id, 2);
}

/**
 * @brief Pack a flexifunction_read_all message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_flexifunction_read_all_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t target_component)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);

        memcpy(_MAV_PAYLOAD(msg), buf, 2);
#else
	mavlink_flexifunction_read_all_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;

        memcpy(_MAV_PAYLOAD(msg), &packet, 2);
#endif

	msg->msgid = MAVLINK_MSG_ID_FLEXIFUNCTION_READ_ALL;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 2);
}

/**
 * @brief Encode a flexifunction_read_all struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param flexifunction_read_all C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_flexifunction_read_all_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_flexifunction_read_all_t* flexifunction_read_all)
{
	return mavlink_msg_flexifunction_read_all_pack(system_id, component_id, msg, flexifunction_read_all->target_system, flexifunction_read_all->target_component);
}

/**
 * @brief Send a flexifunction_read_all message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_flexifunction_read_all_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FLEXIFUNCTION_READ_ALL, buf, 2);
#else
	mavlink_flexifunction_read_all_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FLEXIFUNCTION_READ_ALL, (const char *)&packet, 2);
#endif
}

#endif

// MESSAGE FLEXIFUNCTION_READ_ALL UNPACKING


/**
 * @brief Get field target_system from flexifunction_read_all message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_flexifunction_read_all_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from flexifunction_read_all message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_flexifunction_read_all_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a flexifunction_read_all message into a struct
 *
 * @param msg The message to decode
 * @param flexifunction_read_all C-struct to decode the message contents into
 */
static inline void mavlink_msg_flexifunction_read_all_decode(const mavlink_message_t* msg, mavlink_flexifunction_read_all_t* flexifunction_read_all)
{
#if MAVLINK_NEED_BYTE_SWAP
	flexifunction_read_all->target_system = mavlink_msg_flexifunction_read_all_get_target_system(msg);
	flexifunction_read_all->target_component = mavlink_msg_flexifunction_read_all_get_target_component(msg);
#else
	memcpy(flexifunction_read_all, _MAV_PAYLOAD(msg), 2);
#endif
}
