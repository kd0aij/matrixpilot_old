#include "defines.h"
#include "flexiFunctionTypes.h"
#include "MIXERRegisters.h"
#include "MIXERVars.h"
#include "mixer_options.h"

#define RMAX15 0b0110000000000000	//	1.5 in 2.14 format
#define RMAX   0b0100000000000000	//	1.0 in 2.14 format

// Mixer registers
fractional MIXER_registers[MAX_MIXER_REGS];

// Turn PWM into fraction subtracting the offset
fractional PWM_to_frac(int PWM, int offset)
{
	union longww temp;
	temp.WW = ( (RMAX * 256.0) / ( MIX_PWM_MAX - MIX_PWM_MID ) );
	temp.WW = __builtin_mulss( PWM - offset, temp._.W0);  //
	temp.WW >>= 8;
	return (fractional) temp._.W0;
};

void preMix( void )
{
	int				index;

/*	// Reset all registers to zero.  MUST BE STATELESS.
	for(index = 0; index < REG_MIXER_MAX; index++)
	{
		MIXER_registers[index] = 0;
	}
*/

	// If radio is off, use udb_pwTrim values instead of the udb_pwIn values
	if (udb_flags._.radio_on)
	{
		MIXER_registers[REG_MIXER_PWIN_AILERON_LEFT] 	= PWM_to_frac(udb_pwIn[AILERON_LEFT_INPUT_CHANNEL], udb_pwTrim[AILERON_LEFT_INPUT_CHANNEL]);
		MIXER_registers[REG_MIXER_PWIN_ELEVATOR] 		= PWM_to_frac(udb_pwIn[ELEVATOR_INPUT_CHANNEL], 	udb_pwTrim[ELEVATOR_INPUT_CHANNEL]);
		MIXER_registers[REG_MIXER_PWIN_THROTTLE] 		= PWM_to_frac(udb_pwIn[THROTTLE_INPUT_CHANNEL], 	udb_pwTrim[THROTTLE_INPUT_CHANNEL]);
		MIXER_registers[REG_MIXER_PWIN_RUDDER] 			= PWM_to_frac(udb_pwIn[RUDDER_INPUT_CHANNEL], 		udb_pwTrim[RUDDER_INPUT_CHANNEL]);
		MIXER_registers[REG_MIXER_PWIN_AILERON_RIGHT] 	= PWM_to_frac(udb_pwIn[AILERON_RIGHT_INPUT_CHANNEL], udb_pwTrim[AILERON_RIGHT_INPUT_CHANNEL]);
		MIXER_registers[REG_MIXER_PWIN_FLAP_LEFT] 		= PWM_to_frac(udb_pwIn[FLAP_LEFT_INPUT_CHANNEL], 	udb_pwTrim[FLAP_LEFT_INPUT_CHANNEL]);
		MIXER_registers[REG_MIXER_PWIN_FLAP_RIGHT]	 	= PWM_to_frac(udb_pwIn[FLAP_RIGHT_INPUT_CHANNEL], 	udb_pwTrim[FLAP_RIGHT_INPUT_CHANNEL]);
	}
	else
	{
		MIXER_registers[REG_MIXER_PWIN_AILERON_LEFT] 	= 0;
		MIXER_registers[REG_MIXER_PWIN_ELEVATOR] 		= 0;
		MIXER_registers[REG_MIXER_PWIN_THROTTLE] 		= 0;
		MIXER_registers[REG_MIXER_PWIN_RUDDER] 			= 0;
		MIXER_registers[REG_MIXER_PWIN_AILERON_RIGHT] 	= 0;
		MIXER_registers[REG_MIXER_PWIN_FLAP_LEFT] 		= 0;
		MIXER_registers[REG_MIXER_PWIN_FLAP_RIGHT] 		= 0;
	}

	MIXER_registers[REG_MIXER_APMODE_FULL] = 
		( dcm_flags._.nav_capable & 
			( udb_pwIn[MODE_SWITCH_INPUT_CHANNEL] > MODE_SWITCH_THRESHOLD_HIGH ) ) |
		( dcm_flags._.nav_capable & !udb_flags._.radio_on);

	MIXER_registers[REG_MIXER_RADIO_MANUAL_MODE]= 
		!( udb_pwIn[MODE_SWITCH_INPUT_CHANNEL] > MODE_SWITCH_THRESHOLD_HIGH ) & 
		!( udb_pwIn[MODE_SWITCH_INPUT_CHANNEL] > MODE_SWITCH_THRESHOLD_LOW );

	MIXER_registers[REG_MIXER_APMODE_RADIO_ON]			= udb_flags._.radio_on;

	if( !MIXER_registers[REG_MIXER_APMODE_FULL] & 
		!MIXER_registers[REG_MIXER_RADIO_MANUAL_MODE] )
		MIXER_registers[REG_MIXER_GAIN_MAN_MIX] = RMAX;
	else
		MIXER_registers[REG_MIXER_GAIN_MAN_MIX] = 0;	

	MIXER_registers[REG_MIXER_APCON_ROLL]			= PWM_to_frac(roll_control,0);
	MIXER_registers[REG_MIXER_APCON_PITCH]			= PWM_to_frac(pitch_control,0);
	MIXER_registers[REG_MIXER_APCON_YAW]			= PWM_to_frac(yaw_control,0);
	MIXER_registers[REG_MIXER_APCON_THROTTLE]		= PWM_to_frac(throttle_control,0);
	MIXER_registers[REG_MIXER_APCON_WAGGLE]			= PWM_to_frac(waggle,0);

	MIXER_registers[REG_MIXER_TRIM_AILERON_LEFT] 	= udb_pwTrim[AILERON_LEFT_INPUT_CHANNEL];
	MIXER_registers[REG_MIXER_TRIM_ELEVATOR] 		= udb_pwTrim[ELEVATOR_INPUT_CHANNEL];
	MIXER_registers[REG_MIXER_TRIM_THROTTLE] 		= udb_pwTrim[THROTTLE_INPUT_CHANNEL];
	MIXER_registers[REG_MIXER_TRIM_RUDDER] 			= udb_pwTrim[RUDDER_INPUT_CHANNEL];
	MIXER_registers[REG_MIXER_TRIM_AILERON_RIGHT] 	= udb_pwTrim[AILERON_RIGHT_INPUT_CHANNEL];
	MIXER_registers[REG_MIXER_TRIM_FLAP_LEFT] 		= udb_pwTrim[FLAP_LEFT_INPUT_CHANNEL];
	MIXER_registers[REG_MIXER_TRIM_FLAP_RIGHT] 		= udb_pwTrim[FLAP_RIGHT_INPUT_CHANNEL];
}


void postMix( void )
{
	udb_pwOut[AILERON_LEFT_OUTPUT_CHANNEL] 	= (int) MIXER_registers[REG_MIXER_PWOUT_AILERON_LEFT];
	udb_pwOut[ELEVATOR_OUTPUT_CHANNEL] 		= (int) MIXER_registers[REG_MIXER_PWOUT_ELEVATOR];
	udb_pwOut[RUDDER_OUTPUT_CHANNEL] 		= (int) MIXER_registers[REG_MIXER_PWOUT_RUDDER];
	udb_pwOut[AILERON_RIGHT_OUTPUT_CHANNEL] = (int) MIXER_registers[REG_MIXER_PWOUT_AILERON_RIGHT];
	udb_pwOut[FLAP_LEFT_OUTPUT_CHANNEL] 	= (int) MIXER_registers[REG_MIXER_PWOUT_FLAP_LEFT];
	udb_pwOut[FLAP_RIGHT_OUTPUT_CHANNEL] 	= (int) MIXER_registers[REG_MIXER_PWOUT_FLAP_RIGHT];

	int throttle = (int) MIXER_registers[REG_MIXER_PWOUT_THROTTLE];

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
	preMix();

	runFlexiFunctions( MIXER_data, MIXER_registers , MAX_MIXER_FUNCS );
	
	postMix();
};

