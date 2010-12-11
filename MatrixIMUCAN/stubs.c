#include "../libUDB/libUDB.h"
#include "../libDCM/libDCM.h"
#include "../libCAN/libCAN.h"
#include "defines.h"


int gpscount ; // counter to initialize GPS
int calibcount ; // number of PWM pulses before control is turned on


void dcm_servo_callback_prepare_outputs(void)
{
	CAN_send_imu_data();
	CAN_send_dcm_data();
#if (MAG_YAW_DRIFT == 1)
	CAN_send_mag_data();
#endif

	switch ( calibcount ) 
	{
		case 1: 
		{
			// almost ready to turn the control on, save the sensor offsets to allow testing
			// the dcm before the radio is on.  we record offsets again along with trims
			// immediately before the first wag.
			dcm_calibrate() ;
			break ;
		}
		default:
			break ;
	}

	// count down the startup counter to 0
	if ( calibcount > 0 ) calibcount-- ;

	// FIXME: this code should move into libDCM
	// count down the startup counter to 0
	if ( gpscount > 0 )
	{
		gps_startup_sequence(gpscount) ;
		gpscount-- ;
	}

}


void setup_origin(void)
{
/*	if (use_fixed_origin())
	{
		struct absolute3D origin = get_fixed_origin() ;
		dcm_set_origin_location(origin.x, origin.y, origin.z ) ;
	}
	else
	{
*/
		dcm_set_origin_location(long_gps.WW, lat_gps.WW, alt_sl_gps.WW) ;
//	}
	flags._.f13_print_req = 1 ; // Flag telemetry output that the origin can now be printed.
	
	return ;
}


void dcm_callback_gps_location_updated(void)
{
	if ( flags._.save_origin )
	{
		//	capture origin information during power up. much of this is not actually used for anything,
		//	but is saved in case you decide to extend this code.
		flags._.save_origin = 0 ;
		setup_origin() ;
	}
	
#if ( DEADRECKONING == 0 )
	process_flightplan() ;
#endif
}

void udb_serial_callback_received_char(char rxchar)
{
};

char udb_serial_callback_get_char_to_send(void)
{
	return 0;
}

void init_servoPrepare( void )	// initialize the PWM
{
	calibcount = 400 ;	// wait 400 PWM pulses before turning on the control (10 seconds)
	gpscount = 1000 ;	// wait 25 seconds for GPS to initialize
}

