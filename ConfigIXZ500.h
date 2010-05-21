// used in the IXZ Tester

#define	ADCON2CONFIG 0b0010010000011000 ; // Vref+ ref, scana ch0, int every 7, 16word, usa A only


#define	xrateBUFF	ADCBUF1
#define	yrateBUFF	ADCBUF3 
#define	zrateBUFF	ADCBUF2

#define	xaccelBUFF	ADCBUF4
#define	yaccelBUFF	ADCBUF5
#define	zaccelBUFF	ADCBUF6

#define XSIGN +
#define YSIGN +
#define ZSIGN -

//#define VREF

#define SCALEGYRO 4.95
#define SCALEACCEL 2.64

// Max inputs and outputs
#define MAX_INPUTS	5
#define MAX_OUTPUTS	6

// LED pins
#define LED_RED				LATFbits.LATF0
#define LED_GREEN			LATFbits.LATF1

// Pin locations of the hardware toggle switches
#define HW_SWITCH_1			(PORTDbits.RD3 == 0)
#define HW_SWITCH_2			(PORTDbits.RD2 == 0)
#define HW_SWITCH_3			(PORTFbits.RF6 == 0)

// BAUD Rates
#define UDB_BAUD_4800	51
#define UDB_BAUD_9600	25
#define UDB_BAUD_19200	12
