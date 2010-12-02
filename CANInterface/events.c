// SEE END OF FILE FOR LICENSING

#include "events.h"
#include "../libUDB/libUDB_internal.h"

//#define _TTRIGGERIP _T1IP
//#define _TTRIGGERIF _T1IF
//#define _TTRIGGERIE _T1IE

#define _TTRIGGERIP _QEIIP
#define _TTRIGGERIF _QEIIF
#define _TTRIGGERIE _QEIIE



#define MAX_EVENTS	8

EVENT	events[MAX_EVENTS];


unsigned int register_event( void (*event_callback) (void) )
{
	int eventIndex;

	for(eventIndex = 0; eventIndex < MAX_EVENTS; eventIndex++)
	{
		if(events[eventIndex].event_callback == NULL)
		{
			events[eventIndex].event_callback = event_callback;
			return eventIndex;
		}
	}

	while(1);		// STOP HERE ON FAILURE.
	return INVALID_HANDLE;
};


void trigger_event(unsigned int hEvent)
{
	events[hEvent].eventPending = true;
	_TTRIGGERIF = 1 ;  // trigger the interrupt
};


void init_events(void)	/* initialize timers */
{
	// The TTRIGGER interrupt is used a software interrupt event trigger
	_TTRIGGERIP = 2 ;		// priority 1
	_TTRIGGERIF = 0 ;		// clear the interrupt
	_TTRIGGERIE = 1 ;		// enable the interrupt

	int eventIndex;

	for(eventIndex = 0; eventIndex < MAX_EVENTS; eventIndex++)
	{
		events[eventIndex].event_callback 	= NULL;
		events[eventIndex].eventPending 	= false;
	}
	
	return ;
}


//  process T1 TRIGGER interrupt = software interrupt
//void __attribute__((__interrupt__,__no_auto_psv__)) _T1Interrupt(void) 
void __attribute__((__interrupt__,__no_auto_psv__)) _QEIInterrupt(void) 
{
	interrupt_save_extended_state ;
	//indicate_loading_inter ;

	int eventIndex;
	EVENT* pEvent;

	_TTRIGGERIF = 0 ;			// clear the interrupt

	for(eventIndex = 0; eventIndex < MAX_EVENTS; eventIndex++)
	{
		pEvent = &events[eventIndex];
		if(pEvent->eventPending == true)
		{
			pEvent->eventPending = false;
			if(pEvent->event_callback != NULL)
			{
				pEvent->event_callback();
			}
		}
	}

	interrupt_restore_extended_state ;
	return ;
}



/*
unsigned char udb_cpu_load(void)
{
	return (unsigned char)(__builtin_muluu(cpu_timer, CPU_LOAD_PERCENT) >> 16) ;
}
*/

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
