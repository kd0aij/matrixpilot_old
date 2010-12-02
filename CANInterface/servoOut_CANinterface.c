// SEE END OF FILE FOR LICENSE TERMS

#include "../libUDB/libUDB.h"
#include "../libCAN/libCAN.h"
#include "../libDCM/libDCM.h"
#include "CANInterface_defines.h"
#include <string.h>


//	routines to drive the PWM pins for the servos,
//	assumes the use of the 16MHz crystal.

// Tracking the output number for bit bashed outputs
unsigned char outputNum ;	

int udb_pwOut[MAX_OUTPUTS+1];	// pulse widths for servo outputs in UDB loop

void setupOutputs( void ) ;
//void manualPassthrough( void ) ;



void udb_init_pwm( void )	// initialize the PWM
{
	PDC1 = PDC2 = PDC3 = PDC4 = 0 ;
	
	int i;
	for (i=0; i <= NUM_OUTPUTS; i++)
		udb_pwOut[i] = 0;
	
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

	// PWM is requried to run to keep the watchdog timer alive
	// PWM is activated by setting flag 	op_control.pwm_active = 1;
	IEC2bits.PWMIE = 1 ;     // enable the PWM interrupt

	return ;
}



void __attribute__((__interrupt__,__no_auto_psv__)) _PWMInterrupt(void)
{
	int index;
	// interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	// if the CAN interface is conencted, flag it as ok.
	if(RxTimeouts == RX_MAX_TIMEOUTS)
		op_status.cntrl_comm_ok = 0;
	else
	{
		op_status.cntrl_comm_ok = 1;
		RxTimeouts++;
	};

	// If failsafe has been received and it is in failsafe range, flag is as ok (1)
	if(op_status.failsafe_rx == 1)
	{
		if( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MIN) || (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MAX) )
			op_status.failsafe_ok = 0;
		else
			op_status.failsafe_ok = 1;
	}
	else
	{
		op_status.failsafe_ok = 0;
	}

// If in failsafe and CANbus is properly connected, let the autopilot take over.
	
	// If the mode input 
	if(udb_pwIn[MODE_SWITCH_INPUT_CHANNEL] < MODE_SWITCH_THRESHOLD_LOW)
	{
		op_status.passthrough = 1;
	}
	else
	{
		op_status.passthrough = 0;
	};

	// If the failsafe is not ok and the autopilot is connected, force non passthrough
	if( (op_status.failsafe_ok == 0) && ( op_status.cntrl_comm_ok == 1) )
	{
		op_status.passthrough = 0;
	}

	if( op_status.cntrl_comm_ok == 0)
	{
		op_status.passthrough = 1;
	}

	// If a good radio frame is recieved
	if(op_status.frame_ok == 1)
	{
		op_control.pwm_active = 1;
	}

	// skip udb_servo_callback_prepare_outputs()
//	dcm_servo_callback_prepare_outputs() ;

	if(op_status.passthrough == 1)
	{
		index = 1;
		while( (index <= MAX_INPUTS) && (index <= MAX_OUTPUTS) )
		{
			udb_pwOut[index] = udb_pwIn[index];
			index++;
		}
	}

	if(op_control.pwm_active == 1)
	{
		setupOutputs() ;
	}

	IFS2bits.PWMIF = 0 ; /* clear the interrupt */

	ClrWdt();
	
	// interrupt_restore_extended_state ;

	return ;
}


void setupOutputs( void )
{
	PDC1 = udb_pwOut[CH7_OUTPUT_CHANNEL] ;
	PDC2 = udb_pwOut[CH5_OUTPUT_CHANNEL] ;
	PDC3 = udb_pwOut[CH3_OUTPUT_CHANNEL] ;
	PDC4 = udb_pwOut[CH1_OUTPUT_CHANNEL] ;

	outputNum = 5 ;
	if ( udb_pwOut[CH8_OUTPUT_CHANNEL] > 0 )
	{
		PR4 = (udb_pwOut[CH8_OUTPUT_CHANNEL] << 1) ;	// set timer to the pulse width
		LATEbits.LATE0 = 1 ;	// start the pulse by setting the E0 pin high
	}
	else
	{
		PR4 = 100 ;				// set timer to a short wait
		LATEbits.LATE0 = 0 ;	// skip the pulse by setting the E0 pin low
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
			LATEbits.LATE0 = 0 ;		// end the pulse by setting the E0 pin low
			if ( udb_pwOut[CH6_OUTPUT_CHANNEL] > 0 )
			{
				PR4 = (udb_pwOut[CH6_OUTPUT_CHANNEL] << 1) ;	// set timer to the pulse width
				LATEbits.LATE2 = 1 ;	// start the pulse by setting the E2 pin high
			}
			else
			{
				PR4 = 100 ;				// set timer to the pulse width
				LATEbits.LATE2 = 0 ;	// skip the pulse by setting the E2 pin low
			}	
			TMR4 = 0 ;				// start timer at 0
			break;
		
		case 6:
			LATEbits.LATE2 = 0 ;		// end the pulse by setting the E2 pin low

			if ( udb_pwOut[CH4_OUTPUT_CHANNEL] > 0 )
			{
				PR4 = (udb_pwOut[CH4_OUTPUT_CHANNEL] << 1) ;	// set timer to the pulse width
				LATEbits.LATE4 = 1 ;	// start the pulse by setting the E4 pin high
			}
			else
			{
				PR4 = 100 ;				// set timer to the pulse width
				LATEbits.LATE4 = 0 ;	// skip the pulse by setting the E4 pin low
			}
			TMR4 = 0 ;				// start timer at 0
			break ;

		case 7:
			LATEbits.LATE4 = 0 ;		// end the pulse by setting the E4 pin low
			if ( udb_pwOut[CH2_OUTPUT_CHANNEL] > 0 )
			{
				PR4 = (udb_pwOut[CH2_OUTPUT_CHANNEL] << 1) ;	// set timer to the pulse width
				LATEbits.LATE6 = 1 ;	// start the pulse by setting the E6 pin high
			}
			else
			{
				PR4 = 100 ;				// set timer to the pulse width
				LATEbits.LATE6 = 0 ;	// skip the pulse by setting the E6 pin low
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
