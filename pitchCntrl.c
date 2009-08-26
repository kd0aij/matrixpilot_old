#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

//	If the state machine selects pitch feedback, compute it from the pitch gyro and accelerometer.

int rtlkick = 0 ;

#define RTLKICK RMAX*(RTLPITCHDOWN/57.3)

int pitchgain = PITCHGAIN*RMAX ;

void pitchCntrl(void)
{
	union longww pitchAccum ;
	
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
		pitchAccum.WW = __builtin_mulss( rmat[7] - rtlkick , pitchgain ) ;
	}
	else
	{
		pitchAccum.WW = 0 ;
	}
	
	pitch_control = (long)pitchAccum._.W1 ;
	
	return ;
}
