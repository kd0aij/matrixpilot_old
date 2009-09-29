#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

extern int yawkp ;

int yawkd = YAWKD*RMAX ;

int yawbgain = (int)(8.0*YAWBOOST) ;

union longww gyroYawFeedback ;


void yawCntrl(void)
{
	union longww yawAccum ;
	union longww dotprod ;
	union longww crossprod ;
	int desiredX ;
	int desiredY ;
	int actualX ;
	int actualY ;

#ifdef TestGains
	flags._.GPS_steering = 1 ;
#endif 
	if ( flags._.GPS_steering )
	{
#ifdef TestGains
		desiredX = -cosine ( 0 ) ;
		desiredY = sine ( 0 ) ;
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
			yawAccum.WW = __builtin_mulss( crossprod._.W1 , yawkp ) ;
		}
		else
		{
			if ( crossprod._.W1 > 0 )
			{
				yawAccum._.W1 = RMAX*YAWKP/4 ;
			}
			else
			{
				yawAccum._.W1 = -RMAX*YAWKP/4 ;
			}
		}
	}
	else
	{
		yawAccum.WW = 0 ;
	}
	if ( flags._.GPS_steering || flags._.pitch_feedback )
	{
		gyroYawFeedback.WW = __builtin_mulss( yawkd , omegaAccum[2] ) ;
		yawboost = ( __builtin_mulss( yawbgain , ( pwIn[RUDDER_INPUT_CHANNEL] - pwTrim[RUDDER_INPUT_CHANNEL] ) ))>>3 ;
		// For now yawboost is only mixed into standard-no-aileron airframes
	}
	else
	{
		gyroYawFeedback.WW = 0 ;
		yawboost = 0 ;
	}
	
	yaw_control = (long)yawAccum._.W1 - (long)gyroYawFeedback._.W1 ;
	// Servo reversing is handled in servoMix.c
	
	return ;
}
