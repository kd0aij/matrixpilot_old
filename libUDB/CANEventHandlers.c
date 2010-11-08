#include "CANDataIDRefs.h"
#include "CANTelemetryManager.h"

// Process a event send with data identifier ID_EVENT
void processEvent(TELEMETRY_DATA* pteleData)
{
	switch(pteleData->arrayOffset)
	{
	case ID_AUTOPILOT_DCM_TELEMETRY_COMPLETE:
		break;
	
	// At the end of CAN navigation data update, send it out of the telemetry
	case ID_AUTOPILOT_NAV_TELEMETRY_COMPLETE:
		serial_output_8hz();
		break;

	default:
		break;
	}
	
	return;
}
