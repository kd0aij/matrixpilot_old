// used for the UDB2

#define	ADCON2CONFIG 0b0010010000011000 ; //?

#define	xrateBUFF	ADCBUF1 //?
#define	yrateBUFF	ADCBUF3  //?
#define	zrateBUFF	ADCBUF2 //?

#define	xaccelBUFF	ADCBUF4 //?
#define	yaccelBUFF	ADCBUF5 //?
#define	zaccelBUFF	ADCBUF6 //?

#define XSIGN + //?
#define YSIGN + //?
#define ZSIGN - //?

//#define VREF

#define SCALEGYRO 4.95 //?
#define SCALEACCEL 2.64 //?

// Max inputs and outputs
#define MAX_INPUTS	8
#define MAX_OUTPUTS	8

// LED pins
#define LED_RED				LATEbits.LATE1
#define LED_GREEN			LATEbits.LATE2
#define LED_3				LATEbits.LATE3
#define LED_4				LATEbits.LATE4

// There are no hardware toggle switches on the UDB2, so use values of 0
#define HW_SWITCH_1			0
#define HW_SWITCH_2			0
#define HW_SWITCH_3			0

// BAUD Rates
#define UDB_BAUD_4800	51 //?
#define UDB_BAUD_9600	25 //?
#define UDB_BAUD_19200	12 //?
