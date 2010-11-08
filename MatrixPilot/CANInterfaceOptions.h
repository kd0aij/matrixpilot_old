// SEE END OF FILE FOR LICENSE TERMS

////////////////////////////////////////////////////////////////////////////////
// interfaceOptions.h
// Servo interface board
// 
// This file includes all of the user-configuration for the interface board
// 


////////////////////////////////////////////////////////////////////////////////
// Configure Input and Output Channels
//
// NUM_INPUTS: Set to 8 for interface card
//#define NUM_INPUTS	8

// Logical channel numbers assigned to physical channel numbers marked on the Interface.
// Logical channels are CHANNEL_X
// Physical channels are CHX_INPUT_CHANNEL
/*
// Servos inputs in order of the interface markings
#define CH1_INPUT_CHANNEL				CHANNEL_1
#define CH2_INPUT_CHANNEL				CHANNEL_2
#define CH3_INPUT_CHANNEL				CHANNEL_3
#define CH4_INPUT_CHANNEL				CHANNEL_4
#define CH5_INPUT_CHANNEL				CHANNEL_5
#define CH6_INPUT_CHANNEL				CHANNEL_6
#define CH7_INPUT_CHANNEL				CHANNEL_7
#define CH8_INPUT_CHANNEL				CHANNEL_8
#define SPARE_INPUT_CHANNEL				CHANNEL_UNUSED
*/

// Servos 1-8 in reverse order to match the physical order of the outputs
#define CH1_INPUT_CHANNEL				CHANNEL_8
#define CH2_INPUT_CHANNEL				CHANNEL_7
#define CH3_INPUT_CHANNEL				CHANNEL_6
#define CH4_INPUT_CHANNEL				CHANNEL_5
#define CH5_INPUT_CHANNEL				CHANNEL_4
#define CH6_INPUT_CHANNEL				CHANNEL_3
#define CH7_INPUT_CHANNEL				CHANNEL_2
#define CH8_INPUT_CHANNEL				CHANNEL_1
#define SPARE_INPUT_CHANNEL				CHANNEL_UNUSED


// NUM_OUTPUTS: Set to 8 for interface card
//#define NUM_OUTPUTS	8

// Output channel pin assignments
// Select which logical channel is assigned to while physical channel
// The physical channel CHX_OUTPUT_CHANNEL is marked on the interface board
// The logical channel is CHANNEL_X
// 
#define CH1_OUTPUT_CHANNEL			CHANNEL_1
#define CH2_OUTPUT_CHANNEL			CHANNEL_2
#define CH3_OUTPUT_CHANNEL			CHANNEL_3
#define CH4_OUTPUT_CHANNEL			CHANNEL_4
#define CH5_OUTPUT_CHANNEL			CHANNEL_5
#define CH6_OUTPUT_CHANNEL			CHANNEL_6
#define CH7_OUTPUT_CHANNEL			CHANNEL_7
#define CH8_OUTPUT_CHANNEL			CHANNEL_8


////////////////////////////////////////////////////////////////////////////////
// Throttle channel always defaults to minimum
// It is also limited to minimum at output
// The interface will report lower measurements to the CAN interface
// This is to provide failsafe action without upsetting an ESC
// THIS IS SET AS LOGICAL CHANNEL NOT PHYSICAL CHANNEL
//
#define THROTTLE_INPUT_CHANNEL		CHANNEL_3
#define THROTTLE_OUTPUT_CHANNEL		CHANNEL_3
#define THROTTLE_MINIMUM_OUTPUT		2400	// Equivalent to 1.1ms


////////////////////////////////////////////////////////////////////////////////
// Mode Switch is ideally controlled by a 3-position switch on your transmitter.
// Often the Flap channel will be controlled by a 3-position switch.
// These are the thresholds for the cutoffs between low and middle, and between middle and high.
// Normal signals should fall within about 2000 - 4000.
#define MODE_INPUT_CHANNEL					CHANNEL_8
#define MODE_SWITCH_THRESHOLD_LOW			2600
#define MODE_SWITCH_THRESHOLD_HIGH			3400



////////////////////////////////////////////////////////////////////////////////
// Servo Limits
// What is the limit of measured servo range which is correct
#define SERVO_ABS_MIN 1500
#define SERVO_ABS_MAX 4500

// What is the limit of servo output range which is correct
#define SERVO_OUT_MIN 1500
#define SERVO_OUT_MAX 4500


////////////////////////////////////////////////////////////////////////////////
// Servo mask
// A bitfield of the radio inputs attached 
// COULD BE CHANGED TO BE DEFINED BY RADIO INPUT CHANNELS MJC
#define RADIO_INPUT_MASK	0b011111111

////////////////////////////////////////////////////////////////////////////////
// Receive frame timout
// This is the longest allowable time between received pulses before
//  the frame is reset.  One count is 64us.
// The timeout is used to update the communications and reset the
//  receieve channels mask.
//  Measured in maximum system clock ticks
#define RX_FRAME_TIMEOUT  7

// The system heartbeat/tick period
// Used for 
//	 	checking servo framing
//		telemetry triggers
// Assuming /64 prescaler
#define HEARTBEAT_PERIOD  73		// ~1ms


// The maximum number of PWM cycles without successful autopilot conenction
//  before reverting to manual control
#define RX_MAX_TIMEOUTS  5




/****************************************************************************/
// This is part of the servo and radio interface software
//
// ServoInterface source code
//	http://code.google.com/p/rc-servo-interface
//
// Copyright 2010 ServoInterface Team
// See the AUTHORS.TXT file for a list of authors of ServoInterface.
//
// ServoInterface is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ServoInterface is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with ServoInterface.  If not, see <http://www.gnu.org/licenses/>.
//
// Many parts of ServoInterface use either modified or unmodified code
// from the MatrixPilot pilot project.
// The project also contains code for modifying MatrixPilot to operate
// with ServoInterface.
// For details, credits and licenses of MatrixPilot see the AUTHORS.TXT file.
// or see this website: http://code.google.com/p/gentlenav
/****************************************************************************/
