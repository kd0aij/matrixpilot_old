#include "../libDCM/libDCM.h"
#include "../libDCM/libDCM_internal.h"
#include "../MatrixPilot/defines.h"
#include "../libUDB/libUDB_internal.h"

#include "CANTelemetryManager.h"
#include "CANDataIDrefs.h"
#include "../CANInterface/heartbeat.h"
#include <string.h>

// A buffer for variables aquired by functions.
// THIS ONLY WORKS FOR:
//  single canbus and dual canbus atthe same interrupt priority
unsigned char tempBuffer[8];

// temporary place to put the interface clock variable
unsigned int interfaceClock;


// Get the data pointer to a variable from its identifier and array offset
// The array offset acts as a index into array variables
unsigned char* get_node_variable_from_identifier(unsigned int identifier, unsigned int arrayOffset, unsigned int* pbyteSize)
{
	unsigned char* 	pData;

#if(BOARD_TYPE == CAN_INTERFACE)
	unsigned int 	tempint;
#endif

	switch(identifier)
	{

	case ID_CLOCK_TICK:
		tempint = getHeartbeatTick();
		memcpy(tempBuffer, &tempint, sizeof(tempint));
		pData = (unsigned char*) &tempBuffer;
		*pbyteSize = sizeof(tempint);
		break;
	default:
		pData = 0;
		*pbyteSize = 0;
		break;
	}

	return pData;
}
