#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

//	Perform control based on the airframe type.
//	Use the radio to determine the baseline pulse widths if the radio is on.
//	Otherwise, use the trim pulse width measured during power up.


void servoMix( void )
{
	long temp ;
	int aileron_deflection ;
	int elevator_deflection ;
	int rudder_deflection ;
	
	// Set up the baseline deflections to include the manual adjustments
	// roll_control and pitch_control are already reversed if necessary
	aileron_deflection = pwIn[AILERON_INPUT_CHANNEL] - pwTrim[AILERON_INPUT_CHANNEL] + roll_control;
	elevator_deflection = pwIn[ELEVATOR_INPUT_CHANNEL] - pwTrim[ELEVATOR_INPUT_CHANNEL] + pitch_control;
	rudder_deflection = pwIn[RUDDER_INPUT_CHANNEL] - pwTrim[RUDDER_INPUT_CHANNEL] ;
	
	// Mix aileron, elevator, and rudder deflections into output channels for each airframe type
	if ( AIRFRAME_TYPE == AIRFRAME_STANDARD )
	{
		temp = (long)pwTrim[AILERON_INPUT_CHANNEL] + (long)aileron_deflection + (long)waggle;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		//	Reverse the polarity of the secondary aileron if necessary
		if ( !AILERON_SECONDARY_CHANNEL_REVERSED )
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)pwOut[AILERON_OUTPUT_CHANNEL] ;
		else
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)6000 - (long)pwOut[AILERON_OUTPUT_CHANNEL] ;
		
		temp = (long)pwTrim[ELEVATOR_INPUT_CHANNEL] + (long)elevator_deflection ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)pwTrim[RUDDER_INPUT_CHANNEL] + (long)rudder_deflection ;
		pwOut[RUDDER_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
	}
	
	
	else if ( AIRFRAME_TYPE == AIRFRAME_VTAIL )
	{
		temp = (long)pwTrim[AILERON_INPUT_CHANNEL] + (long)aileron_deflection + (long)waggle ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		//	Reverse the polarity of the secondary aileron if necessary
		if ( !AILERON_SECONDARY_CHANNEL_REVERSED )
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)pwOut[AILERON_OUTPUT_CHANNEL] ;
		else
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)6000 - (long)pwOut[AILERON_OUTPUT_CHANNEL] ;
		
		//	Take into account the possible reversal of the rudder channel
		if ( !RUDDER_CHANNEL_REVERSED )
		{
			temp = (long)pwTrim[ELEVATOR_INPUT_CHANNEL] + (long)elevator_deflection/2 + (long)rudder_deflection/2 ;
			pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
			
			temp = (long)pwTrim[RUDDER_INPUT_CHANNEL] + (long)elevator_deflection/2 - (long)rudder_deflection/2 ;
			pwOut[RUDDER_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		}
		else
		{
			temp = (long)pwTrim[ELEVATOR_INPUT_CHANNEL] + (long)elevator_deflection/2 - (long)rudder_deflection/2 ;
			pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
			
			temp = (long)pwTrim[RUDDER_INPUT_CHANNEL] - (long)elevator_deflection/2 - (long)rudder_deflection/2 ;
			pwOut[RUDDER_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		}
	}	
	
	else if ( AIRFRAME_TYPE == AIRFRAME_DELTA )
	{
		temp = (long)pwTrim[AILERON_INPUT_CHANNEL] + (long)aileron_deflection/2 + (long)elevator_deflection/2 + (long)waggle ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)pwTrim[ELEVATOR_INPUT_CHANNEL] - (long)aileron_deflection/2 + (long)elevator_deflection/2 - (long)waggle ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
	}
	
	
	else if ( AIRFRAME_TYPE == AIRFRAME_HELI )
	{
		temp = (long)pwTrim[AILERON_INPUT_CHANNEL] + (long)aileron_deflection/2 + (long)elevator_deflection/2 ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)pwTrim[ELEVATOR_INPUT_CHANNEL] + (long)elevator_deflection ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		//	Reverse the polarity of the secondary aileron if necessary
		if ( !AILERON_SECONDARY_CHANNEL_REVERSED )
		{
			temp = (long)pwTrim[AILERON_SECONDARY_OUTPUT_CHANNEL] - (long)aileron_deflection/2 + (long)elevator_deflection/2 ;
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = temp ;
		}
		else
		{
			temp = (long)pwTrim[AILERON_SECONDARY_OUTPUT_CHANNEL] + (long)aileron_deflection/2 - (long)elevator_deflection/2 ;
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = temp ;
		}
		temp = (long)pwTrim[RUDDER_INPUT_CHANNEL] + (long)rudder_deflection ;
		pwOut[RUDDER_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		// FIXME: when one channel saturates in HELI mixing, fix other channels to compensate
	}
}
