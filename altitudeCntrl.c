#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"
#include "options.h"

int throttleIn = 0 ;
int throttleOut = 0 ;
int desiredHeight = 0 ;

union longww throttleFiltered = { 0 } ;

#define THROTTLEFILTSHIFT 12

#define HEIGHTMARGIN 50 // height margin between full on and full off throttle, meters

#define DEADBAND 150

#define MAXTHROTTLE ((int) 2.0*SERVORANGE*SERVOSAT  )

#define THROTTLEHEIGHTGAIN ( (int ) ( ( (1.0 - MINIMUMTHROTTLE ) * MAXTHROTTLE ) / ( HEIGHTMARGIN ) ) )

#define PITCHATMAX ((long)PITCHATMAXTHROTTLE)*((long)RMAX)/((long)57.3)
#define PITCHATMIN ((long)PITCHATMINTHROTTLE)*((long)RMAX)/((long)57.3)
#define PITCHATZERO ((long)PITCHATZEROTHROTTLE)*((long)RMAX)/((long)57.3)

#define PITCHHEIGHTGAIN ( ( (PITCHATMAX - PITCHATMIN) / ( ( long )HEIGHTMARGIN    ) ) )

#define HEIGHTTHROTTLEGAIN ( (int )  ( ((long) (1.5*HEIGHTMAX)*(long) 1024 ) / ((long) SERVORANGE*(long)SERVOSAT ) ))

int pitchAltitudeAdjust = 0 ;

union longww throttleAccum ;

void altitudeCntrl(void)
{
	if ( flags._.altitude_hold )
	{
		throttleIn = pwIn[THROTTLE_INPUT_CHANNEL] - pwTrim[THROTTLE_INPUT_CHANNEL] ;
		if ( THROTTLE_CHANNEL_REVERSED ) throttleIn = - throttleIn ;
		
		desiredHeight =(( __builtin_mulss(  HEIGHTTHROTTLEGAIN, throttleIn ))>>11) - HEIGHTMARGIN ;
		if ( throttleIn < DEADBAND )
		{
			pitchAltitudeAdjust = 0 ;
			pwIn[THROTTLE_INPUT_CHANNEL] = pwTrim[THROTTLE_INPUT_CHANNEL] ;
			throttleFiltered.WW += (((long)(throttleIn - throttleFiltered._.W1 ))<<THROTTLEFILTSHIFT ) ;
			altitude_control = throttleFiltered._.W1 ;
		}
		else
		{
			if ( height < desiredHeight )
			{
				throttleAccum.WW = MAXTHROTTLE ;
				pitchAltitudeAdjust = PITCHATMAX ;
			}
			else if ( height > desiredHeight + HEIGHTMARGIN )
			{
				throttleAccum.WW = 0 ;
				pitchAltitudeAdjust = PITCHATZERO ;
			}
			else
			{
				throttleAccum.WW = MAXTHROTTLE + __builtin_mulss( THROTTLEHEIGHTGAIN, ( desiredHeight - height ) );
				pitchAltitudeAdjust = PITCHATMAX + PITCHHEIGHTGAIN*( desiredHeight - height ) ;
			}
			
			// Servo reversing is handled in servoMix.c
			throttleFiltered.WW += (((long)( throttleAccum.WW - throttleFiltered._.W1 ))<<THROTTLEFILTSHIFT );
			altitude_control = throttleFiltered._.W1 ;
		}
	}
	else
	{
		pitchAltitudeAdjust = 0 ;
		altitude_control = 0 ;
	}
	
	return ;
}
