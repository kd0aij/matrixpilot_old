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
//
void preMix( void )
{
// Bring RMAX scaled input controls into registers.
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_ROLL)] 		= in_cntrls[IN_CNTRL_ROLL];
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_PITCH)] 		= in_cntrls[IN_CNTRL_PITCH];
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_THROTTLE)] 	= in_cntrls[IN_CNTRL_THROTTLE];
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_YAW)] 		= in_cntrls[IN_CNTRL_YAW];
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_CAMBER)] 	= in_cntrls[IN_CNTRL_CAMBER];
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_BRAKE)] 		= in_cntrls[IN_CNTRL_BRAKE];
	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_PWIN_FLAP)] 		= in_cntrls[IN_CNTRL_FLAP];

	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_APCON_WAGGLE)]	= PWM_to_frac(waggle,0, false);
//
//	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_TRIM_POINT)] 		= udb_pwTrim[ROLL_INPUT_CHANNEL];
//	flexiFunction_registers[get_input_register_index_from_directory(VIRTUAL_INPUT_TRIM_THROTTLE)] 	= udb_pwTrim[THROTTLE_INPUT_CHANNEL];
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

