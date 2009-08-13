#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

//	routines to drive the PWM pins for the servos,
//	assumes the use of the 16MHz crystal.

int gpscount ; // counter to initialize GPS
int outputNum ;

void setupOutputs( void ) ;
void dummyRudderAndThrottleControl( void ) ;
void manualPassthrough( void ) ;
void passthroughChannel(int inChannel, int outChannel, char reversed) ;

void init_pwm( void )	// initialize the PWM
{
	PDC1 = PDC2 = 3000 + SERVOSAT*500 ;
	PDC3 = 3000 ;
	
	firstsamp = 1;	// flag for the first sample
	calibcount = 400 ; // wait 400 PWM pulses before turning on the control (10 seconds)
	gpscount = 1000 ; // wait 25 seconds for GPS to initialize

	int i;
	for (i=0; i < NUM_OUTPUTS; i++)
		pwOut[i] = 3000;
	
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
		IEC1bits.T4IE = 0 ;				// disable timer 4 interrupt for now (enable for each pulse)
	}
	
	//  note: at this point the PWM is running, so there are pulses going out,
	//	but the PWM interrupt is still off, so no interrupts are coming in yet to compute pulses.
	//  the PWM interrupt is turned on within the A/D interrupt processing
	
	return ;
}

#define SERVORANGE SERVOSAT*1000
#define SERVOMAX 3000 + SERVORANGE
#define SERVOMIN 3000 - SERVORANGE

int pulsesat ( long pw ) // saturation logic to maintain pulse width within bounds
{
	if ( pw > SERVOMAX ) pw = SERVOMAX ;
	if ( pw < SERVOMIN ) pw = SERVOMIN ;
	return pw ;
}

void __attribute__((__interrupt__,__no_auto_psv__)) _PWMInterrupt(void)
{
	indicate_loading_inter ;
	
	//	Executes whatever needs to be done every 20 milliseconds, using the PWM clock.
	//	This is a good place to run the A/D digital filters and compute pulse widths for servos.
	//	Also, this is used to wait a few pulses before recording input DC offsets.
	switch (calibcount ) {
	// case 0 is when the control is up and running

	case 0: {
		imu() ;	
		aileronCntrl() ;
		elevatorCntrl() ;
		dummyRudderAndThrottleControl() ;
		break ;
	}

	case 1: {
		// almost ready to turn the control on, save the input offsets
		xaccel.offset = xaccel.value ;
		xrate.offset = xrate.value ;
		yaccel.offset = yaccel.value ;
		yrate.offset = yrate.value ;
		zaccel.offset = zaccel.value - 2*GRAVITY ; // GRAVITY is measured in A-D/2 units
		zrate.offset = zrate.value ;
		vref.offset = vref.value ;
		manualPassthrough() ;	// Allow manual control while starting up
		break ;
	}
	default: {
		// otherwise, there is not anything to do
		manualPassthrough() ;	// Allow manual control while starting up
		break ;
	}
	}
	
	setupOutputs() ;
		
	// count down the startup counter to 0
	if ( calibcount > 0 ) calibcount-- ;

	switch (gpscount ) {
	// case 0 is when the control is up and running

	case 8:
	{
		U2BRG = 12 ;
	}
	case 10:
	{
		set_baud() ; //	change the baud rate if it was used at 4800 binary
		break ;
	}
	case 12:
	{
		set_bin() ;	// put into binary mode, if it is fresh from the factory
		break ;
	}

	default: {
	}
		// otherwise, there is not anything to do
		break ;
	}
	// count down the startup counter to 0
	if ( gpscount > 0 ) gpscount-- ;
	
	IFS2bits.PWMIF = 0 ; /* clear the interrupt */
	return ;
}

// Eventually replace this with real ruddder, throttle, etc. control functions in separate files
void dummyRudderAndThrottleControl( void )
{
	passthroughChannel(RUDDER_INPUT_CHANNEL, RUDDER_OUTPUT_CHANNEL, 0) ;
	passthroughChannel(THROTTLE_INPUT_CHANNEL, THROTTLE_OUTPUT_CHANNEL, 0) ;
	
	return ;
}

void manualPassthrough( void )
{
	passthroughChannel(THROTTLE_INPUT_CHANNEL, THROTTLE_OUTPUT_CHANNEL, 0) ;
	passthroughChannel(AILERON_INPUT_CHANNEL, AILERON_OUTPUT_CHANNEL, 0) ;
	passthroughChannel(AILERON_INPUT_CHANNEL, AILERON_REVERSED_OUTPUT_CHANNEL, 1) ;
	passthroughChannel(ELEVATOR_INPUT_CHANNEL, ELEVATOR_OUTPUT_CHANNEL, 0) ;
	passthroughChannel(RUDDER_INPUT_CHANNEL, RUDDER_OUTPUT_CHANNEL, 0) ;
	
	return ;
}

void passthroughChannel(int inChannel, int outChannel, char reversed)
{
	union longww val ;
	
	if (reversed == 0)
	{
		val.WW = pwIn[inChannel] ;
	}
	else
	{
		val.WW = (long)6000 - (long)pwIn[inChannel] ;
	}
	
	pwOut[outChannel] = pulsesat(val.WW) ;
	
	return ;
}

void setupOutputs( void )
{
	PDC1 = pwOut[0] ;
	PDC2 = pwOut[1] ;
	PDC3 = pwOut[2] ;
	
	if (NUM_OUTPUTS > 3)
	{
		outputNum = 3 ;
		PR4 = (pwOut[3] << 1) ;	// set timer to the rudder pulse width
		LATEbits.LATE0 = 1 ;	// start the pulse by setting the pin high
		TMR4 = 0 ;				// start timer at 0
		IFS1bits.T4IF = 0 ;		// clear the interrupt
		IEC1bits.T4IE = 1 ;		// enable timer 4 interrupt
	}
	
	return;
}

void __attribute__((__interrupt__,__no_auto_psv__)) _T4Interrupt(void)
{
	indicate_loading_inter ;
	
	switch (outputNum) {
		case 3:
			LATEbits.LATE0 = 0 ;		// end the pulse by setting the pin low
			if (NUM_OUTPUTS > 4)
			{
				outputNum = 4 ;
				PR4 = (pwOut[4] << 1) ;	// set timer to the rudder pulse width
				LATEbits.LATE2 = 1 ;	// start the pulse by setting the pin high
				TMR4 = 0 ;				// start timer at 0
			}
			else
			{
				IEC1bits.T4IE = 0 ;		// disable timer 4 interrupt
			}
			break;
		case 4:
			LATEbits.LATE2 = 0 ;		// end the pulse by setting the pin low
			if (NUM_OUTPUTS > 5)
			{
				outputNum = 5 ;
				PR4 = (pwOut[5] << 1) ;	// set timer to the rudder pulse width
				LATEbits.LATE4 = 1 ;	// start the pulse by setting the pin high
				TMR4 = 0 ;				// start timer at 0
			}
			else
			{
				IEC1bits.T4IE = 0 ;		// disable timer 4 interrupt
			}
			break;
		case 5:
			LATEbits.LATE4 = 0 ;		// end the pulse by setting the pin low
			IEC1bits.T4IE = 0 ;			// disable timer 4 interrupt
			break;
	}
	
	IFS1bits.T4IF = 0 ;					// clear the interrupt
	return;
}
