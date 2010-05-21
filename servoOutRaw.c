#include "libUDB_internal.h"

//	routines to drive the PWM pins for the servos,
//	assumes the use of the 16MHz crystal.

#define SERVOCENTER 3000
#define SERVORANGE (int) (SERVOSAT*1000)
#define SERVOMAX SERVOCENTER + SERVORANGE
#define SERVOMIN SERVOCENTER - SERVORANGE


int twentyHertzCounter = 0 ;
int outputNum ;


void setupOutputs( void ) ;


void udb_init_pwm( void )	// initialize the PWM
{
	PDC1 = PDC2 = PDC3 = 3000 ;
	
	int i;
	for (i=0; i <= NUM_OUTPUTS; i++)
		udb_pwOut[i] = 0;
	
#if (NORADIO == 1)
	udb_radio_on = 1 ;
#endif
	
	TRISE = 0b1111111111000000 ;
	PTPER = 25000 ;			// 25 millisecond period at 16 Mz clock, prescale = 4	
	PTCONbits.PTCKPS = 1;	// prescaler = 4

	PWMCON1bits.PMOD1 = 1 ; // independent PWM mode
	PWMCON1bits.PMOD2 = 1 ;
	PWMCON1bits.PMOD3 = 1 ;
	PWMCON1bits.PEN1L = 0 ; // low pins used as digital I/O
	PWMCON1bits.PEN2L = 0 ;
	PWMCON1bits.PEN3L = 0 ;
	
	PTCONbits.PTEN = 1; 	// turn on the PWM 
	IFS2bits.PWMIF = 0 ; 	// clear the PWM interrupt
	IPC9bits.PWMIP = 3 ;    // priority 3
	
	if (NUM_OUTPUTS > 3)
	{
		T4CON = 0b1000000000000000  ;	// turn on timer 4 with no prescaler
		IPC5bits.T4IP = 7 ;				// priority 7
		IEC1bits.T4IE = 0 ;				// disable timer 4 interrupt for now (enable for each set of pulses)
	}
	
	//  note: at this point the PWM is running, so there are pulses going out,
	//	but the PWM interrupt is still off, so no interrupts are coming in yet to compute pulses.
	//  the PWM interrupt is turned on within the A/D interrupt processing
	
	return ;
}


int udb_servo_pulsesat ( long pw ) // saturation logic to maintain pulse width within bounds
{
	if ( pw > SERVOMAX ) pw = SERVOMAX ;
	if ( pw < SERVOMIN ) pw = SERVOMIN ;
	return (int)pw ;
}


void __attribute__((__interrupt__,__no_auto_psv__)) _PWMInterrupt(void)
{
	// interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	//	Executes whatever needs to be done every 25 milliseconds, using the PWM clock.
	//	This is a good place to run the A/D digital filters and compute pulse widths for servos.
	//	Also, this is used to wait a few pulses before recording input DC offsets.

#if ( NORADIO == 0 )
	twentyHertzCounter++ ;
	if ( twentyHertzCounter >= 2 )
	{
		if ( failSafePulses == 0 )
		{
			udb_radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
		else if ( failSafePulses >= 2 )
		{
			udb_radio_on = 1 ;
			LED_GREEN = LED_ON ;
		}
		twentyHertzCounter = 0 ;
		failSafePulses = 0 ;
	}
#endif
	
	udb_servo_callback_prepare_outputs() ;
	setupOutputs() ;
	
	IFS2bits.PWMIF = 0 ; /* clear the interrupt */
	
	// interrupt_restore_extended_state ;
	return ;
}


void setupOutputs( void )
{
	PDC1 = udb_pwOut[1] ;
	PDC2 = udb_pwOut[2] ;
	PDC3 = udb_pwOut[3] ;
	
	if (NUM_OUTPUTS > 3)
	{
		outputNum = 4 ;
		if ( udb_pwOut[4] > 0 )
		{
			PR4 = (udb_pwOut[4] << 1) ;	// set timer to the pulse width
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
	}
	
	return;
}

void __attribute__((__interrupt__,__no_auto_psv__)) _T4Interrupt(void)
{
	interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	switch ( outputNum ) {
		case 4:
			LATEbits.LATE0 = 0 ;		// end the pulse by setting the E0 pin low (output 4)
			if (NUM_OUTPUTS > 4)
			{
				outputNum = 5 ;
				if ( udb_pwOut[5] > 0 )
				{
					PR4 = (udb_pwOut[5] << 1) ;	// set timer to the pulse width
					LATEbits.LATE2 = 1 ;	// start the pulse by setting the E2 pin high (output 5)
				}
				else
				{
					PR4 = 100 ;				// set timer to the pulse width
					LATEbits.LATE2 = 0 ;	// skip the pulse by setting the E2 pin low (output 5)
				}	
				TMR4 = 0 ;				// start timer at 0
			}
			else
			{
				IEC1bits.T4IE = 0 ;		// disable timer 4 interrupt
			}
			break ;
		
		case 5:
			LATEbits.LATE2 = 0 ;		// end the pulse by setting the E2 pin low (output 5)
			if (NUM_OUTPUTS > 5)
			{
				outputNum = 6 ;
				if ( udb_pwOut[6] > 0 )
				{
					PR4 = (udb_pwOut[6] << 1) ;	// set timer to the pulse width
					LATEbits.LATE4 = 1 ;	// start the pulse by setting the E4 pin high (output 6)
				}
				else
				{
					PR4 = 100 ;				// set timer to the pulse width
					LATEbits.LATE4 = 0 ;	// start the pulse by setting the E4 pin high (output 6)
				}
				TMR4 = 0 ;				// start timer at 0
			}
			else
			{
				IEC1bits.T4IE = 0 ;		// disable timer 4 interrupt
			}
			break ;
		case 6:
			LATEbits.LATE4 = 0 ;		// end the pulse by setting the E4 pin low (output 6)
			IEC1bits.T4IE = 0 ;			// disable timer 4 interrupt
			break ;
	}
	
	IFS1bits.T4IF = 0 ;					// clear the interrupt
	
	interrupt_restore_extended_state ;
	return;
}
