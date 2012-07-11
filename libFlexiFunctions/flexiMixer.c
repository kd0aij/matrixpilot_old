#include "..\MatrixPilot\defines.h"
#include "..\MatrixPilot\fbwCntrl.h"
#include "..\MatrixPilot\mode_switch.h"
#include "flexifunction_options.h"
#include "flexiFunctionTypes.h"
#include "flexiFunctionRegisters.h"
#include "flexifunctionServices.h"


#define RMAX15 0b0110000000000000	//	1.5 in 2.14 format
#define RMAX   0b0100000000000000	//	1.0 in 2.14 format

// Mixer registers
fractional flexiFunction_registers[FLEXIFUNCTION_MAX_REGS];
//
//// Turn PWM into fraction subtracting the offset
//fractional PWM_to_frac(int PWM, int offset)
//{
//	union longww temp;
//	temp.WW = ( (RMAX * 256.0) / ( MIX_PWM_RANGE ) );
//	temp.WW = __builtin_mulss( PWM - offset, temp._.W0);  //
//	temp.WW >>= 8;
//	return (fractional) temp._.W0;
//};
//
void preMix( void )
{
//	int				index;

/*	// Reset all registers to zero.  MUST BE STATELESS.
	for(index = 0; index < REG_MAX; index++)
	{
		flexiFunction_registers[index] = 0;
	}
*/

	// If radio is off, use udb_pwTrim values instead of the udb_pwIn values
	if (udb_flags._.radio_on)
	{
		// Scale throttle to 0 to MIX_PWM_RANGE instead of 0 to 2 * MIX_PWM_RANGE
		// This stops the fractional overflowing 2*RMAX
		int tempThrottle = 0;

		if(udb_pwIn[THROTTLE_INPUT_CHANNEL] < udb_pwTrim[THROTTLE_INPUT_CHANNEL])
			tempThrottle = 0;
		else
			tempThrottle = udb_pwIn[THROTTLE_INPUT_CHANNEL] - udb_pwTrim[THROTTLE_INPUT_CHANNEL];

		tempThrottle = tempThrottle >> 1;

		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_ROLL)] = 
			PWM_to_frac(udb_pwIn[ROLL_INPUT_CHANNEL], 	udb_pwTrim[ROLL_INPUT_CHANNEL], false);

		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_PITCH)] = 
			PWM_to_frac(udb_pwIn[PITCH_INPUT_CHANNEL], 	udb_pwTrim[PITCH_INPUT_CHANNEL], false);

		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_THROTTLE)] = 
			PWM_to_frac(tempThrottle, 0, false);

		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_YAW)] = 
			PWM_to_frac(udb_pwIn[YAW_INPUT_CHANNEL], 		udb_pwTrim[YAW_INPUT_CHANNEL], false);
		
		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_CAMBER)] =
			PWM_to_frac(udb_pwIn[CAMBER_INPUT_CHANNEL], 	udb_pwTrim[CAMBER_INPUT_CHANNEL], false);

		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_BRAKE)] =
			PWM_to_frac(udb_pwIn[BRAKE_INPUT_CHANNEL], 	udb_pwTrim[BRAKE_INPUT_CHANNEL], false);

		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_FLAP)] = 
			PWM_to_frac(udb_pwIn[FLAP_INPUT_CHANNEL], 	udb_pwTrim[FLAP_INPUT_CHANNEL], false);
	}
	else
	{
		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_ROLL)]	 	= 0;
		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_PITCH)] 		= 0;
		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_THROTTLE)] 	= 0;
		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_YAW)] 		= 0;
		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_CAMBER)]		= 0;
		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_BRAKE)]		= 0;
		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_FLAP)]		= 0;
	}

	boolean apmode_full = 
		( dcm_flags._.nav_capable & 
			( udb_pwIn[MODE_SWITCH_INPUT_CHANNEL] > MODE_SWITCH_THRESHOLD_HIGH ) ) |
		( dcm_flags._.nav_capable & !udb_flags._.radio_on);
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_APMODE_FULL)] = apmode_full;

	boolean manual_mode = 
		!( udb_pwIn[MODE_SWITCH_INPUT_CHANNEL] > MODE_SWITCH_THRESHOLD_HIGH ) & 
		!( udb_pwIn[MODE_SWITCH_INPUT_CHANNEL] > MODE_SWITCH_THRESHOLD_LOW );
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_RADIO_MANUAL_MODE)]= manual_mode;

	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_APMODE_RADIO_ON)] = 
		udb_flags._.radio_on;

	if( !apmode_full & 
		!manual_mode )
		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_GAIN_MAN_MIX)] = RMAX;
	else
		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_GAIN_MAN_MIX)] = 0;

#if(USE_FBW == 1)
	if( (fbwManualControlLockout(IN_CNTRL_ROLL) == true) && (flight_mode_switch_auto() == 1) )
		flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_ROLL)]	 	= 0;
#endif //(USE_FBW == 1)

	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_APCON_ROLL)]		= PWM_to_frac(roll_control,0, false);
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_APCON_PITCH)]		= PWM_to_frac(pitch_control,0, false);
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_APCON_YAW)]		= PWM_to_frac(yaw_control,0, false);
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_APCON_THROTTLE)]	= PWM_to_frac(throttle_control,0, false);
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_APCON_WAGGLE)]	= PWM_to_frac(waggle,0, false);
//
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_TRIM_POINT)] 		= udb_pwTrim[ROLL_INPUT_CHANNEL];
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_TRIM_THROTTLE)] 	= udb_pwTrim[THROTTLE_INPUT_CHANNEL];
}


void postMix( void )
{
	udb_pwOut[AILERON_LEFT_OUTPUT_CHANNEL] 	= udb_servo_pulsesat( (int) flexiFunction_registers[get_output_register_index_from_directory(VIRTUAL_OUTPUT_AILERON_L)] );
	udb_pwOut[ELEVATOR_OUTPUT_CHANNEL] 		= udb_servo_pulsesat( (int) flexiFunction_registers[get_output_register_index_from_directory(VIRTUAL_OUTPUT_ELEVATOR)] );
	udb_pwOut[RUDDER_OUTPUT_CHANNEL] 		= udb_servo_pulsesat( (int) flexiFunction_registers[get_output_register_index_from_directory(VIRTUAL_OUTPUT_RUDDER)] );
	udb_pwOut[AILERON_RIGHT_OUTPUT_CHANNEL] = udb_servo_pulsesat( (int) flexiFunction_registers[get_output_register_index_from_directory(VIRTUAL_OUTPUT_AILERON_R)] );
	udb_pwOut[FLAP_LEFT_OUTPUT_CHANNEL] 	= udb_servo_pulsesat( (int) flexiFunction_registers[get_output_register_index_from_directory(VIRTUAL_OUTPUT_FLAP_L)] );
	udb_pwOut[FLAP_RIGHT_OUTPUT_CHANNEL] 	= udb_servo_pulsesat( (int) flexiFunction_registers[get_output_register_index_from_directory(VIRTUAL_OUTPUT_FLAP_R)] );
	udb_pwOut[FLAPMID_LEFT_OUTPUT_CHANNEL] 	= udb_servo_pulsesat( (int) flexiFunction_registers[get_output_register_index_from_directory(VIRTUAL_OUTPUT_FLAPMID_L)] );
	udb_pwOut[FLAPMID_RIGHT_OUTPUT_CHANNEL] = udb_servo_pulsesat( (int) flexiFunction_registers[get_output_register_index_from_directory(VIRTUAL_OUTPUT_FLAPMID_R)] );
	udb_pwOut[SPOILER_OUTPUT_CHANNEL] 		= udb_servo_pulsesat( (int) flexiFunction_registers[get_output_register_index_from_directory(VIRTUAL_OUTPUT_SPOILER)] );

	int throttle = (int) flexiFunction_registers[get_output_register_index_from_directory(VIRTUAL_OUTPUT_THROTTLE)];

	if(throttle < udb_pwTrim[THROTTLE_INPUT_CHANNEL])
		throttle = udb_pwTrim[THROTTLE_INPUT_CHANNEL];

	if ( udb_pwIn[THROTTLE_INPUT_CHANNEL] == 0 )
	{
		throttle = 0 ;
	}

	udb_pwOut[THROTTLE_OUTPUT_CHANNEL]	= throttle;
}


void servoMix( void )
{
	// Check for a new set of functions
	flexiFunction_commit_buffer_check();

	preMix();

	runFlexiFunctions( );
	
	postMix();
};

