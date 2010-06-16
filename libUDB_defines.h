// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009, 2010 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


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


#if (BOARD_TYPE == UDB_2_BOARD)
#define UDB_INCLUDE_CHIP_CONFIG_OPTIONS \
_FOSCSEL(FNOSC_FRCPLL) ;  // fast RC plus PLL \
_FOSC( FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_NONE ) ; \
_FWDT( WDT_OFF ) ;				// no watchdog timer \
_FBORPOR( 	PBOR_OFF & // brown out detection off \
			MCLR_EN &  // enable MCLR \
			RST_PWMPIN & // pwm pins as pwm \
			PWMxH_ACT_HI & // PWMH is active high \
			PWMxL_ACT_HI ) ; // PMWL is active high \
_FGS( CODE_PROT_OFF ) ; // no protection \
_FICD( JTAGEN_OFF & ICS_PGD2 ) ;

#else
#define UDB_INCLUDE_CHIP_CONFIG_OPTIONS \
_FOSC( CSW_FSCM_OFF & HS ) ; 	// external high speed crystal \
_FWDT( WDT_OFF ) ;				// no watchdog timer \
_FBORPOR( 	PBOR_OFF & // brown out detection off \
			MCLR_EN &  // enable MCLR \
			RST_PWMPIN & // pwm pins as pwm \
			PWMxH_ACT_HI & // PWMH is active high \
			PWMxL_ACT_HI ) ; // PMWL is active high \
_FGS( CODE_PROT_OFF ) ; // no protection \
_FICD( 0xC003 ) ;		// normal use of debugging port
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
