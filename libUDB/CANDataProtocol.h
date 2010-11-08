// SEE END OF FILE FOR LICENSE TERMS

//#include "ConfigCANbus.h"
#include "libUDB.h"
#include "CANTelemetryManager.h"

#ifndef DATA_PROTOCOL_H
#define DATA_PROTOCOL_H

// Structure index so that register values can be easily inserted
typedef struct tagINDEX_STRUCT
{
	unsigned int index_low	: 6;
	unsigned int index_high	: 4;
	unsigned int filler		: 6;
} INDEX_STRUCT;

typedef union
{
	INDEX_STRUCT _;
	unsigned int index;
} DATA_INDEX;



// Structure of TX extended identifier register
typedef struct tagCxRXEIDBITS
{
	unsigned int EID13_6	: 8;
	unsigned int EID17_14	: 4;
	unsigned int 			: 4;
} CxRXEIDBITS;


typedef struct tagCAN_TX_STRUCT
{
	volatile CxTXxSIDBITS*	pSID;
	volatile CxTXxEIDBITS*	pEID;
	volatile CxTXxDLCBITS*	pDLC;
	volatile unsigned int*	pData;
	volatile CxTXxCONBITS*  pTxCon;
} CAN_TX_PROTOCOL_STRUCT;


typedef struct tagCAN_RX_STRUCT
{
	volatile CxRXxSIDBITS*			pSID;
	volatile CxRXEIDBITS*			pEID;
	volatile CxRXxDLCBITS*			pDLC;
	volatile unsigned int*			pData;
} CAN_RX_PROTOCOL_STRUCT;

extern const CAN_TX_PROTOCOL_STRUCT	CANxTX1ProtoStruct;
extern const CAN_RX_PROTOCOL_STRUCT	CANxRX2ProtoStruct;

// parse data received from the CAN interface
void parse_received_data(const CAN_RX_PROTOCOL_STRUCT* pCANRXStruct);

// request to start sending data
void start_CAN_data_send(const CAN_TX_PROTOCOL_STRUCT* pTxData);

// send the next data packet
boolean transmit_data(const CAN_TX_PROTOCOL_STRUCT* pTXData);

#endif

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
