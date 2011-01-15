// MESSAGE ACTION PACKING

#define MAVLINK_MSG_ID_ACTION 10

typedef struct __mavlink_action_t 
{
	uint8_t target; ///< The system executing the action
	uint8_t target_component; ///< The component executing the action
	uint8_t action; ///< The action id

} mavlink_action_t;



/**
 * @brief Pack a action message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target The system executing the action
 * @param target_component The component executing the action
 * @param action The action id
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_action_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target, uint8_t target_component, uint8_t action)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_ACTION;

	i += put_uint8_t_by_index(target, i, msg->payload); // The system executing the action
	i += put_uint8_t_by_index(target_component, i, msg->payload); // The component executing the action
	i += put_uint8_t_by_index(action, i, msg->payload); // The action id

	return mavlink_finalize_message(msg, system_id, component_id, i);
}

/**
 * @brief Pack a action message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target The system executing the action
 * @param target_component The component executing the action
 * @param action The action id
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_action_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target, uint8_t target_component, uint8_t action)
{
	uint16_t i = 0;
	msg->msgid = MAVLINK_MSG_ID_ACTION;

	i += put_uint8_t_by_index(target, i, msg->payload); // The system executing the action
	i += put_uint8_t_by_index(target_component, i, msg->payload); // The component executing the action
	i += put_uint8_t_by_index(action, i, msg->payload); // The action id

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, i);
}

/**
 * @brief Encode a action struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param action C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_action_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_action_t* action)
{
	return mavlink_msg_action_pack(system_id, component_id, msg, action->target, action->target_component, action->action);
}

/**
 * @brief Send a action message
 * @param chan MAVLink channel to send the message
 *
 * @param target The system executing the action
 * @param target_component The component executing the action
 * @param action The action id
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_action_send(mavlink_channel_t chan, uint8_t target, uint8_t target_component, uint8_t action)
{
	mavlink_message_t msg;
	mavlink_msg_action_pack_chan(mavlink_system.sysid, mavlink_system.compid, chan, &msg, target, target_component, action);
	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE ACTION UNPACKING

/**
 * @brief Get field target from action message
 *
 * @return The system executing the action
 */
static inline uint8_t mavlink_msg_action_get_target(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload)[0];
}

/**
 * @brief Get field target_component from action message
 *
 * @return The component executing the action
 */
static inline uint8_t mavlink_msg_action_get_target_component(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t))[0];
}

/**
 * @brief Get field action from action message
 *
 * @return The action id
 */
static inline uint8_t mavlink_msg_action_get_action(const mavlink_message_t* msg)
{
	return (uint8_t)(msg->payload+sizeof(uint8_t)+sizeof(uint8_t))[0];
}

/**
 * @brief Decode a action message into a struct
 *
 * @param msg The message to decode
 * @param action C-struct to decode the message contents into
 */
static inline void mavlink_msg_action_decode(const mavlink_message_t* msg, mavlink_action_t* action)
{
	action->target = mavlink_msg_action_get_target(msg);
	action->target_component = mavlink_msg_action_get_target_component(msg);
	action->action = mavlink_msg_action_get_action(msg);
}
