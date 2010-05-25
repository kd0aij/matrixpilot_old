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

extern boolean needSaveExtendedState ;
extern boolean timer_5_on ;

extern int defaultCorcon ;
extern unsigned int cpu_timer ;
extern int magMessage ;

//#define indicate_loading_main		//LATEbits.LATE4 = 0
//#define indicate_loading_inter	//LATEbits.LATE4 = 1

// Empirical results show that reading and writing to the
// "Timer On" function loses clock cycles in the timer. 
// So the software makes a test using a parallel variable
// called timer_5_on.
#define indicate_loading_inter		if ( timer_5_on == 0 )	\
									{						\
										T5CONbits.TON = 1 ;	\
										timer_5_on = 1 ;	\
									}

#define indicate_loading_main		if ( timer_5_on == 1 )	\
									{						\
										T5CONbits.TON = 0 ;	\
										timer_5_on = 0 ;	\
									}


// When ISRs fire during dsp math calls, state is not preserved properly, so we
// have to help preserve extra register state on entry and exit from ISRs.
// In addition, the dsp math calls change and restore CORCON internally, so
// if we fire an ISR in the middle of a dsp math call, CORCON can be set to
// an unexpected value, so we also restore CORCON to the application default,
// which we save in main().  We keep track of whether or not we're running dsp
// calls in needSaveExtendedState var, and only perform these actions if so.
#define interrupt_save_extended_state \
	{ \
		if (needSaveExtendedState) { \
			__asm__("push CORCON"); \
			__asm__("push SR"); \
			__asm__("push MODCON"); \
			__asm__("push XBREV"); \
			__asm__("push ACCAL"); \
			__asm__("push ACCAH"); \
			__asm__("push ACCAU"); \
			__asm__("push ACCBL"); \
			__asm__("push ACCBH"); \
			__asm__("push ACCBU"); \
			__asm__("push RCOUNT"); \
			__asm__("push DCOUNT"); \
			__asm__("push DOSTARTL"); \
			__asm__("push DOSTARTH"); \
			__asm__("push DOENDL"); \
			__asm__("push DOENDH"); \
			int asmDoRestoreExtendedState = 1; \
			__asm__("push %0" : "+r"(asmDoRestoreExtendedState)); \
			CORCON = defaultCorcon; \
			needSaveExtendedState = 0; \
		} \
		else \
		{ \
			int asmDoRestoreExtendedState = 0; \
			__asm__("push %0" : "+r"(asmDoRestoreExtendedState)); \
		} \
	}

#define interrupt_restore_extended_state \
	{ \
		int asmDoRestoreExtendedState; \
		__asm__("pop %0" : "+r"(asmDoRestoreExtendedState)); \
		if (asmDoRestoreExtendedState) { \
			__asm__("pop DOENDH"); \
			__asm__("pop DOENDL"); \
			__asm__("pop DOSTARTH"); \
			__asm__("pop DOSTARTL"); \
			__asm__("pop DCOUNT"); \
			__asm__("pop RCOUNT"); \
			__asm__("pop ACCBU"); \
			__asm__("pop ACCBH"); \
			__asm__("pop ACCBL"); \
			__asm__("pop ACCAU"); \
			__asm__("pop ACCAH"); \
			__asm__("pop ACCAL"); \
			__asm__("pop XBREV"); \
			__asm__("pop MODCON"); \
			__asm__("pop SR"); \
			__asm__("pop CORCON"); \
			needSaveExtendedState = 1; \
		} \
	}

#endif
