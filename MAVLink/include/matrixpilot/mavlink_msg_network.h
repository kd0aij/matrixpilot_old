// MESSAGE NETWORK PACKING

#define MAVLINK_MSG_ID_NETWORK 183

typedef struct __mavlink_network_t
{
 uint8_t test1; ///< Test1Name
 uint8_t test2; ///< Test2Name
} mavlink_network_t;

#define MAVLINK_MSG_ID_NETWORK_LEN 2
#define MAVLINK_MSG_ID_183_LEN 2



#define MAVLINK_MESSAGE_INFO_NETWORK { \
	"NETWORK", \
	2, \
	{  { "test1", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_network_t, test1) }, \
         { "test2", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_network_t, test2) }, \
         } \
}


/**
 * @brief Pack a network message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param test1 Test1Name
 * @param test2 Test2Name
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_network_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t test1, uint8_t test2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, test1);
	_mav_put_uint8_t(buf, 1, test2);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 2);
#else
	mavlink_network_t packet;
	packet.test1 = test1;
	packet.test2 = test2;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 2);
#endif

	msg->msgid = MAVLINK_MSG_ID_NETWORK;
	return mavlink_finalize_message(msg, system_id, component_id, 2, 154);
}

/**
 * @brief Pack a network message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param test1 Test1Name
 * @param test2 Test2Name
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_network_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t test1,uint8_t test2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, test1);
	_mav_put_uint8_t(buf, 1, test2);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, 2);
#else
	mavlink_network_t packet;
	packet.test1 = test1;
	packet.test2 = test2;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, 2);
#endif

	msg->msgid = MAVLINK_MSG_ID_NETWORK;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 2, 154);
}

/**
 * @brief Encode a network struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param network C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_network_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_network_t* network)
{
	return mavlink_msg_network_pack(system_id, component_id, msg, network->test1, network->test2);
}

/**
 * @brief Send a network message
 * @param chan MAVLink channel to send the message
 *
 * @param test1 Test1Name
 * @param test2 Test2Name
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_network_send(mavlink_channel_t chan, uint8_t test1, uint8_t test2)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[2];
	_mav_put_uint8_t(buf, 0, test1);
	_mav_put_uint8_t(buf, 1, test2);

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NETWORK, buf, 2, 154);
#else
	mavlink_network_t packet;
	packet.test1 = test1;
	packet.test2 = test2;

	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_NETWORK, (const char *)&packet, 2, 154);
#endif
}

#endif

// MESSAGE NETWORK UNPACKING


/**
 * @brief Get field test1 from network message
 *
 * @return Test1Name
 */
static inline uint8_t mavlink_msg_network_get_test1(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field test2 from network message
 *
 * @return Test2Name
 */
static inline uint8_t mavlink_msg_network_get_test2(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Decode a network message into a struct
 *
 * @param msg The message to decode
 * @param network C-struct to decode the message contents into
 */
static inline void mavlink_msg_network_decode(const mavlink_message_t* msg, mavlink_network_t* network)
{
#if MAVLINK_NEED_BYTE_SWAP
	network->test1 = mavlink_msg_network_get_test1(msg);
	network->test2 = mavlink_msg_network_get_test2(msg);
#else
	memcpy(network, _MAV_PAYLOAD(msg), 2);
#endif
}
