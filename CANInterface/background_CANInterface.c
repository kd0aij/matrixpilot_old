// SEE END OF FILE FOR LICENSE TERMS

#include "../libUDB/libUDB_internal.h"
#include "Heartbeat.h"
#include "indicators.h"

#define tmr1_period 		0x2000 // sets time period for timer 1 interrupt to 0.5 seconds
#define CPU_LOAD_PERCENT	400   // = (100 / (8192 * 2)) * (256**2)

void cpu_timer_process(void);
unsigned int cpu_timer = 0 ;

unsigned int	hBackgroundEvent = INVALID_HANDLE;
unsigned int	hBackgroundTimer = INVALID_HANDLE;


void udb_init_clock(void)	/* initialize timers */
{
//	TRISF = 0b1111111111101100 ;	// Enable LED outputs

	init_heartbeat();
	init_events();

	// Setup udb_background_trigger to be called every 500ms at low priority
	hBackgroundEvent = register_event(&cpu_timer_process);
	hBackgroundTimer = register_timer(hBackgroundEvent);
	set_timer(hBackgroundTimer, 1000, true);

	// DO NOT DO udb_background_callback_triggered

	// Timer 5 is used to measure time spent per second in interrupt routines
	// which enables the calculation of the CPU loading.
	TMR5 = 0 ; 				// initialize timer
	T5CONbits.TCKPS = 3 ;	// prescaler = 256 option
	T5CONbits.TCS = 0 ;	    // use the crystal to drive the clock
	_T5IE = 0 ;				// disable the interrupt
	
	// Timer 5 will be turned on in interrupt routines and turned off in main()
	T5CONbits.TON = 0 ;		// turn off timer 5
	timer_5_on = 0;
	
	init_LEDs();
	
	return ;
}


void cpu_timer_process(void)
{
	cpu_timer = TMR5 ;
	T5CONbits.TON = 0 ;		// turn off timer 5 
	TMR5 = 0 ;				// reset timer 5 to 0
	T5CONbits.TON = 1 ;		// turn on timer 5
	timer_5_on = 1;
}
	

void udb_background_trigger(void)
{
//	_TTRIGGERIF = 1 ;  // trigger the interrupt
//	Trigger does not run any more
	return ;
}


unsigned char udb_cpu_load(void)
{
	return (unsigned char)(__builtin_muluu(cpu_timer, CPU_LOAD_PERCENT) >> 16) ;
}

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
