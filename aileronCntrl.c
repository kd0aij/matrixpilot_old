#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"


int yawkp = YAWKP*RMAX ;
int rollkp = ROLLKP*RMAX ;

int rollkd = ROLLKD*RMAX ;

union longww gyroFeedback ;

void aileronCntrl(void)
{
	union longww aileronAccum ;
	union longww dotprod ;
	union longww crossprod ;
	int base ;
	int desiredX ;
	int desiredY ;
	int actualX ;
	int actualY ;

	if ( flags._.radio_on )
	{
		base = pwIn[AILERON_INPUT_CHANNEL] + waggle ;
	}
	else
	{
		base = pwTrim[AILERON_INPUT_CHANNEL] + waggle ;
	}
#ifdef TestGains
	flags._.GPS_steering = 1 ;
#endif 
	if ( flags._.GPS_steering )
	{
#ifdef TestGains
		desiredX = -cosine ( 64 ) ;
		desiredY = sine ( 64 ) ;
#else
		desiredX = -cosine( desired_dir ) ;
		desiredY = sine( desired_dir ) ;
#endif
		actualX = rmat[1] ;
		actualY = rmat[4] ;
		dotprod.WW = __builtin_mulss( actualX , desiredX ) + __builtin_mulss( actualY , desiredY ) ;
		crossprod.WW = __builtin_mulss( actualX , desiredY ) - __builtin_mulss( actualY , desiredX ) ;
		crossprod.WW = crossprod.WW<<2 ;
		if ( dotprod._.W1 > 0 )
		{
			aileronAccum.WW = __builtin_mulss( crossprod._.W1 , yawkp ) ;
		}
		else
		{
			if ( crossprod._.W1 > 0 )
			{
				aileronAccum._.W1 = RMAX*YAWKP/4 ;
			}
			else
			{
				aileronAccum._.W1 = -RMAX*YAWKP/4 ;
			}
		}
	}
	else
	{
		aileronAccum.WW = 0 ;
		gyroFeedback.WW = 0 ;
	}
#ifdef TestGains
	flags._.pitch_feedback = 1 ;
#endif
	
	if ( flags._.pitch_feedback )
	{
		gyroFeedback.WW = __builtin_mulss( rollkd , omega[1] ) ;
		aileronAccum.WW += __builtin_mulss( rmat[6] , rollkp ) ;
	}
	else
	{
		gyroFeedback.WW = 0 ;
	}
	
	//	use channel 1 switch to reverse the polarity of the aileron control feedback
	if ( PORTDbits.RD3 )
	{
		aileronAccum.WW = (long)base + (long)aileronAccum._.W1 - (long)gyroFeedback._.W1 ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( aileronAccum.WW ) ;
	}
	else
	{
		aileronAccum.WW = (long)base - (long)aileronAccum._.W1 + (long)gyroFeedback._.W1 ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( aileronAccum.WW ) ;
	}	
	
	//	use channel 3 switch to reverse the polarity of the secondary aileron
	if ( PORTFbits.RF6 )
	{
		pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)pwOut[AILERON_OUTPUT_CHANNEL] ;
	}
	else
	{
		pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)6000 - (long)pwOut[AILERON_OUTPUT_CHANNEL] ;
	}
	
	return ;
}

