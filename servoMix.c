#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

//	Perform control based on the airframe type.
//	Use the radio to determine the baseline pulse widths if the radio is on.
//	Otherwise, use the trim pulse width measured during power up.
//
//	Mix computed roll and pitch controls into the output channels for the compiled airframe type


void servoMix( void )
{
	long temp ;
	int pwManual[MAX_INPUTS+1] ;
	
	// If radio is off, use pwTrim values instead of the pwIn values
	for (temp = 1; temp <= NUM_INPUTS; temp++)
		if (flags._.radio_on)
			pwManual[temp] = pwIn[temp];
		else
			pwManual[temp] = pwTrim[temp];
	
	
	// Standard airplane airframe
	// Mix roll_control and waggle into ailerons
	// Mix pitch_control into elevators
#if ( AIRFRAME_TYPE == AIRFRAME_STANDARD )
		temp = pwManual[AILERON_INPUT_CHANNEL] + REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, roll_control + waggle) ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = 3000 +
			REVERSE_IF_NEEDED(AILERON_SECONDARY_CHANNEL_REVERSED, pwOut[AILERON_OUTPUT_CHANNEL] - 3000) ;
		
		temp = pwManual[ELEVATOR_INPUT_CHANNEL] + REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, pitch_control) ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = pwManual[RUDDER_INPUT_CHANNEL] /*+ REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, yaw_control)*/ ;
		pwOut[RUDDER_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
		
		temp = pwManual[THROTTLE_INPUT_CHANNEL] + REVERSE_IF_NEEDED(THROTTLE_CHANNEL_REVERSED, altitude_control) ;
		pwOut[THROTTLE_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
#endif
	
	
	// V-Tail airplane airframe
	// Mix roll_control and waggle into ailerons
	// Mix pitch_control into both elevator and rudder
#if ( AIRFRAME_TYPE == AIRFRAME_VTAIL )
		temp = pwManual[AILERON_INPUT_CHANNEL] + REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, roll_control + waggle) ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		//	Reverse the polarity of the secondary aileron if necessary
		pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = 3000 +
			REVERSE_IF_NEEDED(AILERON_SECONDARY_CHANNEL_REVERSED, pwOut[AILERON_OUTPUT_CHANNEL] - 3000) ;
		
		temp = pwManual[ELEVATOR_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, pitch_control /*+ yaw_control*/) ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = pwManual[RUDDER_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, pitch_control /*- yaw_control*/) ;
		pwOut[RUDDER_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = pwManual[THROTTLE_INPUT_CHANNEL] + REVERSE_IF_NEEDED(THROTTLE_CHANNEL_REVERSED, altitude_control) ;
		pwOut[THROTTLE_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
#endif
	
	
	// Delta-Wing airplane airframe
	// Mix roll_control, pitch_control, and waggle into aileron and elevator
#if ( AIRFRAME_TYPE == AIRFRAME_DELTA )
		temp = pwManual[AILERON_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, roll_control + pitch_control + waggle) ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = pwManual[ELEVATOR_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, -roll_control + pitch_control - waggle) ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = pwManual[RUDDER_INPUT_CHANNEL] /*+ REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, yaw_control)*/ ;
		pwOut[RUDDER_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
		
		temp = pwManual[THROTTLE_INPUT_CHANNEL] + REVERSE_IF_NEEDED(THROTTLE_CHANNEL_REVERSED, altitude_control) ;
		pwOut[THROTTLE_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
#endif
	
	
	// Standard airplane airframe with no ailerons (using MatrixNav style rudder navigation)
	// Mix pitch_control into elevators
	// Mix yaw control into rudder
#if ( AIRFRAME_TYPE == AIRFRAME_STANDARD_NOAIL )
		temp = pwManual[AILERON_INPUT_CHANNEL] ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = 3000 +
			REVERSE_IF_NEEDED(AILERON_SECONDARY_CHANNEL_REVERSED, pwOut[AILERON_OUTPUT_CHANNEL] - 3000) ;
		
		temp = pwManual[ELEVATOR_INPUT_CHANNEL] + REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, pitch_control) + pitchboost;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = pwManual[RUDDER_INPUT_CHANNEL] + REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, yaw_control + waggle) + yawboost;
		pwOut[RUDDER_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
		
		temp = pwManual[THROTTLE_INPUT_CHANNEL] + REVERSE_IF_NEEDED(THROTTLE_CHANNEL_REVERSED, altitude_control) ;
		pwOut[THROTTLE_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
#endif
	
	
	// V-Tail airplane airframe with no ailerons (using MatrixNav style rudder navigation)
	// Mix pitch_control and yaw_control into both elevator and rudder
#if ( AIRFRAME_TYPE == AIRFRAME_VTAIL_NOAIL )
		temp = pwManual[AILERON_INPUT_CHANNEL] ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		//	Reverse the polarity of the secondary aileron if necessary
		pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = 3000 +
			REVERSE_IF_NEEDED(AILERON_SECONDARY_CHANNEL_REVERSED, pwOut[AILERON_OUTPUT_CHANNEL] - 3000) ;
		
		temp = pwManual[ELEVATOR_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, pitch_control + yaw_control) ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = pwManual[RUDDER_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, pitch_control - yaw_control) ;
		pwOut[RUDDER_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = pwManual[THROTTLE_INPUT_CHANNEL] + REVERSE_IF_NEEDED(THROTTLE_CHANNEL_REVERSED, altitude_control) ;
		pwOut[THROTTLE_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
#endif
	
	
	// Helicopter airframe
	// Mix half of roll_control and half of pitch_control into aileron channels
	// Mix full pitch_control into elevator
	// Ignore waggle for now
	// FIXME: when one channel saturates, fix other channels to compensate?  Or is this not necessary?
#if ( AIRFRAME_TYPE == AIRFRAME_HELI )
		temp = pwManual[AILERON_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, roll_control/2 + pitch_control/2) ;
		pwOut[AILERON_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = pwManual[ELEVATOR_INPUT_CHANNEL] + REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, pitch_control) ;
		pwOut[ELEVATOR_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = pwManual[AILERON_SECONDARY_OUTPUT_CHANNEL] + 
			REVERSE_IF_NEEDED(AILERON_SECONDARY_CHANNEL_REVERSED, -roll_control/2 + pitch_control/2) ;
		pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = temp ;
		
		temp = pwManual[RUDDER_INPUT_CHANNEL] /*+ REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, yaw_control)*/ ;
		pwOut[RUDDER_OUTPUT_CHANNEL] = pulsesat( temp ) ;
		
		temp = pwManual[THROTTLE_INPUT_CHANNEL] + REVERSE_IF_NEEDED(THROTTLE_CHANNEL_REVERSED, altitude_control) ;
		pwOut[THROTTLE_OUTPUT_CHANNEL] =  pulsesat( temp ) ;
#endif
}
