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
