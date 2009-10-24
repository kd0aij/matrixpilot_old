#include "p30f4011.h"
#include "defines.h"
#include "definesRmat.h"
#include <stdio.h>
#include <stdarg.h>

int sb_index = 0 ;
int end_index = 0;

#define SERIAL_BUFFER_SIZE 256
char serial_buffer[SERIAL_BUFFER_SIZE] ;

void init_USART1(void)
{	
//	debugging/telemetry USART, runs at 19200 baud
	U1MODE = 0b0010000000000000 ; // turn off RX, used to clear errors
	U1STA  = 0b0000010100010000 ;

//	U1BRG =  51 ; // 4800 baud
	U1BRG =  12 ; // 19200 baud

	U1MODEbits.UARTEN = 1 ; // turn on uart
	U1MODEbits.ALTIO = 1 ; // alternate pins
	
	U1STAbits.UTXEN = 1 ; // turn on transmitter

	IFS0bits.U1RXIF = 0 ; // clear the interrupt
	IPC2bits.U1RXIP = 3 ; // priority 3
	IEC0bits.U1RXIE = 1 ; // turn on the interrupt

	IFS0bits.U1TXIF = 0 ; // clear the interrupt 
 	IPC2bits.U1TXIP = 4 ; // priority 4 
 	IEC0bits.U1TXIE = 1 ; // turn on the interrupt

	return ;
}

void __attribute__((__interrupt__,__no_auto_psv__)) _U1RXInterrupt(void)
{
	char rxchar ;
	indicate_loading_inter ;
	rxchar = U1RXREG ;
	if ( U2STAbits.FERR ) {  init_USART1(); }
	else if ( U2STAbits.OERR ) {  init_USART1(); }
	
	IFS0bits.U1RXIF = 0 ; // clear the interrupt
	return ;
}

// add this text to the output buffer
void serial_output( char* format, ... )
{
	va_list arglist ;
	unsigned char txchar ;
	
	va_start(arglist, format) ;
	
	int start_index = end_index ;
	int remaining = SERIAL_BUFFER_SIZE - start_index ;
	
	if (remaining > 0) {
		int wrote = vsnprintf( (char*)(&serial_buffer[start_index]), (size_t)remaining, format, arglist) ;
		end_index = start_index + wrote;
	}
	
	if (sb_index == 0)
	{
		IFS0bits.U1TXIF = 1 ; // trigger the TX interrupt
	}
	
	va_end(arglist);
	
	return ;
}

void __attribute__((__interrupt__,__no_auto_psv__)) _U1TXInterrupt(void)
{
	unsigned char txchar ;
	IFS0bits.U1TXIF = 0 ; // clear the interrupt 
	txchar = serial_buffer[ sb_index++ ] ;
	if ( txchar )
	{
		U1TXREG = txchar ;
	}
	else
	{
		sb_index = 0 ;
		end_index = 0 ;
	}
	
	return ;
}



extern signed char bearing_to_origin ;
extern int tofinish, crosstrack, desiredHeight, waypointIndex, tofinish ;
extern signed char desired_dir_waypoint ;

void serial_output_gps( void )
{
#if ( SERIAL_OUTPUT_FORMAT == SERIAL_DEBUG )
	serial_output("lat: %li, long: %li, alt: %li\r\nrmat: %i, %i, %i, %i, %i, %i, %i, %i, %i\r\n" , 
		lat_gps.WW , long_gps.WW , alt_sl_gps.WW , 
		rmat[0] , rmat[1] , rmat[2] , 
		rmat[3] , rmat[4] , rmat[5] , 
		rmat[6] , rmat[7] , rmat[8]  ) ;
		
#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_ARDUSTATION )
	// I still need to rework the units of many of these items
	serial_output("!!!TIM:%li,LAT:%li,LON:%li,SPD:%i,CRT:%i,ALT:%li,ALH:%i,CRS:%i,BER:%i,WPN:%i,DST:%i,***\r\n",
		tow.WW, lat_gps.WW , long_gps.WW , sog_gps.BB, climb_gps.BB, alt_sl_gps.WW, desiredHeight, cog_gps.BB, bearing_to_origin,
		waypointIndex, tofinish) ;

#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_UDB )
		// F2 below means "Format Revision 2: and is used by a Telemetry parser to invoke the right pattern matching
        // If you change this output format, then change F2 to F3 or F4, etc - to mark a new revision of format.
		// F2 is a compromise between easy reading of raw data in a file and not droppping chars in transmission.
		serial_output("F2:T%li:S%d%d%d%d:N%li:E%li:A%li:W%i:a%i:b%i:c%i:d%i:e%i:f%i:g%i:h%i:i%i:c%i:s%i:\r\n",
		tow, flags._.radio_on, flags._.nav_capable, flags._.GPS_steering, flags._.use_waypoints,
	 	lat_gps.WW , long_gps.WW , alt_sl_gps.WW, waypointIndex,
		rmat[0] , rmat[1] , rmat[2] , 
		rmat[3] , rmat[4] , rmat[5] , 
		rmat[6] , rmat[7] , rmat[8] ,
		cog_gps, sog_gps ) ;
#endif
}


void serial_output_rapid( void )
{
#if ( SERIAL_OUTPUT_FORMAT == SERIAL_ARDUSTATION )
	unsigned int mode ;
	
	if (flags._.GPS_steering == 0 && flags._.pitch_feedback == 0 && flags._.use_waypoints == 0)
		mode = 1 ;
	else if (flags._.GPS_steering == 0 && flags._.pitch_feedback == 1 && flags._.use_waypoints == 0)
		mode = 2 ;
	else if (flags._.GPS_steering == 1 && flags._.pitch_feedback == 1 && flags._.use_waypoints == 1)
		mode = 3 ;
	else if (flags._.GPS_steering == 1 && flags._.pitch_feedback == 1 && flags._.use_waypoints == 0)
		mode = 0 ;
	else
		mode = 99 ; // Unknown
	
	serial_output("+++THH:%i,RLL:%i,PCH:%i,STT:%i,***\r\n",
		(pwOut[THROTTLE_OUTPUT_CHANNEL]-2000)/20,
		(pwOut[AILERON_OUTPUT_CHANNEL]-3000)/20, // this should instead be current roll angle in degrees
		(pwOut[ELEVATOR_OUTPUT_CHANNEL]-3000)/20, // this should instead be current pitch angle in degrees
		mode) ;
#endif
}

