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


#include "libUDB_internal.h"

union udb_fbts_byte udb_flags ;

boolean timer_5_on = 0 ;
boolean needSaveExtendedState = 0 ;
int defaultCorcon = 0 ;


void udb_init(void)
{
	defaultCorcon = CORCON ;
	
	udb_flags.B = 0 ;
	
	udb_init_leds() ;
	udb_init_ADC() ;
	udb_init_clock() ;
	udb_init_capture() ;
	udb_init_I2C() ;
	udb_init_GPS() ;
	udb_init_USART() ;
	udb_init_pwm() ;
	SRbits.IPL = 0 ;	// turn on all interrupt priorities
	
	return ;
}


void udb_run(void)
{
	//  nothing else to do... entirely interrupt driven
	while (1)
	{
		// pause cpu counting timer while not in an ISR
		indicate_loading_main ;
	}
	// Never returns
}


void udb_init_leds( void )
{
	
#if (BOARD_TYPE == UDB3_BOARD)
	_TRISE1 = _TRISE2 = _TRISE3 = _TRISE4 = 0 ;
	
#elif (BOARD_TYPE == GREEN_BOARD || BOARD_TYPE == RED_BOARD || BOARD_TYPE == RED_GREEN_BOARD)
	TRISFbits.TRISF0 = 0 ;
#endif
	
	return ;
}


// the compiler does not respect the resource used by the Microchip math
// library, so interrupts need to save and restore extended state, and
// reset CORCON if firing in the middle of a math lib call.
void udb_setDSPLibInUse(boolean inUse)
{
	needSaveExtendedState = inUse ;
	return ;
}
