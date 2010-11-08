// SEE END OF FILE FOR LICENSE TERMS

#include "CANTelemetryManager.h"
#include "CANDataIDrefs.h"

// An array of telemetry queue requests, one per queue
boolean telemetryRequests[TELEMETRY_LIST_COUNT];

// The index into the telemetry queues
// Needs a count for every queue since the transmission of
// a low prority list can be interrupted by a higher priority
unsigned char telemetryIndices[TELEMETRY_LIST_COUNT];

// Get the next telemetry identifier in the queue
//  Return ID_NULL if finished sending
TELEMETRY_LIST_ENTRY* get_next_telemetry_send_item(void);

// Get a pointer to the variable from the identifier
extern unsigned char* get_variable_from_identifier(unsigned int identifier, unsigned int arrayOffset, unsigned int* pbyteSize);


// Request that a queue of telemetry items be sent
// queueNo is the index of the requested queue
// Lowest queue numbers have priority
inline void requestTelemetrySend(unsigned char queueNo)
{
	telemetryRequests[queueNo] = true;
};

// Initialise everything
void initTelemetryManager(void)
{
	unsigned char index = 0;

	for(index = 0; index < TELEMETRY_LIST_COUNT; index++)
	{
		telemetryIndices[index] = 0;
		telemetryRequests[index] = false;
	}
};

// Get the next telemetry data
// return true if data is filled, return false if data send finished
boolean get_next_telemetry_data(TELEMETRY_DATA* pteleData)
{
	TELEMETRY_LIST_ENTRY* pTelemetryItem;
	unsigned char*  pData;
	unsigned int	byteSize;

	pTelemetryItem = get_next_telemetry_send_item();

	if (pTelemetryItem == ID_NULL)
	{
		return false;
	}

	pData = get_variable_from_identifier(pTelemetryItem->identifier, pTelemetryItem->arrayOffset, &byteSize);

	if(pData == 0)
	{
		pteleData->byteSize = 0;
		pteleData->arrayOffset = pTelemetryItem->arrayOffset;
		pteleData->identifier = pTelemetryItem->identifier;
		return true;
	}
	else
	{
		pteleData->byteSize = byteSize;
		pteleData->arrayOffset = pTelemetryItem->arrayOffset;
		pteleData->identifier = pTelemetryItem->identifier;
		memcpy(pteleData->pData, pData, byteSize);
	}

	return true;
};


// Get the next telemetry identifier in the highest priority active queue
//  Return ID_NULL if finished sending everything
TELEMETRY_LIST_ENTRY* get_next_telemetry_send_item()
{
	TELEMETRY_LIST_ENTRY* 	pTelemetryItem;

	unsigned char	queueIndex = 0;
	unsigned char	itemIndex = 0;
	
	while(queueIndex < TELEMETRY_LIST_COUNT)
	{
		if(telemetryRequests[queueIndex] == true)
		{
			itemIndex = telemetryIndices[queueIndex];
			pTelemetryItem 	= &(telemetryLists[queueIndex][itemIndex]);

			if(pTelemetryItem->identifier == ID_NULL)
			{
				telemetryRequests[queueIndex] = false;
				telemetryIndices[queueIndex] = 0;
			}
			else
			{
				telemetryIndices[queueIndex] = itemIndex + 1;
				queueIndex = TELEMETRY_LIST_COUNT;
			}
		}
		else
		{
			pTelemetryItem = ID_NULL;
		}
		queueIndex++;
	};
	
	
	return pTelemetryItem;
};


// Parse incoming telemtry data
// Return true if parsed ok. Return false if not ok
boolean parse_telemetry_data(const TELEMETRY_DATA* pteleData)
{
	unsigned int byteSize;

	unsigned char* pData = get_variable_from_identifier(pteleData->identifier, pteleData->arrayOffset, &byteSize);

	if(pteleData->identifier == ID_EVENT)
		processEvent(pteleData);
	else if(pData == 0) return false;

	// Check the data sizes match
	if(byteSize == pteleData->byteSize)
	{
		memcpy(pData, pteleData->pData, pteleData->byteSize);
	}

	return true;
};



/****************************************************************************/
// This is part of the servo and radio interface software
//
// ServoInterface source code
//	http://code.google.com/p/rc-servo-interface
//
// Copyright 2010 ServoInterface Team
// See the AUTHORS.TXT file for a list of authors of ServoInterface.
//
// ServoInterface is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ServoInterface is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with ServoInterface.  If not, see <http://www.gnu.org/licenses/>.
//
// Many parts of ServoInterface use either modified or unmodified code
// from the MatrixPilot pilot project.
// The project also contains code for modifying MatrixPilot to operate
// with ServoInterface.
// For details, credits and licenses of MatrixPilot see the AUTHORS.TXT file.
// or see this website: http://code.google.com/p/gentlenav
/****************************************************************************/
