#ifdef ConfigRed
#include "ConfigRed.h"
#endif

#ifdef ConfigGreen
#include "ConfigGreen.h"
#endif 

#define tmr1_period 0x2000 // sets time period for timer 1 interrupt to 0.5 seconds
//#define FILTERSHIFT 6 // filter shift divide
#define FILTERSHIFT 3 
#define LONGDEG_2_BYTECIR 305 // = (256/360)*((256)**4)/(10**7)
#define COURSEDEG_2_BYTECIR 466 // = (256/360)*((256)**2)/(10**2)
#define CALIB_PAUSE 12
#define STANDBY_PAUSE 48 // pause for 16 seconds of runs through the state machine
#define NUM_WAGGLES 4 // waggle 4 times during the end of the standby pause (this number must be less than STANDBY_PAUSE)
#define WAGGLE_SIZE 300

#define SERVORANGE (int) SERVOSAT*1000
#define SERVOMAX 3000 + SERVORANGE
#define SERVOMIN 3000 - SERVORANGE

#define ACCTAU 200 // in milliseconds
#define RATETAU 100

#define ACCTBYTAU 5120/ACCTAU	// 256*(time_step/time_constant)
#define RATETBYTAU 5120/RATETAU

#define indicate_loading_main 	//LATEbits.LATE4 = 0
#define indicate_loading_inter	//LATEbits.LATE4 = 1


// Choose your airframe type:
//    AIRFRAME_STANDARD		 	Ailerons and Elevator, and Rudder passthrough
//    AIRFRAME_VTAIL			Ailerons, and Elevator and Rudder as V-tail controls
//    AIRFRAME_DELTA			Aileron and Elevator as Elevons, and Rudder passthrough
//    AIRFRAME_STANDARD_NOAIL	Elevator and Rudder control (like MatrixNav)
//    AIRFRAME_VTAIL_NOAIL		Elevator and Rudder as V-tail controls (like MatrixNav with VTAIL)
#define AIRFRAME_TYPE	AIRFRAME_STANDARD


// NUM_INPUTS: Set to 4 or 5 
//   4 enables only the standard 4 input channels
//   5 also enables E8 as the 5th input channel
#define NUM_INPUTS	5


// NUM_OUTPUTS: Set to 3, 4, 5, or 6
//   3 enables only the standard 3 output channels
//   4 also enables E0 as the 4th output channel
//   5 also enables E2 as the 5th output channel
//   6 also enables E4 as the 6th output channel
#define NUM_OUTPUTS	5


// Channel numbers for each input.
// Use as is, or edit to match your setup.
//   - If you're set up MatrixNav-style (rudder navigation), then you may want to swap
//     the aileron and runner channels so that rudder is CHANNEL_1, and aileron is 5.
#define THROTTLE_INPUT_CHANNEL				CHANNEL_3
#define AILERON_INPUT_CHANNEL				CHANNEL_1
#define ELEVATOR_INPUT_CHANNEL				CHANNEL_2
#define RUDDER_INPUT_CHANNEL				CHANNEL_5
#define MODE_SWITCH_INPUT_CHANNEL			CHANNEL_4


// The Failsafe Channel is the RX channel that is monitored for loss of signal
// Make sure this is set to a channel you actually have plugged into the UAV Dev Board!
// For Spektrum receivers, set this to THROTTLE_INPUT_CHANNEL, and see the instructions
// for setting up a low failsafe value in the receiver.
//
// If you set this to something other than CHANNEL_4, then make sure you are also sending
// valid servo pulses to Input channel 4 every 20ms, or the failsafe will not work properly.
#define FAILSAFE_INPUT_CHANNEL				MODE_SWITCH_INPUT_CHANNEL


// Channel numbers for each output
// Use as is, or edit to match your setup.
//   - Only assign each channel to one output purpose
//   - If you don't want to use an output channel, set it to CHANNEL_UNUSED
//   - If you're set up MatrixNav-style (rudder navigation), then you may want to swap
//     the aileron and runner channels so that rudder is CHANNEL_1, and aileron is 5.
#define THROTTLE_OUTPUT_CHANNEL				CHANNEL_3
#define AILERON_OUTPUT_CHANNEL				CHANNEL_1
#define ELEVATOR_OUTPUT_CHANNEL				CHANNEL_2
#define RUDDER_OUTPUT_CHANNEL				CHANNEL_5
#define AILERON_SECONDARY_OUTPUT_CHANNEL	CHANNEL_4
#define CAMERA_ROLL_OUTPUT_CHANNEL			CHANNEL_UNUSED
#define CAMERA_PITCH_OUTPUT_CHANNEL			CHANNEL_UNUSED
#define CAMERA_YAW_OUTPUT_CHANNEL			CHANNEL_UNUSED


// Camera Stabilization
// To enable, set this value to 1, and assign one or more of the CAMERA_*_OUTPUT_CHANNELS above.
#define USE_CAMERA_STABILIZATION			0


// Servo Reversing Configuration
// Here you can choose which reversing switches use hardware switches, and hard code the rest.
// Note that your servo reversing settings here should match what you set on your transmitter.
// For any of these that evaluate to 1 (either hardcoded or by flipping a switch on the board,
// as you define below), that servo will be sent reversed controls.
#define AILERON_CHANNEL_REVERSED			(HW_SWITCH_1 == 0)
#define ELEVATOR_CHANNEL_REVERSED			(HW_SWITCH_2 == 0)
#define RUDDER_CHANNEL_REVERSED				0	// Hardcoded to be unreversed, since we have only 3 switches.
#define AILERON_SECONDARY_CHANNEL_REVERSED	(HW_SWITCH_3 == 0)
#define THROTTLE_CHANNEL_REVERSED			0
#define CAMERA_ROLL_CHANNEL_REVERSED		0
#define CAMERA_PITCH_CHANNEL_REVERSED		0
#define CAMERA_YAW_CHANNEL_REVERSED			0
