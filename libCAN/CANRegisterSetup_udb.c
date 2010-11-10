// SEE END OF FILE FOR LICENSE TERMS

// CANbus structures defined for transmission

// The CANbus port changes between the AP and interface board.
// This is done so that CANbus loop testing is possible on the interface board

// CANdefines does simple setup between UDB and interface
#include "../libUDB/libUDB.h"
#include "CANDataProtocol.h"

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
