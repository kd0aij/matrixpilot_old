#include "libUDB_internal.h"

#if (BOARD_TYPE == UDB_2_BOARD)

//	routines to drive the PWM pins for the servos,
//	assumes the use of the 16MHz crystal.

int udb_pwOut[MAX_OUTPUTS+1] ;	// pulse widths for servo outputs

int twentyHertzCounter = 0 ;


void udb_init_pwm( void )	// initialize the PWM
{
	OC1CONbits.OCM = 
	OC2CONbits.OCM = 
	OC3CONbits.OCM = 
	OC4CONbits.OCM = 
	OC5CONbits.OCM = 
	OC6CONbits.OCM = 
	OC7CONbits.OCM = 
	OC8CONbits.OCM = 0 ;  // disable
	
	OC1R = OC2R = OC3R = OC4R = OC5R = OC6R = OC7R = OC8R = 0 ;  // no first pulse
	OC1RS = OC2RS = OC3RS = OC4RS = OC5RS = OC6RS = OC7RS = OC8RS = 0 ; // initial pulse
	
	OC1CONbits.OCM = 
	OC2CONbits.OCM = 
	OC3CONbits.OCM = 
	OC4CONbits.OCM = 
	OC5CONbits.OCM = 
	OC6CONbits.OCM = 
	OC7CONbits.OCM = 
	OC8CONbits.OCM = 6 ;  // enable
	
	int i;
	for (i=0; i <= NUM_OUTPUTS; i++)
		udb_pwOut[i] = 0;
	
#if (NORADIO == 1)
	udb_radio_on = 1 ;
#endif
	
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
	
	//  note: at this point the PWM is running, so there are pulses going out,
	//	but the PWM interrupt is still off, so no interrupts are coming in yet to compute pulses.
	//  the PWM interrupt is turned on within the A/D interrupt processing
	
	return ;
}


void udb_set_action_state(boolean newValue)
{
	LATEbits.LATE4 = newValue ;
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
	
	OC1RS = udb_pwOut[1] ;
	OC2RS = udb_pwOut[2] ;
	OC3RS = udb_pwOut[3] ;
	OC4RS = udb_pwOut[4] ;
	OC5RS = udb_pwOut[5] ;
	OC6RS = udb_pwOut[6] ;
	OC7RS = udb_pwOut[7] ;
	OC8RS = udb_pwOut[8] ;
	
	IFS2bits.PWMIF = 0 ; /* clear the interrupt */
	
	// interrupt_restore_extended_state ;
	return ;
}

#endif
