#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

//	Perform control based on the airframe type.
//	Use the radio to determine the baseline pulse widths if the radio is on.
//	Otherwise, use the trim pulse width measured during power up.


#define REVERSE_IF_NEEDED(NEEDS_REVERSING, VALUE)		((NEEDS_REVERSING) ? (-(VALUE)) : (VALUE))


void servoMix( void )
{
	long temp ;
	
	// If radio is off, use pwTrim values instead of the pwIn values
	if (!flags._.radio_on)
		for (temp = 0; temp < NUM_INPUTS; temp++)
			pwIn[temp] = pwTrim[temp];
	
	// Mix aileron, elevator, and rudder deflections into output channels for each airframe type
	
	// Standard airplane airframe
	// Mix roll_control and waggle into ailerons
	// Mix pitch_control into elevators
	if ( AIRFRAME_TYPE == AIRFRAME_STANDARD )
	{
		temp = (long)pwIn[AILERON_INPUT_CHANNEL] + REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, (long)roll_control + (long)waggle) ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)3000 +
			REVERSE_IF_NEEDED(AILERON_SECONDARY_CHANNEL_REVERSED, (long)pwOut[AILERON_OUTPUT_CHANNEL] - (long)3000) ;
		
		temp = (long)pwIn[ELEVATOR_INPUT_CHANNEL] + REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, (long)pitch_control) ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)pwIn[RUDDER_INPUT_CHANNEL] /*+ REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, (long)yaw_control)*/ ;
		pwOut[RUDDER_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
		
		temp = (long)pwIn[THROTTLE_INPUT_CHANNEL] ;
		pwOut[THROTTLE_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
	}
	
	
	// V-Tail airplane airframe
	// Mix roll_control and waggle into ailerons
	// Mix pitch_control into both elevator and rudder
	else if ( AIRFRAME_TYPE == AIRFRAME_VTAIL )
	{
		temp = (long)pwIn[AILERON_INPUT_CHANNEL] + REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, (long)roll_control + (long)waggle) ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		//	Reverse the polarity of the secondary aileron if necessary
		pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = (long)3000 +
			REVERSE_IF_NEEDED(AILERON_SECONDARY_CHANNEL_REVERSED, (long)pwOut[AILERON_OUTPUT_CHANNEL] - (long)3000) ;
		
		temp = (long)pwIn[ELEVATOR_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, (long)pitch_control /*+ (long)yaw_control*/) ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)pwIn[RUDDER_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, (long)pitch_control /*- (long)yaw_control*/) ;
		pwOut[RUDDER_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)pwIn[THROTTLE_INPUT_CHANNEL] ;
		pwOut[THROTTLE_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
	}	
	
	
	// Delta-Wing airplane airframe
	// Mix roll_control, pitch_control, and waggle into aileron and elevator
	else if ( AIRFRAME_TYPE == AIRFRAME_DELTA )
	{
		temp = (long)pwIn[AILERON_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, (long)roll_control + (long)pitch_control + (long)waggle) ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)pwIn[ELEVATOR_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, -(long)roll_control + (long)pitch_control - (long)waggle) ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)pwIn[RUDDER_INPUT_CHANNEL] /*+ REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, (long)yaw_control)*/ ;
		pwOut[RUDDER_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
		
		temp = (long)pwIn[THROTTLE_INPUT_CHANNEL] ;
		pwOut[THROTTLE_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
	}
	
	
	// Helicopter airframe
	// Mix half of roll_control and half of pitch_control into aileron channels
	// Mix full pitch_control into elevator
	// Ignore waggle for now
	// FIXME: when one channel saturates, fix other channels to compensate?  Or is this not necessary?
	else if ( AIRFRAME_TYPE == AIRFRAME_HELI )
	{
		temp = (long)pwIn[AILERON_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, (long)roll_control/2 + (long)pitch_control/2) ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)pwIn[ELEVATOR_INPUT_CHANNEL] + REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, (long)pitch_control) ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)pwIn[AILERON_SECONDARY_OUTPUT_CHANNEL] + 
			REVERSE_IF_NEEDED(AILERON_SECONDARY_CHANNEL_REVERSED, -(long)roll_control/2 + (long)pitch_control/2) ;
		pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = temp ;
		
		temp = (long)pwIn[RUDDER_INPUT_CHANNEL] /*+ REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, (long)yaw_control)*/ ;
		pwOut[RUDDER_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = (long)pwIn[THROTTLE_INPUT_CHANNEL] ;
		pwOut[THROTTLE_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
	}
}
