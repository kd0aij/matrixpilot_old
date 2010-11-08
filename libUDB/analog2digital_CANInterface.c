// See end of file for license

#include "libUDB_internal.h"

#define ADC_ACTIVE_CHANNEL_COUNT	4

struct ADchannel 	channels[ADC_ACTIVE_CHANNEL_COUNT];

boolean firstsamp = true;


//	Virtual Variables. These are not used by the interface board.
// They are here for telmetry purposes (copy of UDB variables on CAN interface)

struct ADchannel udb_xaccel, udb_yaccel , udb_zaccel ; // x, y, and z accelerometer channels
struct ADchannel udb_xrate , udb_yrate, udb_zrate ;  // x, y, and z gyro channels
struct ADchannel udb_vref ; // reference voltage


void udb_init_ADC( void )
{
	TRISB	|=  0b1111111111111000; 	// Set only analog ports to inputs
	TRISA	|=	0b0000011000000000; 	// Reference inputs set as inputs

//	ADCON1 = 0b0010001111100100 ; // signed fractional , auto convert , seq, auto samp
	ADCON1 = 0b0010000011100100 ; // int , auto convert , seq, auto samp

	ADCON2 = 0b1000010000010000 ; // supply ref, scana ch0, int every N channels, 16word, usa A only
								  // NOte that number of channels must match ADC_ACTIVE_CHANNEL_COUNT

//	ADCON3 = 0b0001111100111111 ; // slowest possible, approximately 500 samples per second for each channel
	ADCON3 = 0b0000001100111111 ;

	ADCHS  = 0b0000000000000110 ; // channel AN0 - Overidden by auto scanning
	ADPCFG = 0b1111100100111111 ; // analog inputs on 6,7,9,10
	ADCSSL = 0b0000011011000000 ; 
	
	_ADIF = 0 ; 	// clear the AD interrupt
	_ADIP = 5 ;     // priority 5
	_ADIE = 1 ;     // enable the interrupt
	_ADON = 1 ;		// turn on the A to D
	return ;
}


void __attribute__((__interrupt__,__no_auto_psv__)) _ADCInterrupt(void)
{
	interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	int count;

	channels[0].input = ADCBUF0;
	channels[1].input = ADCBUF1;
	channels[2].input = ADCBUF2;
	channels[3].input = ADCBUF3;


	if ( firstsamp == true )	// use the first sample to initialize the filters
	{
		for(count = 0; count < ADC_ACTIVE_CHANNEL_COUNT; count++)
		{
			channels[count].value = channels[count].input;
		}
//		IEC2bits.PWMIE = 1 ;     // enable the PWM interrupt
		firstsamp = false;
	}
	else
	{
		for(count = 0; count < ADC_ACTIVE_CHANNEL_COUNT; count++)
		{
			channels[count].value = channels[count].value +
							(( (channels[count].input>>1) - (channels[count].value>>1) )>> FILTERSHIFT ) ;
		}
	}
	
	_ADIF = 0 ; 	// clear the AD interrupt
	
	interrupt_restore_extended_state ;
	return ;
}

/****************************************************************************/
// This is part of the servo and radio interface software
//
// ServoInterface source code
//	http://code.google.com/p/rc-servo-interface
//
// Copyright 2010 ServoInterface Team
// See the AUTHORS.TXT file for a list of authors of ServoInterface.
//
// ServoInterface is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ServoInterface is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with ServoInterface.  If not, see <http://www.gnu.org/licenses/>.
//
// Many parts of ServoInterface use either modified or unmodified code
// from the MatrixPilot pilot project.
// The project also contains code for modifying MatrixPilot to operate
// with ServoInterface.
// For details, credits and licenses of MatrixPilot see the AUTHORS.TXT file.
// or see this website: http://code.google.com/p/gentlenav
/****************************************************************************/
