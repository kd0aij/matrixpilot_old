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
	aileron_deflection = pwIn[AILERON_INPUT_CHANNEL] - pwTrim[AILERON_INPUT_CHANNEL] ;
	elevator_deflection = pwIn[ELEVATOR_INPUT_CHANNEL] - pwTrim[ELEVATOR_INPUT_CHANNEL] ;
	rudder_deflection = pwIn[RUDDER_INPUT_CHANNEL] - pwTrim[RUDDER_INPUT_CHANNEL] ;
	
	
	// Add roll and pitch control
	// use channel 1 switch to reverse the polarity of the aileron control feedback
	if ( PORTDbits.RD3 == 1 )
		aileron_deflection += roll_control ;
	else
		aileron_deflection += -roll_control ;
		
	//	use channel 2 switch to reverse the polarity of the control feedback
	if ( PORTDbits.RD2 == 1)
		elevator_deflection += pitch_control ;
	else
		elevator_deflection += -pitch_control ;
	
	rudder_deflection = 0 ;
	
	
	// Mix aileron, elevator, and rudder deflections into output channels for each airframe type
	if ( AIRFRAME_TYPE == AIRFRAME_STANDARD )
	{
		temp = (long)(pwTrim[AILERON_INPUT_CHANNEL] + waggle) + (long)aileron_deflection ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		//	use channel 3 switch to reverse the polarity of the secondary aileron
		if ( PORTFbits.RF6 )
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)(pwOut[AILERON_OUTPUT_CHANNEL]) ;
		else
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)6000 - (long)(pwOut[AILERON_OUTPUT_CHANNEL]) ;
		
		temp = (long)(pwTrim[ELEVATOR_INPUT_CHANNEL]) + (long)elevator_deflection ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)(pwTrim[RUDDER_INPUT_CHANNEL]) + (long)rudder_deflection ;
		pwOut[RUDDER_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
	}
	
	
	else if ( AIRFRAME_TYPE == AIRFRAME_VTAIL )
	{
		temp = (long)(pwTrim[AILERON_INPUT_CHANNEL] + waggle) + (long)aileron_deflection ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		//	use channel 3 switch to reverse the polarity of the secondary aileron
		if ( PORTFbits.RF6 )
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)(pwOut[AILERON_OUTPUT_CHANNEL]) ;
		else
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)6000 - (long)(pwOut[AILERON_OUTPUT_CHANNEL]) ;
		
		temp = (long)(pwTrim[ELEVATOR_INPUT_CHANNEL]) + (long)elevator_deflection/2 + (long)rudder_deflection/2 ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)(pwTrim[RUDDER_INPUT_CHANNEL]) + (long)elevator_deflection/2 - (long)rudder_deflection/2 ;
		pwOut[RUDDER_OUTPUT_CHANNEL] = pulsesat( temp ) ;
	}
	
	
	else if ( AIRFRAME_TYPE == AIRFRAME_DELTA )
	{
		temp = (long)(pwTrim[AILERON_INPUT_CHANNEL] + waggle) + (long)aileron_deflection/2 + (long)elevator_deflection/2 ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)(pwTrim[ELEVATOR_INPUT_CHANNEL] - waggle) - (long)aileron_deflection/2 + (long)elevator_deflection/2 ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
	}
	
	
	else if ( AIRFRAME_TYPE == AIRFRAME_HELI )
	{
		temp = (long)(pwTrim[AILERON_INPUT_CHANNEL]) + (long)aileron_deflection/2 + (long)elevator_deflection/2 ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)(pwTrim[ELEVATOR_INPUT_CHANNEL] + waggle) + (long)elevator_deflection ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		//	use channel 3 switch to reverse the polarity of the secondary aileron
		if ( PORTFbits.RF6 )
		{
			temp = (long)(pwTrim[AILERON_SECONDARY_OUTPUT_CHANNEL]) - (long)aileron_deflection/2 + (long)elevator_deflection/2 ;
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = temp ;
		}
		else
		{
			temp = (long)(pwTrim[AILERON_SECONDARY_OUTPUT_CHANNEL]) + (long)aileron_deflection/2 - (long)elevator_deflection/2 ;
			pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = temp ;
		}
		temp = (long)(pwTrim[RUDDER_INPUT_CHANNEL]) + (long)rudder_deflection ;
		pwOut[RUDDER_OUTPUT_CHANNEL] = pulsesat( temp ) ;
	}
}
