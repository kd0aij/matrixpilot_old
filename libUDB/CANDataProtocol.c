// SEE END OF FILE FOR LICENSE TERMS

#include "CANInterface_internal.h"
#include "CANDataProtocol.h"
#include "CANDataIDrefs.h"

// Tracking if the CANbus is currently sending data or not.
volatile boolean	sendingCANData	= false;


void parse_received(unsigned int idRef, unsigned int arrayOffset, unsigned char dataLength, unsigned int* pData);


/**********************************************************************************************
	Receive data routines
***********************************************************************************************/

// Parse received CANbus data from registers into useable data.
// Then call the functions to parse the useable data into the database
void parse_received_data(const CAN_RX_PROTOCOL_STRUCT* pCANRXStruct)
{
	// Extract the mixed up bits of data from the identifier registers and put them into useful formats

	TELEMETRY_DATA rxData;

	rxData.byteSize = pCANRXStruct->pDLC->DLC;

	rxData.identifier = pCANRXStruct->pEID->EID13_6;

	DATA_INDEX arrayOffset;
	arrayOffset.index = 0;

	// Merge index from different parts of the registers
	arrayOffset._.index_low = pCANRXStruct->pDLC->EID5_0;
	arrayOffset._.index_high = pCANRXStruct->pEID->EID17_14;

	rxData.arrayOffset = arrayOffset.index;

	rxData.pData = (unsigned char*) pCANRXStruct->pData;
	
	parse_telemetry_data(&rxData);
};



/**********************************************************************************************
	Transmit data routines
***********************************************************************************************/

// Transmit the next data packet
boolean transmit_data(const CAN_TX_PROTOCOL_STRUCT* pTxData)
{
	DATA_INDEX		arrayOffset;
	TELEMETRY_DATA	teleData;

	// If not sending already, return false
	if(sendingCANData == false)
		return false;

	teleData.pData = (unsigned char*) pTxData->pData;

	// Get the next required data description
	if(get_next_telemetry_data(&teleData) == false)
	{
		sendingCANData = false;
		return false;
	}
	else
	{
		pTxData->pDLC->DLC 	= teleData.byteSize;
	
		arrayOffset.index 	= teleData.arrayOffset;

		pTxData->pDLC->EID5_0 	= arrayOffset._.index_low;
		pTxData->pEID->EID17_14	= arrayOffset._.index_high;
	
		pTxData->pEID->EID13_6	= teleData.identifier;
	}

	pTxData->pTxCon->TXREQ = 1;
	return true;
};



// Start CAN data send. Do not start if running already
void start_CAN_data_send(const CAN_TX_PROTOCOL_STRUCT* pTxData)
{
	if(sendingCANData == false)
	{
		sendingCANData = true;
		transmit_data(pTxData);
	};

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
