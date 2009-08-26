#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

// Only build this code if we don't have ailerons to control
#if USE_MATRIX_NAV_CONTROL


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
		gyroYawFeedback.WW = __builtin_mulss( YAWKD_M , omega[2] ) ;
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
			yawAccum.WW = __builtin_mulss( crossprod._.W1 , YAWKP_M ) ;
		}
		else
		{
			if ( crossprod._.W1 > 0 )
			{
				yawAccum._.W1 = YAWKP_M/4 ;
			}
			else
			{
				yawAccum._.W1 = -YAWKP_M/4 ;
			}
		}
	}
	else
	{
		yawAccum.WW = 0 ;
		gyroYawFeedback.WW = 0 ;
	}
	
	yaw_control = (long)yawAccum._.W1 - (long)gyroYawFeedback._.W1 ;
	
	return ;
}

#endif
