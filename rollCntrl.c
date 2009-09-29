#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

int yawkp = YAWKP*RMAX ;
int rollkp = ROLLKP*RMAX ;

int rollkd = ROLLKD*RMAX ;

union longww gyroRollFeedback ;


void rollCntrl(void)
{
	union longww rollAccum ;
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
			rollAccum.WW = __builtin_mulss( crossprod._.W1 , yawkp ) ;
		}
		else
		{
			if ( crossprod._.W1 > 0 )
			{
				rollAccum._.W1 = yawkp/4 ;
			}
			else
			{
				rollAccum._.W1 = -yawkp/4 ;
			}
		}
	}
	else
	{
		rollAccum.WW = 0 ;
		gyroRollFeedback.WW = 0 ;
	}
#ifdef TestGains
	flags._.pitch_feedback = 1 ;
#endif
	
	if ( flags._.pitch_feedback )
	{
		gyroRollFeedback.WW = __builtin_mulss( rollkd , omegaAccum[1] ) ;
		rollAccum.WW += __builtin_mulss( rmat[6] , rollkp ) ;
	}
	else
	{
		gyroRollFeedback.WW = 0 ;
	}
	
	roll_control = (long)rollAccum._.W1 - (long)gyroRollFeedback._.W1 ;
	// Servo reversing is handled in servoMix.c
	
	return ;
}
