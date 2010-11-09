// SEE END OF FILE FOR LICENSE TERMS

#include "../libUDB/libUDB_internal.h"
#include "CANInterfaceOptions.h"
#include "heartbeat.h"

volatile unsigned int tickCount = 0;

#define MAX_TIMERS 8

TIMER	timers[MAX_TIMERS];

inline unsigned int getHeartbeatTick(void)
{
	return tickCount;
}

//  process T3 interrupt

void __attribute__((__interrupt__,__no_auto_psv__)) _T3Interrupt(void) 
{
	unsigned char timerIndex;
	TIMER* pTimer;

//	interrupt_save_extended_state ;
	indicate_loading_inter ;

	tickCount++;

	radio_heartbeat_callback(tickCount);

	for(timerIndex = 0; timerIndex < MAX_TIMERS; timerIndex++)
	{
		pTimer = &timers[timerIndex];
		if(pTimer->active == true)
		{
			if(pTimer->timeout == tickCount)
			{
				if(pTimer->repeat == 0)
				{
					pTimer->active = false;
				}
				else
				{
					pTimer->timeout = tickCount + pTimer->repeat;
				}
				trigger_event(pTimer->hEvent);
			}
		}
	}
		
	IFS0bits.T3IF = 0 ;			// clear the interrupt
	
//	interrupt_restore_extended_state ;
	return ;
}


void init_heartbeat(void)
{
	unsigned int timerIndex;

	for(timerIndex = 0; timerIndex < MAX_TIMERS; timerIndex++)
	{
		timers[timerIndex].hEvent = INVALID_HANDLE;
		timers[timerIndex].active = false;
	};

	// Timer 1 is used as a 1ms heartbeat timer
	TMR3 = 0 ;					// initialize timer'
	PR3	= HEARTBEAT_PERIOD;		// Set frame timeout time
	T3CONbits.TCKPS = 2 ;		// prescaler = 64 option
	T3CONbits.TCS = 0 ;	    	// use the XTAL/PLL to drive the clock
	_T3IP = 5 ;					// heartbeat priority 5
	_T3IE = 1 ;					// enable the interrupt
	T3CONbits.TON = 1 ;			// turn on timer 3

}
 
// Register a timer with a handle to a related event
// return a handle to the timer regsitered
// return an invalid handle if there is no space for an extra timer
unsigned int register_timer(unsigned int hEvent)
{
	int timerIndex;

	for(timerIndex = 0; timerIndex < MAX_TIMERS; timerIndex++)
	{
		if(timers[timerIndex].hEvent == INVALID_HANDLE)
		{
			timers[timerIndex].hEvent = hEvent;
			return timerIndex;
		}
	}
	
	while(1);		// STOP HERE ON FAILURE
	return INVALID_HANDLE;
};

void set_timer(unsigned int hTimer, unsigned int period, boolean repeat)
{
	TIMER* pTimer = &timers[hTimer];
	
	if(repeat == true)
		pTimer->repeat = period;
	else
		pTimer->repeat = 0;
		
	pTimer->timeout = tickCount + period;
	pTimer->active = true;
};


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
