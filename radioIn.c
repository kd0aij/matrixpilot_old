#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

//	Measure the pulse widths of the servo channel inputs from the radio.
//	The dsPIC makes this rather easy to do using its capture feature.

//	One of the channels is also used to validate pulse widths to detect loss of radio.

//	The pulse width inputs can be directly converted to units of pulse width outputs to control
//	the servos by simply dividing by 2.

void init_capture(void)
{
	T2CON = 0b1000000000000000  ;	// turn on timer 2 with no prescaler
	TRISD = 0b1111111111111111 ;	// make the d port input, to enable IC1 and IC2
	TRISFbits.TRISF6 = 1 ;			// make F6 an input to enable the 3rd switch
	IC1CON = IC2CON = IC7CON = IC8CON = 0b0010000010000001 ;
	
	int i;
	for (i=0; i <= NUM_INPUTS; i++)
		rise[i] = pwIn[i] = pwTrim[i] = 3000;
	
	IPC0bits.IC1IP = IPC1bits.IC2IP = IPC4bits.IC7IP = IPC4bits.IC8IP = 7 ; // priority 7
	IFS0bits.IC1IF = IFS0bits.IC2IF = IFS1bits.IC7IF = IFS1bits.IC8IF = 0 ; // clear the interrupt
	IEC0bits.IC1IE = IEC0bits.IC2IE = IEC1bits.IC7IE = IEC1bits.IC8IE = 1 ; // turn on the interrupt
	
	if (NUM_INPUTS > 4)
	{
		TRISEbits.TRISE8 = 1 ;	 // set E8 to be an input pin
		INTCON2bits.INT0EP = 0;  // Set up the 5th input channel to start out reading low-to-high edges
		IPC0bits.INT0IP = 7 ; // priority 7
		IFS0bits.INT0IF = 0 ; // clear the interrupt
		IEC0bits.INT0IE = 1 ; // turn on the interrupt
	}
	
	return ;
}

// Input Channel 1
void __attribute__((__interrupt__,__no_auto_psv__)) _IC7Interrupt(void)
{
	indicate_loading_inter ;
	if (PORTBbits.RB4)
	{
		 rise[1] = IC7BUF ;
	}
	else
	{
		pwIn[1] = ((IC7BUF - rise[1]) >> 1 ) ;
	}

	IFS1bits.IC7IF = 0 ; // clear the interrupt
	return ;
}

// Input Channel 2
void __attribute__((__interrupt__,__no_auto_psv__)) _IC8Interrupt(void)
{
	indicate_loading_inter ;
	if (PORTBbits.RB5)
	{
		 rise[2] = IC8BUF ;
	}
	else
	{
		pwIn[2] = ((IC8BUF - rise[2]) >> 1 ) ;
	}

	IFS1bits.IC8IF = 0 ; // clear the interrupt
	return ;
}

// Input Channel 3
void __attribute__((__interrupt__,__no_auto_psv__)) _IC2Interrupt(void)
{
	indicate_loading_inter ;
	if (PORTDbits.RD1)
	{
		 rise[3] = IC2BUF ;
	}
	else
	{
		pwIn[3] = ((IC2BUF - rise[3]) >> 1 ) ;
	}

	IFS0bits.IC2IF = 0 ; // clear the interrupt
	return ;
}

// Input Channel 4
void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
{
	indicate_loading_inter ;
	if (PORTDbits.RD0)
	{
		 rise[4] = IC1BUF ;
	}
	else
	{
		pwIn[4] = ((IC1BUF - rise[4]) >> 1 );
		
		// The failsafe channel might not be Input 4, so if not, make sure to also connect Input 4 to the receiver
		// to make sure this code is checked.
		if ( (pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			pulsesselin++ ;
		}
	}
	IFS0bits.IC1IF =  0 ; // clear the interrupt
	return ;
}

// Input Channel 5 (Pin RE8)
void __attribute__((__interrupt__,__no_auto_psv__)) _INT0Interrupt(void)
{
	indicate_loading_inter ;
	
	int t = TMR2 ;
	
	if (PORTEbits.RE8)
	{
		rise[5] = t ;
		INTCON2bits.INT0EP = 1 ;	// Set up the interrupt to read high-to-low edges
	}
	else
	{
		pwIn[5] = ((t - rise[5]) >> 1 ) ;
		INTCON2bits.INT0EP = 0 ;	// Set up the interrupt to read low-to-high edges
	}
	
	IFS0bits.INT0IF = 0 ; 		// clear the interrupt
	return;
}


