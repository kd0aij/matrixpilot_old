#include "libUDB.h"
#include "defines.h"
#include "definesRmat.h"

//	routines to drive the PWM pins for the servos,
//	assumes the use of the 16MHz crystal.

int gpscount ; // counter to initialize GPS
int calibcount ; // number of PWM pulses before control is turned on
int fourHertzCounter = 0 ;
int startTelemetry = 0 ;


void manualPassthrough( void ) ;


void init_servoPrepare( void )	// initialize the PWM
{
	firstsamp = 1 ;		// flag for the first sample
	calibcount = 400 ;	// wait 400 PWM pulses before turning on the control (10 seconds)
	gpscount = 1000 ;	// wait 25 seconds for GPS to initialize

	int i;
	for (i=0; i <= NUM_OUTPUTS; i++)
		if (i != THROTTLE_OUTPUT_CHANNEL)
			udb_pwOut[i] = 3000 ;
	
	return ;
}


void udb_servo_callback_prepare_outputs(void)
{
	// This is a simple counter to do stuff at 4hz
	fourHertzCounter++ ;
	if ( fourHertzCounter >= 10 )
	{
		if ( startTelemetry )
		{
			serial_output_4hz() ;
			rxMagnetometer() ;
		}
		fourHertzCounter = 0 ;
	}
	
	
	switch ( calibcount ) {
		// case 0 is when the control is up and running
			
		case 0: {
			imu() ;
			updateBehavior() ;
			rollCntrl() ;
			yawCntrl() ;
			altitudeCntrl();
			pitchCntrl() ;
			servoMix() ;
#if ( USE_CAMERA_STABILIZATION == 1 )
			cameraCntrl();
#endif
			updateTriggerAction() ;
			break ;
		}
			
		case 1: {
			// almost ready to turn the control on, save the input offsets
			udb_a2d_record_offsets() ;
			manualPassthrough() ;	// Allow manual control while starting up
			startTelemetry = 1 ;
			break ;
		}
		default: {
			// otherwise, there is not anything to do
			manualPassthrough() ;	// Allow manual control while starting up
			break ;
		}
	}
	
	// count down the startup counter to 0
	if ( calibcount > 0 ) calibcount-- ;

	
	// count down the startup counter to 0
	gps_startup_sequence(gpscount) ;

	if ( gpscount > 0 ) gpscount-- ;
	
	return ;
}

void manualPassthrough( void )
{
	roll_control = pitch_control = yaw_control = altitude_control = 0 ;
	servoMix() ;
	
	return ;
}

