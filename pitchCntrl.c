#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

//	If the state machine selects pitch feedback, compute it from the pitch gyro and accelerometer.

int pitchgain = (int)(PITCHGAIN*RMAX) ;
int pitchrate = 0 ;
int pitchkd = (int) (PITCHKD*RMAX) ;

int pitchbgain = (int)(8.0*PITCHBOOST) ;

int rudderElevMixGain = (int)(RMAX*RUDDERELEVMIX) ;
int rudderElevMix ;

int elevInput ;

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
	
	if ( flags._.pitch_feedback )
	{
		pitchAccum.WW = 	__builtin_mulss( rmat[7] + pitchAltitudeAdjust, pitchgain ) 
						+	__builtin_mulss( pitchkd , pitchrate ) ;
		
		if ( ! ELEVATOR_CHANNEL_REVERSED )
		{
			elevInput = pwIn[ELEVATOR_INPUT_CHANNEL] - pwTrim[ELEVATOR_INPUT_CHANNEL] ;
		}
		else
		{
			elevInput = pwTrim[ELEVATOR_INPUT_CHANNEL] - pwIn[ELEVATOR_INPUT_CHANNEL] ;
		}
				
		pitchboost =  (__builtin_mulss(pitchbgain , ( elevInput ))>>3) ;
		// For now pitchboost is only mixed into standard-no-aileron airframes
	}
	else
	{
		pitchAccum.WW = 0 ;
		pitchboost = 0 ;
	}
	
	pitch_control = (long)pitchAccum._.W1 + rudderElevMix ;
	// Servo reversing is handled in servoMix.c
	
	return ;
}
