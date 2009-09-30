#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"
#include "options.h"

int throttleIn = 0 ;
int throttleOut = 0 ;
int desiredHeight = 0 ;

union longww throttleFiltered = { 0 } ;

#define THROTTLEFILTSHIFT 12

#define HEIGHTMARGIN 10 // full throttle until height is margin below target
						// min when height is margin above target

#define DEADBAND 150

#define MAXTHROTTLE ((int) 2.0*SERVORANGE*SERVOSAT  )

#define THROTTLEHEIGHTGAIN ( (int ) ( ( (1.0 - MINIMUMTHROTTLE ) * MAXTHROTTLE ) / ( HEIGHTMARGIN ) ) )

#define PITCHATMAX ((long)PITCHATMAXTHROTTLE)*((long)RMAX)/((long)57.3)
#define PITCHATMIN ((long)PITCHATMINTHROTTLE)*((long)RMAX)/((long)57.3)
#define PITCHATZERO ((long)PITCHATZEROTHROTTLE)*((long)RMAX)/((long)57.3)

#define PITCHHEIGHTGAIN ( ( (PITCHATMAX - PITCHATMIN) / ( ( long )(HEIGHTMARGIN*2) ) ) )

#define HEIGHTTHROTTLEGAIN ( (int )  ( ((long) (1.5*HEIGHTMAX)*(long) 1024 ) / ((long) SERVORANGE*(long)SERVOSAT ) ))

int pitchAltitudeAdjust = 0 ;

union longww throttleAccum ;

extern struct waypointparameters goal ;


void altitudeCntrl(void)
{
	if ( flags._.altitude_hold )
	{
		// keep the In and Trim throttle values within 2000-4000 to account for
		// Spektrum receivers using failsafe values below 2000.
		throttleIn = pulsesat( pwIn[THROTTLE_INPUT_CHANNEL] ) - pulsesat( pwTrim[THROTTLE_INPUT_CHANNEL] ) ;
		
		if ( THROTTLE_CHANNEL_REVERSED ) throttleIn = - throttleIn ;
		
		if ( flags._.use_waypoints == 1 )
		{
			desiredHeight = goal.height ;
		}
		else
		{
			desiredHeight =(( __builtin_mulss(  HEIGHTTHROTTLEGAIN, throttleIn ))>>11) ;
		}
		
		if ( throttleIn < DEADBAND )
		{
			pitchAltitudeAdjust = 0 ;
			throttleFiltered.WW += (((long)(pwTrim[THROTTLE_INPUT_CHANNEL] - throttleFiltered._.W1 ))<<THROTTLEFILTSHIFT ) ;
			altitude_control = throttleFiltered._.W1 - pwTrim[THROTTLE_INPUT_CHANNEL] ;
		}
		else
		{
			if ( height < (desiredHeight - HEIGHTMARGIN) )
			{
				throttleAccum.WW = MAXTHROTTLE ;
				pitchAltitudeAdjust = PITCHATMAX ;
			}
			else if ( height > (desiredHeight + HEIGHTMARGIN) )
			{
				throttleAccum.WW = 0 ;
				pitchAltitudeAdjust = PITCHATZERO ;
			}
			else
			{
				throttleAccum.WW = MAXTHROTTLE + __builtin_mulss( THROTTLEHEIGHTGAIN, ( desiredHeight - height - HEIGHTMARGIN ) );
				pitchAltitudeAdjust = PITCHATMAX + PITCHHEIGHTGAIN*( desiredHeight - height - HEIGHTMARGIN ) ;
			}
			
#if (RACING_MODE == 1)
			if ( flags._.GPS_steering )
			{
				throttleAccum.WW = MAXTHROTTLE ;
			}
#endif
			
			// Servo reversing is handled in servoMix.c
			int throttleOut = pulsesat( pwTrim[THROTTLE_INPUT_CHANNEL] - throttleAccum.WW ) ;
			throttleFiltered.WW += (((long)( throttleOut - throttleFiltered._.W1 ))<<THROTTLEFILTSHIFT );
			altitude_control = throttleFiltered._.W1 - pwTrim[THROTTLE_INPUT_CHANNEL] ;
		}
	}
	else
	{
		pitchAltitudeAdjust = 0 ;
		altitude_control = 0 ;
	}
	
	return ;
}
