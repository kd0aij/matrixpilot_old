// This file is part of the MatrixPilot RollPitchYaw demo.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


// main program for testing the IMU.


#include "../libDCM/libDCM.h"


// Used for serial debug output
#include "stdio.h"

char debug_buffer[256] ;
int db_index = 0 ;
void send_debug_line( void ) ;


int main (void)
{
	// Set up the libraries
	udb_init() ;
	dcm_init() ;
	
//	udb_serial_set_rate(19200) ;
	udb_serial_set_rate(115200) ;
	
	LED_GREEN = LED_OFF ;
	
	// Start it up!
	udb_run() ;  // This never returns.
	
	return 0 ;
}


// Called every 1/2 second at high priority
void udb_background_callback_periodic(void)
{
	if (!dcm_flags._.calib_finished)
	{
		// If still calibrating, blink RED
		udb_led_toggle(LED_RED) ;
	}
	else
	{
		// No longer calibrating: solid RED and send debug output
		LED_RED = LED_ON ;
	}
	
	return ;
}


// Called every time we get gps data (1, 2, or 4 Hz, depending on GPS config)
void dcm_callback_gps_location_updated(void)
{
	// Blink GREEN led to show that the GPS is communicating
	udb_led_toggle(LED_GREEN) ;
	return ;
}


// Called at 40 Hz, before sending servo pulses
void dcm_servo_callback_prepare_outputs(void)
{
	if (!dcm_flags._.calib_finished)
	{
		udb_pwOut[ROLL_OUTPUT_CHANNEL] = 3000 ;
		udb_pwOut[PITCH_OUTPUT_CHANNEL] = 3000 ;
		udb_pwOut[YAW_OUTPUT_CHANNEL] = 3000 ;
	}
	else
	{
		union longww accum ;
		
		accum.WW = __builtin_mulss( rmat[6] , 4000 ) ;
		udb_pwOut[ROLL_OUTPUT_CHANNEL] = udb_servo_pulsesat(3000 + accum._.W1) ;
		
		accum.WW = __builtin_mulss( rmat[7] , 4000 ) ;
		udb_pwOut[PITCH_OUTPUT_CHANNEL] = udb_servo_pulsesat(3000 + accum._.W1) ;
		
		accum.WW = __builtin_mulss( rmat[4] , 4000 ) ;
		udb_pwOut[YAW_OUTPUT_CHANNEL] = udb_servo_pulsesat(3000 + accum._.W1) ;
	}
	
	// Serial output at 8Hz  (40Hz / 5)
	if (udb_heartbeat_counter % 5 == 0) 
	{
		if ( dcm_flags._.calib_finished )
		{
			send_debug_line() ;
		}
	}
	
	return ;
}

extern fractional omegacorrP[3] , omegacorrI[3] ;
extern int gplane[3] ;
extern int udb_magOffset[3] ;
int output_count = 0 ;
extern unsigned int spin_rate ;
extern int spin_axis[3] ;
extern int ggain[3] ;

// Prepare a line of serial output and start it sending
void send_debug_line( void )
{
	db_index = 0 ;
	if ( output_count == 0 )
	{
		output_count = 1 ;
		sprintf( debug_buffer , "r[3] , r[4] , r[5] , "
								"r[6] , r[7] , r[8] , "
								"g[0] , g[1] , g[2] , "
								"B[0] , B[1] , B[2] , "
								 ) ;
	}
	else if ( output_count == 1 )
	{
		output_count = 2 ;
		sprintf( debug_buffer , "B0[0] , B0[1] , B0[2] , "
								"gyro[0] , gyro[1] , gyro[2] , "
								"rate , n[0] , n[1] , n2] , "
								"P[0] , P[1] , P[2] , "
								"gain[0] , gain[1] , gain[2] , "
								"I[0] , I[1] , I[2] \r\n" ) ;
	}
	else
	{
		sprintf( debug_buffer , "%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%u,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i\r\n" , 
		rmat[3] , rmat[4] , rmat[5] ,
		rmat[6] , rmat[7] , rmat[8] ,
		gplane[0] , gplane[1] , gplane[2] ,		
		udb_magFieldBody[0] , udb_magFieldBody[1] , udb_magFieldBody[2] , 
		udb_magOffset[0] , udb_magOffset[1] , udb_magOffset[2] , 
		omegagyro[0] , omegagyro[1] , omegagyro[2] , 
		spin_rate , spin_axis[0] , spin_axis[1] , spin_axis[2] , 
		omegacorrP[0] , omegacorrP[1] , omegacorrP[2] ,
		ggain[0] , ggain[1] , ggain[2] ,
		omegacorrI[0] , omegacorrI[1] , omegacorrI[2] 	) ; 
	}
	
	udb_serial_start_sending_data() ;
	
	return ;
}



/*
// Prepare a line of serial output and start it sending
void send_debug_line( void )
{
	db_index = 0 ;
	sprintf( debug_buffer , "lat: %li, long: %li, alt: %li\r\nrmat: %i, %i, %i, %i, %i, %i, %i, %i, %i\r\n" , 
		lat_gps.WW , long_gps.WW , alt_sl_gps.WW , 
		rmat[0] , rmat[1] , rmat[2] , 
		rmat[3] , rmat[4] , rmat[5] , 
		rmat[6] , rmat[7] , rmat[8]  ) ; 
	
	udb_serial_start_sending_data() ;
	
	return ;
}
*/


// Return one character at a time, as requested.
// Requests will stop after we send back a -1 end-of-data marker.
int udb_serial_callback_get_byte_to_send(void)
{
	unsigned char c = debug_buffer[ db_index++ ] ;
	
	if (c == 0) return -1 ;
	
	return c ;
}


// Don't respond to serial input
void udb_serial_callback_received_byte(char rxchar)
{
	// Do nothing
	return ;
}
