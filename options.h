#ifdef ConfigRed
#include "ConfigRed.h"
#endif

#ifdef ConfigGreen
#include "ConfigGreen.h"
#endif 
 
#define tmr1_period 0x6000 // sets time period for timer 1 interrupt to 1.5 seconds
//#define FILTERSHIFT 6 // filter shift divide
#define FILTERSHIFT 3 
#define LONGDEG_2_BYTECIR 305 // = (256/360)*((256)**4)/(10**7)
#define COURSEDEG_2_BYTECIR 466 // = (256/360)*((256)**2)/(10**2)
#define CALIB_PAUSE 4
#define STANDBY_PAUSE 16 
#define WAGGLE 300

#define ACCTAU 200 // in milliseconds
#define RATETAU 100

#define ACCTBYTAU 5120/ACCTAU	// 256*(time_step/time_constant)
#define RATETBYTAU 5120/RATETAU

#define indicate_loading_main
#define indicate_loading_inter
//#define indicate_loading_main LATEbits.LATE0 = 0
//#define indicate_loading_inter LATEbits.LATE0 = 1


// Channel numbers on the board, mapped to positions in the pulse width arrays.
// Don't edit these.  :)
#define CHANNEL_1 0
#define CHANNEL_2 1
#define CHANNEL_3 2
#define CHANNEL_4 3
#define CHANNEL_5 4
#define CHANNEL_6 5


// NUM_INPUTS: Set to 4 or 5 
//   4 enables only the standard 4 input channels
//   5 also enables E8 as the 5th input channel
#define NUM_INPUTS	5


// NUM_OUTPUTS: Set to 3, 4, 5, or 6
//   3 enables only the standard 3 output channels
//   4 also enables E0 as the 4th output channel
//   5 also enables E2 as the 5th output channel
//   6 also enables E4 as the 6th output channel
#define NUM_OUTPUTS	6


// Channel numbers for each input.
// Use as is, or edit to match your setup.
#define THROTTLE_INPUT_CHANNEL				CHANNEL_3
#define AILERON_INPUT_CHANNEL				CHANNEL_1
#define ELEVATOR_INPUT_CHANNEL				CHANNEL_2
#define RUDDER_INPUT_CHANNEL				CHANNEL_5
#define MODE_SWITCH_INPUT_CHANNEL			CHANNEL_4


// Channel numbers for each output
// Use as is, or edit to match your setup.
#define THROTTLE_OUTPUT_CHANNEL				CHANNEL_3
#define AILERON_OUTPUT_CHANNEL				CHANNEL_1	// Switch polarity with switch 1
#define ELEVATOR_OUTPUT_CHANNEL				CHANNEL_2	// Switch polarity with switch 2
#define RUDDER_OUTPUT_CHANNEL				CHANNEL_4
#define AILERON_SECONDARY_OUTPUT_CHANNEL	CHANNEL_5	// Switch polarity relative to the primary aileron channel with switch 3
#define UNUSED_OUTPUT_CHANNEL				CHANNEL_6
