// CANbus structures defined for transmission

// The CANbus port changes between the AP and interface board.
// This is done so that CANbus loop testing is possible on the interface board

// CANdefines does simple setup between UDB and interface
#include "libUDB.h"
#include "CANDataProtocol.h"


/*******************STRUCTURES FOR CAN INTERFACE******************/
#if(BOARD_TYPE == CAN_INTERFACE)

const CAN_TX_PROTOCOL_STRUCT	CANxTX1ProtoStruct = 
	{
		&C2TX1SIDbits,
		&C2TX1EIDbits,
		&C2TX1DLCbits,
		&C2TX1B1,
		&C2TX1CONbits
	};

const CAN_RX_PROTOCOL_STRUCT	CANxRX2ProtoStruct = 
	{
		&C2RX1SIDbits,
		(CxRXEIDBITS*) &C2RX1EID,
		&C2RX1DLCbits,
		&C2RX1B1
	};


/***************STRUCTURES FOR MATRIXPILOT **********************/
#else

const CAN_TX_PROTOCOL_STRUCT	CANxTX1ProtoStruct = 
	{
		&C1TX1SIDbits,
		&C1TX1EIDbits,
		&C1TX1DLCbits,
		&C1TX1B1,
		&C1TX1CONbits
	};

const CAN_RX_PROTOCOL_STRUCT	CANxRX2ProtoStruct = 
	{
		&C1RX1SIDbits,
		(CxRXEIDBITS*) &C1RX1EID,
		&C1RX1DLCbits,
		&C1RX1B1
	};


#endif

