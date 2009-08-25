// Other defines for the UAV Dev Board


// Channel numbers on the board, mapped to positions in the pulse width arrays.
#define CHANNEL_1 0
#define CHANNEL_2 1
#define CHANNEL_3 2
#define CHANNEL_4 3
#define CHANNEL_5 4
#define CHANNEL_6 5


// Choose the type of air frame by setting AIRFRAME_TYPE in options.h
#define AIRFRAME_STANDARD	0	// Ailerons and Elevator, and Rudder passthrough
#define AIRFRAME_VTAIL		1	// Ailerons, and Elevator and Rudder as V-tail controls
#define AIRFRAME_DELTA		2	// Aileron and Elevator as Elevons, and Rudder passthrough
#define AIRFRAME_HELI		3	// Aileron (Front-Left), Elevator (Rear), and 2ndAileron (Front-Right), and Rudder passthrough


// Pin locations of the hardware toggle switches
#define HW_SWITCH_1			(PORTDbits.RD3)
#define HW_SWITCH_2			(PORTDbits.RD2)
#define HW_SWITCH_3			(PORTFbits.RF6)


// LED pins
#define LED_RED				LATFbits.LATF0
#define LED_GREEN			LATFbits.LATF1
#define LED_RED_DO_TOGGLE	__builtin_btg( (unsigned int*)&LATF , 0 )
#define LED_GREEN_DO_TOGGLE	__builtin_btg( (unsigned int*)&LATF , 1 )

// LED states
#define LED_ON		0
#define LED_OFF		1


// If GPS data has not been received for this many state machine cycles, consider the GPS lock to be lost.
#define GPS_DATA_MAX_AGE	3
