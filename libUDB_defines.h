#ifndef UDB_DEFINES_H
#define UDB_DEFINES_H

// Build for the specific board type
#define RED_BOARD		1
#define GREEN_BOARD		2
#define RED_GREEN_BOARD	3	// Test board for Inversense Gyros
#define UDB_2_BOARD		4


// Include the necessary files for the current board type
#if (BOARD_TYPE == RED_BOARD)
#include "p30f4011.h"
#include "ConfigRed.h"

#elif (BOARD_TYPE == GREEN_BOARD)
#include "p30f4011.h"
#include "ConfigGreen.h"

#elif (BOARD_TYPE == RED_GREEN_BOARD)
#include "p30f4011.h"
#include "ConfigIXZ500.h"

#elif (BOARD_TYPE == UDB_2_BOARD)
#include "p33fj256gp710a.h"
#include "ConfigUDB2.h"
#endif


// Types
typedef char boolean;
#define true	1
#define false	0

struct ADchannel {
	int input; // raw input
	int value; // filtered a little bit as part of A/D
	int offset;  // baseline at power up 
};  // variables for processing an AD channel


// LED states
#define LED_ON		0
#define LED_OFF		1


// Channel numbers on the board, mapped to positions in the pulse width arrays.
#define CHANNEL_UNUSED	0	// udb_pwIn[0], udb_pwOut[0], etc. are not used, but allow lazy code everywhere else  :)
#define CHANNEL_1		1
#define CHANNEL_2		2
#define CHANNEL_3		3
#define CHANNEL_4		4
#define CHANNEL_5		5
#define CHANNEL_6		6
#define CHANNEL_7		7
#define CHANNEL_8		8


// Constants
#define tmr1_period 0x2000 // sets time period for timer 1 interrupt to 0.5 seconds
#define FILTERSHIFT 3
#define RMAX   0b0100000000000000	//	1.0 in 2.14 fractional format
#define GRAVITY ((long)(5280.0/SCALEACCEL))  // gravity in AtoD/2 units

#define SERVOCENTER 3000
#define SERVORANGE (int) (SERVOSAT*1000)
#define SERVOMAX SERVOCENTER + SERVORANGE
#define SERVOMIN SERVOCENTER - SERVORANGE

extern int magMessage ;
#endif
