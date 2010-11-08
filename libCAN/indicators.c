#include "indicators.h"
#include "libUDB.h"
#include "CANInterface_defines.h"
#include "heartbeat.h"

void indicator_tick_callback(void);


void init_LEDs(void)
{
	TRISDbits.TRISD3 = 0;
	TRISDbits.TRISD2 = 0;

	// Set a timer to callback the indicator function event 250ms
	unsigned int hEvent = register_event(&indicator_tick_callback);
	unsigned int hTimer = register_timer(hEvent);
	set_timer(hTimer, 250, true); 
};


void indicator_tick_callback(void)
{
	if(op_status.passthrough == 1)
	{
		redLEDon();
	}
	else
	{
		redLEDoff();
	}

	if(op_status.rx_ok == 1)
	{
		greenLEDon();
	}
	else
	{
		greenLEDoff();
	}
};

inline void redLEDon(void)
{
	LATDbits.LATD2 = 1;
}; 	

inline void redLEDoff(void)
{
	LATDbits.LATD2 = 0;
}; 	

inline void greenLEDon(void)
{
	LATDbits.LATD3 = 1;
};

inline void greenLEDoff(void)
{
	LATDbits.LATD3 = 0;
};	

