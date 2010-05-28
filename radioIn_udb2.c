#include "libUDB_internal.h"

#if (BOARD_TYPE == UDB_2_BOARD)

//	Measure the pulse widths of the servo channel inputs from the radio.
//	The dsPIC makes this rather easy to do using its capture feature.

//	One of the channels is also used to validate pulse widths to detect loss of radio.

//	The pulse width inputs can be directly converted to units of pulse width outputs to control
//	the servos by simply dividing by 2.

int udb_pwIn[MAX_INPUTS+1] ;	// pulse widths of radio inputs
int udb_pwTrim[MAX_INPUTS+1] ;	// initial pulse widths for trimming

boolean udb_radio_on = 0;
int failSafePulses = 0 ;

unsigned int rise[MAX_INPUTS+1] ;	// rising edge clock capture for radio inputs


void udb_init_capture(void)
{
	T2CON = 0b1000000000000000  ;	// turn on timer 2 with no prescaler
	
	int i;
	for (i=0; i <= NUM_INPUTS; i++)
		udb_pwIn[i] = udb_pwTrim[i] = 0 ;
	
	IC1CON = IC2CON = IC7CON = IC8CON =
	IC1CON = IC2CON = IC7CON = IC8CON = 0b0010000010000001 ;
	
	IPC0bits.IC1IP = IPC1bits.IC2IP = IPC4bits.IC7IP = IPC4bits.IC8IP =
	IPC0bits.IC1IP = IPC1bits.IC2IP = IPC4bits.IC7IP = IPC4bits.IC8IP = 6 ; // priority 6
	
	IFS0bits.IC1IF = IFS0bits.IC2IF = IFS1bits.IC7IF = IFS1bits.IC8IF =
	IFS0bits.IC1IF = IFS0bits.IC2IF = IFS1bits.IC7IF = IFS1bits.IC8IF = 0 ; // clear the interrupt
	
	if (NUM_INPUTS > 0) IEC1bits.IC7IE = 1 ; // turn on interrupt for input 1
	if (NUM_INPUTS > 1) IEC1bits.IC8IE = 1 ; // turn on interrupt for input 2
	if (NUM_INPUTS > 2) IEC0bits.IC2IE = 1 ; // turn on interrupt for input 3
	if (NUM_INPUTS > 3) IEC0bits.IC1IE = 1 ; // turn on interrupt for input 4
	if (NUM_INPUTS > 4) IEC0bits.IC1IE = 1 ; // turn on interrupt for input 5
	if (NUM_INPUTS > 5) IEC0bits.IC1IE = 1 ; // turn on interrupt for input 6
	if (NUM_INPUTS > 6) IEC0bits.IC1IE = 1 ; // turn on interrupt for input 7
	if (NUM_INPUTS > 7) IEC0bits.IC1IE = 1 ; // turn on interrupt for input 8
	
	return ;
}


void udb_servo_record_trims(void)
{
	int i;
	for (i=0; i <= NUM_INPUTS; i++)
		udb_pwTrim[i] = udb_pwIn[i] ;
	
	return ;
}


// Input Channel 1
void __attribute__((__interrupt__,__no_auto_psv__)) _IC7Interrupt(void)
{
	unsigned int time ;	
	IFS1bits.IC7IF = 0 ; // clear the interrupt
	while ( IC7CONbits.ICBNE )
	{
		time = IC7BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTBbits.RB4)
	{
		 rise[1] = time ;
	}
	else
	{
		udb_pwIn[1] = ((time - rise[1]) >> 1 ) ;
		
#if ( FAILSAFE_INPUT_CHANNEL == 1 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif

	return ;
}


// Input Channel 2
void __attribute__((__interrupt__,__no_auto_psv__)) _IC8Interrupt(void)
{
	unsigned int time ;
	IFS1bits.IC8IF = 0 ; // clear the interrupt
	while ( IC8CONbits.ICBNE )
	{
		time = IC8BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTBbits.RB5)
	{
		 rise[2] = time ;
	}
	else
	{
		udb_pwIn[2] = ((time - rise[2]) >> 1 ) ;
		
#if ( FAILSAFE_INPUT_CHANNEL == 2 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}	
#endif
	
	return ;
}


// Input Channel 3
void __attribute__((__interrupt__,__no_auto_psv__)) _IC2Interrupt(void)
{
	unsigned int time ;
	IFS0bits.IC2IF = 0 ; // clear the interrupt
	while ( IC2CONbits.ICBNE )
	{
		time = IC2BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD1)
	{
		 rise[3] = time ;
	}
	else
	{
		udb_pwIn[3] = ((time - rise[3]) >> 1 ) ;
		
#if ( FAILSAFE_INPUT_CHANNEL == 3 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}


// Input Channel 4
void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
{
	unsigned int time ;
	IFS0bits.IC1IF =  0 ; // clear the interrupt
	while ( IC1CONbits.ICBNE )
	{
		time = IC1BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD0)
	{
		 rise[4] = time ;
	}
	else
	{
		udb_pwIn[4] = ((time - rise[4]) >> 1 );
		
#if ( FAILSAFE_INPUT_CHANNEL == 4 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}


// Input Channel 5
void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
{
	unsigned int time ;
	IFS0bits.IC1IF =  0 ; // clear the interrupt
	while ( IC1CONbits.ICBNE )
	{
		time = IC1BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD0)
	{
		 rise[5] = time ;
	}
	else
	{
		udb_pwIn[5] = ((time - rise[5]) >> 1 );
		
#if ( FAILSAFE_INPUT_CHANNEL == 5 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}


// Input Channel 6
void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
{
	unsigned int time ;
	IFS0bits.IC1IF =  0 ; // clear the interrupt
	while ( IC1CONbits.ICBNE )
	{
		time = IC1BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD0)
	{
		 rise[6] = time ;
	}
	else
	{
		udb_pwIn[6] = ((time - rise[6]) >> 1 );
		
#if ( FAILSAFE_INPUT_CHANNEL == 6 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}


// Input Channel 7
void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
{
	unsigned int time ;
	IFS0bits.IC1IF =  0 ; // clear the interrupt
	while ( IC1CONbits.ICBNE )
	{
		time = IC1BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD0)
	{
		 rise[7] = time ;
	}
	else
	{
		udb_pwIn[7] = ((time - rise[7]) >> 1 );
		
#if ( FAILSAFE_INPUT_CHANNEL == 7 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}


// Input Channel 8
void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
{
	unsigned int time ;
	IFS0bits.IC1IF =  0 ; // clear the interrupt
	while ( IC1CONbits.ICBNE )
	{
		time = IC1BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD0)
	{
		 rise[8] = time ;
	}
	else
	{
		udb_pwIn[8] = ((time - rise[8]) >> 1 );
		
#if ( FAILSAFE_INPUT_CHANNEL == 8 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}



#endif
