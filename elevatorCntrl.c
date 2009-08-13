#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

//	Perform elevator control.
//	Use the radio to determine the baseline pulse width if the radio is on.
//	Otherwise, use the "trim" pulse width measured during power up.

//	If the state machine selects pitch feedback, compute it from the pitch gyro and accelerometer.

int rtlkick = 0 ;

#define RTLKICK RMAX*(RTLPITCHDOWN/57.3)

int pitchgain = PITCHGAIN*RMAX ;

void elevatorCntrl(void)
{
	union longww elevAccum ;
	int base ;
	
	if ( flags._.radio_on )
	{
		base = pwIn[ELEVATOR_INPUT_CHANNEL] ;
	}
	else
	{
		base = pwTrim[ELEVATOR_INPUT_CHANNEL] ;
	}
#ifdef TestGains
	flags._.GPS_steering = 1 ;
	flags._.pitch_feedback = 1 ;
#endif 
	if ( flags._.GPS_steering )
	{
		rtlkick = RTLKICK ;
	}
	else
	{
		rtlkick = 0 ;
	}
	if ( flags._.pitch_feedback )
	{
		elevAccum.WW = __builtin_mulss( rmat[7] - rtlkick , pitchgain ) ;
	}
	else
	{
		elevAccum.WW = 0 ;
	}

	//	use channel 2 switch to reverse the polarity of the control feedback
	if ( PORTDbits.RD2 )
	{
		elevAccum.WW = (long)base + (long)elevAccum._.W1 ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( elevAccum.WW ) ;
	}
	else
	{
		elevAccum.WW = (long)base - (long)elevAccum._.W1 ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( elevAccum.WW ) ;
	}
	return ;
}
