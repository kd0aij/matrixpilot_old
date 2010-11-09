// SEE END OF FILE FOR LICENSE TERMS

#include "../libUDB/libUDB.h"
#include "CANInterface_defines.h"
#include <string.h>

//	routines to drive the PWM pins for the servos,
//	assumes the use of the 16MHz crystal.

int outputNum ;

int udb_pwOut[MAX_OUTPUTS+1];	// pulse widths for servo outputs in UDB loop
int pwOut[MAX_OUTPUTS+1];		// pulse widths for servo outputs in CAN loop

void setupOutputs( void ) ;
//void manualPassthrough( void ) ;								

void udb_init_pwm( void )	// initialize the PWM
{
	PDC1 = PDC2 = PDC3 = PDC4 = 3000 ;
	
	int i;
	for (i=0; i <= NUM_OUTPUTS; i++)
		pwOut[i] = 3000;
	
	pwOut[THROTTLE_OUTPUT_CHANNEL] = THROTTLE_MINIMUM_OUTPUT;

	TRISE &= 0xFF00 ;		// Set low byte portE PWMs to outputs
	PTPER = 25000 ;			// 25 millisecond period at 16 Mz clock, prescale = 4	
	PTCONbits.PTCKPS = 1;	// prescaler = 4

	PWMCON1bits.PMOD1 = 1 ; // independent PWM mode
	PWMCON1bits.PMOD2 = 1 ;
	PWMCON1bits.PMOD3 = 1 ;
	PWMCON1bits.PMOD4 = 1 ;

	PWMCON1bits.PEN1H = 1 ; // High pins used as PWM
	PWMCON1bits.PEN2H = 1 ;
	PWMCON1bits.PEN3H = 1 ;
	PWMCON1bits.PEN4H = 1 ;

	PWMCON1bits.PEN1L = 0 ; // low pins used as digital I/O
	PWMCON1bits.PEN2L = 0 ;
	PWMCON1bits.PEN3L = 0 ;
	PWMCON1bits.PEN4L = 0 ;
	
	PTCONbits.PTEN = 1; 	// turn on the PWM 
	IFS2bits.PWMIF = 0 ; 	// clear the PWM interrupt
	IPC9bits.PWMIP = 3 ;    // priority 3
//	IPC9bits.PWMIP = 1 ;    // priority 1
	
	T4CON = 0b1000000000000000  ;	// turn on timer 4 with no prescaler
	IPC5bits.T4IP = 7 ;				// priority 7
	IEC1bits.T4IE = 0 ;				// disable timer 4 interrupt for now (enable for each set of pulses)

	//  note: at this point the PWM is running, so there are pulses going out,
	//	but the PWM interrupt is still off, so no interrupts are coming in yet to compute pulses.
	//  the PWM interrupt is turned on within the A/D interrupt processing
	
	// Ignore this and start it here anyway..
	IEC2bits.PWMIE = 1 ;     // enable the PWM interrupt

	return ;
}

int pulsesat ( long pw ) // saturation logic to maintain pulse width within bounds
{
	if ( pw > SERVO_OUT_MAX ) pw = SERVO_OUT_MAX ;
	if ( pw < SERVO_OUT_MIN ) pw = SERVO_OUT_MIN ;
	return (int)pw ;
}


void __attribute__((__interrupt__,__no_auto_psv__)) _PWMInterrupt(void)
{
	// interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	//	Executes whatever needs to be done every 25 milliseconds, using the PWM clock.
	//	This is a good place to run the A/D digital filters and compute pulse widths for servos.
	//	Also, this is used to wait a few pulses before recording input DC offsets.
	

	if(RxTimeouts == RX_MAX_TIMEOUTS)
	{
		op_status.passthrough = 1;
	}
	else
	{
		if(pwIn[MODE_INPUT_CHANNEL] < MODE_SWITCH_THRESHOLD_LOW)
		{
			op_status.passthrough = 1;
		}
		else
		{
			op_status.passthrough = 0;
		};

		RxTimeouts++;
	};

// If in failsafe and CANbus is properly connected, let the autopilot take over.
	if( ( (pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MIN) || (pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MAX) ) &&
		  		(RxTimeouts < RX_MAX_TIMEOUTS) )
	{
		op_status.passthrough = 0;
	};


// If in passthrough mode, copy inputs to outputs
	if(op_status.passthrough == 1)
	{
		memcpy(pwOut,pwIn,sizeof(pwIn));	// Warning, this might glitch
	}
	else
	{
		memcpy(&pwOut[1], ServoInDataBuff, sizeof(ServoInDataBuff));
//		memcpy(pwOut,pwIn,sizeof(pwIn));	// Warning, this might glitch
	};

	if(pwOut[THROTTLE_OUTPUT_CHANNEL] < THROTTLE_MINIMUM_OUTPUT)
	{
		pwOut[THROTTLE_OUTPUT_CHANNEL] = THROTTLE_MINIMUM_OUTPUT;
	};
	
	setupOutputs() ;
	
	IFS2bits.PWMIF = 0 ; /* clear the interrupt */

	ClrWdt();
	
	// interrupt_restore_extended_state ;

	return ;
}


void setupOutputs( void )
{
	PDC1 = pwOut[CH7_OUTPUT_CHANNEL] ;
	PDC2 = pwOut[CH5_OUTPUT_CHANNEL] ;
	PDC3 = pwOut[CH3_OUTPUT_CHANNEL] ;
	PDC4 = pwOut[CH1_OUTPUT_CHANNEL] ;

	outputNum = 5 ;
	if ( pwOut[CH8_OUTPUT_CHANNEL] > 0 )
	{
		PR4 = (pwOut[CH8_OUTPUT_CHANNEL] << 1) ;	// set timer to the pulse width
		LATEbits.LATE0 = 1 ;	// start the pulse by setting the E0 pin high (output 4)
	}
	else
	{
		PR4 = 100 ;				// set timer to a short wait
		LATEbits.LATE0 = 0 ;	// skip the pulse by setting the E0 pin low (output 4)
	}	
	TMR4 = 0 ;				// start timer at 0
	IFS1bits.T4IF = 0 ;		// clear the interrupt
	IEC1bits.T4IE = 1 ;		// enable timer 4 interrupt

	return;
}

void __attribute__((__interrupt__,__no_auto_psv__)) _T4Interrupt(void)
{
	interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	switch ( outputNum ) {
		case 5:
			LATEbits.LATE0 = 0 ;		// end the pulse by setting the E0 pin low (output 4)
			if ( pwOut[CH6_OUTPUT_CHANNEL] > 0 )
			{
				PR4 = (pwOut[CH6_OUTPUT_CHANNEL] << 1) ;	// set timer to the pulse width
				LATEbits.LATE2 = 1 ;	// start the pulse by setting the E2 pin high (output 5)
			}
			else
			{
				PR4 = 100 ;				// set timer to the pulse width
				LATEbits.LATE2 = 0 ;	// skip the pulse by setting the E2 pin low (output 5)
			}	
			TMR4 = 0 ;				// start timer at 0
			break;
		
		case 6:
			LATEbits.LATE2 = 0 ;		// end the pulse by setting the E2 pin low (output 5)

			if ( pwOut[CH4_OUTPUT_CHANNEL] > 0 )
			{
				PR4 = (pwOut[CH4_OUTPUT_CHANNEL] << 1) ;	// set timer to the pulse width
				LATEbits.LATE4 = 1 ;	// start the pulse by setting the E4 pin high (output 6)
			}
			else
			{
				PR4 = 100 ;				// set timer to the pulse width
				LATEbits.LATE4 = 0 ;	// start the pulse by setting the E4 pin high (output 6)
			}
			TMR4 = 0 ;				// start timer at 0
			break ;

		case 7:
			LATEbits.LATE4 = 0 ;		// end the pulse by setting the E2 pin low (output 5)
			if ( pwOut[CH2_OUTPUT_CHANNEL] > 0 )
			{
				PR4 = (pwOut[CH2_OUTPUT_CHANNEL] << 1) ;	// set timer to the pulse width
				LATEbits.LATE6 = 1 ;	// start the pulse by setting the E4 pin high (output 6)
			}
			else
			{
				PR4 = 100 ;				// set timer to the pulse width
				LATEbits.LATE6 = 0 ;	// start the pulse by setting the E4 pin high (output 6)
			}
			TMR4 = 0 ;				// start timer at 0
			break ;
		default:
			LATEbits.LATE6 = 0 ;		// end the pulse by setting the E4 pin low (output 6)
			IEC1bits.T4IE = 0 ;			// disable timer 4 interrupt
			break ;
	}
	
	outputNum++;

	IFS1bits.T4IF = 0 ;					// clear the interrupt
	
	interrupt_restore_extended_state ;
	return;
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
