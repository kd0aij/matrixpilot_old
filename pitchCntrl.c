#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

//	If the state machine selects pitch feedback, compute it from the pitch gyro and accelerometer.

int rtlkick = 0 ;

#define RTLKICK RMAX*(RTLPITCHDOWN/57.3)

int pitchgain = (int)(PITCHGAIN*RMAX) ;
int pitchrate = 0 ;
//int pitchkd = (int)(PITCHKD*RMAX) ;
int pitchkd = 0 ;
//int pitchbgain = (int)(8.0*PITCHBOOST) ;
int pitchbgain = 0 ;

// note: I was using experimenting with pitchkd and PITCHBOOST for a while.
// they are not really needed, so I did not leave them in.
// if you want to try them out, you are welcome to turn them back on. - WJP

int rudderElevMixGain = (int)(RMAX*RUDDERELEVMIX) ;
int rudderElevMix ;


void pitchCntrl(void)
{
	union longww pitchAccum ;
	
	if ( flags._.pitch_feedback && USE_RUDDER_NAV_CONTROL)
	{
		pitchAccum.WW = __builtin_mulss( rmat[6] , rudderElevMixGain ) ;
		pitchAccum.WW = __builtin_mulss( pitchAccum._.W1 , pwOut[RUDDER_OUTPUT_CHANNEL] - pwTrim[RUDDER_INPUT_CHANNEL] ) << 4 ;
		rudderElevMix = pitchAccum._.W1 ;
	}
	else
	{
		rudderElevMix = 0 ;
	}

	pitchAccum.WW = (	__builtin_mulss( rmat[8] , omegagyro[0] )
					-	__builtin_mulss( rmat[6] , omegagyro[2] ))<<1 ;
	pitchrate = pitchAccum._.W1 ;
	
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
		pitchAccum.WW = 	__builtin_mulss( rmat[7] - rtlkick , pitchgain ) 
						+	__builtin_mulss( pitchkd , pitchrate ) ;
		pitchboost =  (__builtin_mulss(pitchbgain , (	pwIn[ELEVATOR_INPUT_CHANNEL] - pwTrim[ELEVATOR_INPUT_CHANNEL] ))>>3) ;
		// For now pitchboost is only mixed into standard-no-aileron airframes
	}
	else
	{
		pitchAccum.WW = 0 ;
		pitchboost = 0 ;
	}
	
	pitch_control = (long)pitchAccum._.W1 + rudderElevMix ;
	
	return ;
}
