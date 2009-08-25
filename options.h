#include "definesUAVDB.h"

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

#define ACCTAU 200 // in milliseconds
#define RATETAU 100

#define ACCTBYTAU 5120/ACCTAU	// 256*(time_step/time_constant)
#define RATETBYTAU 5120/RATETAU

#define indicate_loading_main 	//LATEbits.LATE0 = 0
#define indicate_loading_inter	//LATEbits.LATE0 = 1

// Choose your airframe type: AIRFRAME_STANDARD, AIRFRAME_VTAIL, or AIRFRAME_DELTA
#define AIRFRAME_TYPE		AIRFRAME_STANDARD


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
#define THROTTLE_OUTPUT_CHANNEL				CHANNEL_5
#define AILERON_OUTPUT_CHANNEL				CHANNEL_1
#define ELEVATOR_OUTPUT_CHANNEL				CHANNEL_2
#define RUDDER_OUTPUT_CHANNEL				CHANNEL_4
#define AILERON_SECONDARY_OUTPUT_CHANNEL	CHANNEL_3
#define UNUSED_OUTPUT_CHANNEL				CHANNEL_6


// Servo Reversing Configuration
// Here you can choose which reversing switches use hardware switches, and hard code the rest.
// For any of these that evaluate to 1, that servo will be sent reversed controls.
#define AILERON_CHANNEL_REVERSED			(HW_SWITCH_1 == 0)
#define ELEVATOR_CHANNEL_REVERSED			(HW_SWITCH_2 == 0)
#define RUDDER_CHANNEL_REVERSED				(HW_SWITCH_3 == 0)
#define AILERON_SECONDARY_CHANNEL_REVERSED	1	// Hardcoded to be reversed, since we have only 3 switches.
