// SEE END OF FILE FOR LICENSE TERMS

#include "../libUDB/libUDB.h"
#include "../libUDB/libUDB_internal.h"
#include "../libCAN/CANInterface_defines.h"
#include "../libCAN/CANInterface_internal.h"
#include "../libCAN/CANDataProtocol.h"

unsigned int uiServosFound = 0;

// Servo data buffers for interface
unsigned int ServoOutDataBuff[8];
unsigned int ServoInDataBuff[8];

unsigned int RxTimeouts = 0;

OP_STATE op_status;

//---------------------------------------------------------------------

volatile unsigned int ServoTxMsg	= 0xFFFF;  	// Counter for which servo tx message is being done
volatile unsigned int DataTxMsg		= 0x0000;  	// Counter for which servo tx message is being done

//
// Intilializing the receive registers to be 0

void init_CAN2(void);
void config_CAN2_RX_SERVO(void);
void config_CAN2_RX_DATA(void);
void config_CAN2_TX(void);
void config_CAN2_COPRO_TX(void);

void ResetAllCAN2Tx(void);
void ResetAllCAN2Rx(void);

void init_cntrl_comms(void)
{
	init_CAN2();

	config_CAN2_RX_SERVO();
	config_CAN2_TX();
	config_CAN2_COPRO_TX();
	config_CAN2_RX_DATA();

 //Change to Operation Mode from Configuration Mode
 C2CTRLbits.REQOP = 0;
 while(C2CTRLbits.OPMODE != 0);//Wait for CAN2 mode change from Configuration Mode to normal mode

 //Enable transmission

 ServoTxMsg = 0;	// Clear the servo Tx message counter to indicate that CAN is ready
};


//-----------------------------------------------------------------------------------------------------------------------
		// Broadcast servo input control data on CANbus
//-----------------------------------------------------------------------------------------------------------------------
void send_radio_data(void)
{
	int index;

	if(C2TX0CONbits.TXREQ)
	{
		return;
	};

	ServoTxMsg = 1;

	int FoundServos = uiServosFound;

// If the servo is found then set the MSB of the data to show it.
	for(index = 0; index < 8; index++)
	{
		if((FoundServos & 0x0001) == 1)
		{
			ServoOutDataBuff[index] = pwIn[index+1] | 0x8000;
		}
		else
		{
			ServoOutDataBuff[index] = pwIn[index+1];
		};
		FoundServos >>= 1;
	};

	C2TX0EID = 0x0001;  	// First servo data set

	C2TX0B1 = ServoOutDataBuff[0];
	C2TX0B2 = ServoOutDataBuff[1];
	C2TX0B3 = ServoOutDataBuff[2];
	C2TX0B4 = ServoOutDataBuff[3];

	C2TX0CONbits.TXREQ = 1;
};


// Interface recieves servo data from autopilot
void receive_servo_data()
{
	if(ServoInDataBuff[THROTTLE_OUTPUT_CHANNEL] < THROTTLE_MINIMUM_OUTPUT)
		ServoInDataBuff[THROTTLE_OUTPUT_CHANNEL] = THROTTLE_MINIMUM_OUTPUT;

	RxTimeouts = 0;
};



//-------------------------------------------------------------------------------------------------------------------
				//Broadcast coprocessor data to whatever needs it
//-------------------------------------------------------------------------------------------------------------------
void send_coprocessor_data(void)
{
	requestTelemetrySend(0);	// Fast flight data is the first, highest priority queue
/*
	if(C2TX1CONbits.TXREQ == 1)	// If already transmitting data then return
	{
		return;
	}
*/
	start_CAN_data_send(&CANxTX1ProtoStruct);
}

//-------------------------------------------------------------------------------------------------------------------
				//init CAN2
//-------------------------------------------------------------------------------------------------------------------
void init_CAN2(void)
{
	TRISGbits.TRISG1 = 0;			// CAN 2 TX set to output	
	TRISGbits.TRISG0 = 1;			// CAN 2 RX set to input

	C2CTRLbits.CANCKS = 0;			// Select the CAN Master Clock . It is equal to 4Fcy here. 
									// (Fcy=4MHz)
	
	C2CFG1bits.SJW=00;			   	//Synchronized jump width time is 1 x TQ when SJW is equal to 00
	 
	C2CFG1bits.BRP = BRP_VAL;		//((FCY/(2*NTQ*BITRATE))-1)  
	
	 
	C2CFG2 = CAN_TIMING_CONFIG2;	// See canbus config for settings
	
	//CAN2 Interrupts
	C2INTF = 0;						//Reset all The CAN Interrupts 
	IFS2bits.C2IF = 0;  			//Reset the Interrupt Flag status register
	C2INTE = 0x000F;                //Enable interrupt sources
//	C2INTE = 0x00FF;                //Enable interrupt sources
	IEC2bits.C2IE = 1;				//Enable the CAN2 Interrupt 

};


//-----------------------------------------------------------------------------------------------------------------------
		// Configure recieve buffer 0 for servo 
//-----------------------------------------------------------------------------------------------------------------------
void config_CAN2_RX_SERVO(void)
{
// initializing the Receive Buffer 0 for high priority control transfers
 CAN_SID_RX rx_sid;

 rx_sid.bb = 0;
 rx_sid.format.protocol		 	= CANB_PROTOCOL_SERVO;
 rx_sid.format.priority 		= CANB_PRIORITY_CRITICAL;
 rx_sid.format.source 			= CANB_SOURCE_AUTOPILOT;
 rx_sid.format.EXIDE 			= 1;

 C2RX0CON =  0x0000; 	// Receive Status Reset

 // Acceptance Mask Registers
 C2RXM0SID  = 0x1FFD; 	//All of SID must be correct and extended address
 C2RXM0EIDH = 0x0000;	// Accept all data addresses
 C2RXM0EIDL = 0x0000;

//Filter 0 setup to receive controls from the autopilot only

 C2RXF0SID 	= rx_sid.bb;	//CAN2 Receive Acceptance Filter0 SID
 C2RXF0EIDH = 0x0000; 		//CAN2 Receive Acceptace  Filter0 Extended Identifier high byte
 C2RXF0EIDL = 0x0000;		//CAN2 Receive Acceptance Filter0 Extended identifier low byte


 C2RX1CON =  0x0000; 	// Receive Status Reset
};


//-----------------------------------------------------------------------------------------------------------------------
		// Configure recieve buffer 1 for data transfer
//-----------------------------------------------------------------------------------------------------------------------
void config_CAN2_RX_DATA()
{
 // initializing the Receive Buffer 1
 CAN_SID_RX 		rx_sid;
 CAN_RX_SIDFILTER	rx_sid_filter;

 rx_sid.bb = 0;
 rx_sid.format.priority 	= CANB_PRIORITY_LOW;
 rx_sid.format.source 		= CANB_SOURCE_AUTOPILOT;
 rx_sid.format.protocol		= CANB_PROTOCOL_DATA;
 rx_sid.format.EXIDE 		= 1;

 // Acceptance Mask Registers
 rx_sid_filter.bb				= 0;
 rx_sid_filter.format.priority 	= 0;	// Do not filter by priority
 rx_sid_filter.format.protocol 	= 3;	// Filter by protocol
 rx_sid_filter.format.EXIDE		= 1;	// Extended identifier messages only
 rx_sid_filter.format.source	= 0;	// Do not filter for source

 C2RXM1SID  = rx_sid_filter.bb;	//0x1FFD;
 C2RXM1EIDH = 0x0000;
 C2RXM1EIDL = 0x0000;

//Initializing of Acceptance Filters
 C2RXF2SID 	= rx_sid.bb;	//CAN1 Receive Acceptance Filter2 SID
 C2RXF2EIDH = 0x0000; 	//CAN1 Receive Acceptace  Filter2 Extended Identifier high byte
 C2RXF2EIDL = 0x0000;	//CAN1 Receive Acceptance Filter2 Extended identifier low byte

 C2RX1CON =  0x0000; 	// Receive Buffer Status Reset
};


//-----------------------------------------------------------------------------------------------------------------------
		// Configure Transmit buffer 0 for servo control
//-----------------------------------------------------------------------------------------------------------------------
 void config_CAN2_TX(void)
{
 CAN_SID_TX tx_sid;

 tx_sid.bb = 0;
 tx_sid.format.protocol		= CANB_PROTOCOL_SERVO;
 tx_sid.format.priority		= CANB_PRIORITY_CRITICAL;
 tx_sid.format.source 		= CANB_SOURCE_SERVO_IF;
 tx_sid.format.TXIDE 		= 1;

 C2TX0CON = 0x0003; 		// High priority
 C2TX0SID = tx_sid.bb;
 C2TX0EID = 0x0000;         // EID = 0000000000000000000 (0x00000)
 C2TX0DLC = 0x0040;			// 8 bytes to send
};


//-----------------------------------------------------------------------------------------------------------------------
		// Configure Transmit buffer 1 for data transfer from coprocessor
//-----------------------------------------------------------------------------------------------------------------------
void config_CAN2_COPRO_TX()
{
  //Configure Transmit registers
 CAN_SID_TX tx_sid;

 tx_sid.bb = 0;
 tx_sid.format.protocol		= CANB_PROTOCOL_DATA;
 tx_sid.format.priority		= CANB_PRIORITY_LOW;
 tx_sid.format.source 		= CANB_SOURCE_COPROCESSOR;
 tx_sid.format.TXIDE 		= 1;

 C2TX1CON = 0x0002;             // Low Intermediate priority
 C2TX1SID = tx_sid.bb;          // SID = 10101010101 (0x555) 
 C2TX1EID = 0x0000;             // EID = 1110000000100100011 (0x00123)                  
 C2TX1DLC = 0x0040;             // Data length set for each message
};



//-----------------------------------------------------------------------------------------------------------------------
		// CAN ISR
//-----------------------------------------------------------------------------------------------------------------------
void __attribute__((interrupt, no_auto_psv)) _C2Interrupt(void)
{
	interrupt_save_extended_state ;

	switch (C2CTRLbits.ICODE) 
	{
		case 7: 
			C2INTFbits.WAKIF = 0; 
			break;
		case 6:
			// read the message 
		    if(C2RX0CONbits.RXFUL==1)
		    {
				if(C2RX0CONbits.FILHIT0 == 0)
				{
					switch(C2RX0EID)
					{
					case 1:
						ServoInDataBuff[0] = C2RX0B1;
				        ServoInDataBuff[1] = C2RX0B2;
				        ServoInDataBuff[2] = C2RX0B3;
				        ServoInDataBuff[3] = C2RX0B4;
						break;
					case 2:
				        ServoInDataBuff[4] = C2RX0B1; 
				        ServoInDataBuff[5] = C2RX0B2;  	//Move the recieve data from Buffers to InData
				        ServoInDataBuff[6] = C2RX0B3;	
				        ServoInDataBuff[7] = C2RX0B4;
						receive_servo_data();
						break;
					};
				};
		    }
			C2INTFbits.RX0IF = 0;
			C2RX0CONbits.RXFUL = 0;
			break;
		case 5:
		    if(C2RX1CONbits.RXFUL==1)
		    {
				parse_received_data(&CANxRX2ProtoStruct);
			}
			C2INTFbits.RX1IF = 0;
			C2RX1CONbits.RXFUL = 0;
			break;
		case 4: 
			// If this is the end of the first set of servos, transmit the next set
			if(ServoTxMsg == 1)
			{
				C2TX0EID = 0x0002;  	// Second servo data set
	
				C2TX0B1 = ServoOutDataBuff[4];
				C2TX0B2 = ServoOutDataBuff[5];
				C2TX0B3 = ServoOutDataBuff[6];
				C2TX0B4 = ServoOutDataBuff[7];
				ServoTxMsg = 2;
				C2TX0CONbits.TXREQ = 1;
			}
			else
			{
				send_coprocessor_data();
			 	ServoTxMsg = 0;
			};        
		
			C2INTFbits.TX0IF = 0;
			break;
		case 3: 
			C2INTFbits.TX1IF = 0; 
			transmit_data(&CANxTX1ProtoStruct);
			break;
		case 2: 
			C2INTFbits.TX2IF = 0;
			break;
		case 1:
			if(C2INTFbits.EWARN)
			{
				if(C2INTFbits.TXWAR)
				{
					ResetAllCAN2Tx();
					C2INTFbits.TXWAR = 0;
				}

				if(C2INTFbits.RXWAR)
				{
					ResetAllCAN2Rx();
					C2INTFbits.RXWAR = 0;
				}

				if(C2INTFbits.RXEP)
				{
					ResetAllCAN2Rx();
					C2INTFbits.RXEP = 0;
				}

				if(C2INTFbits.TXEP)
				{
					ResetAllCAN2Tx();
					C2INTFbits.TXEP = 0;
				}

				C2INTFbits.EWARN = 0;
			}
			else if(C2INTFbits.TXBO)
			{
				ResetAllCAN2Tx();
				C2INTFbits.TXBO = 0;
			}
			C2INTFbits.ERRIF = 0; // Add error handler code
		break;
		case 0:
			if(C2INTFbits.IVRIF)
			{
				ResetAllCAN2Rx();
				C2INTFbits.IVRIF = 0;
			};
			break;
	}

	ResetAllCAN2Rx();
	interrupt_restore_extended_state ;

	IFS2bits.C2IF = 0; // Clear CAN1 interrupt flag before returning
}



void ResetAllCAN2Tx()
{
	C2INTFbits.TX0IF = 0;
	C2INTFbits.TX1IF = 0;
	C2INTFbits.TX2IF = 0;
};

void ResetAllCAN2Rx()
{
	C2INTFbits.RX0IF = 0;
	C2INTFbits.RX1IF = 0;
	C2RX0CONbits.RXFUL = 0;
	C2RX1CONbits.RXFUL = 0;
	C2INTFbits.RX0OVR = 0;
	C2INTFbits.RX1OVR = 0;
};



//        unsigned RX0IF  :1;
//        unsigned RX1IF  :1;
//        unsigned TX0IF  :1;
//        unsigned TX1IF  :1;
//        unsigned TX2IF  :1;
//        unsigned ERRIF  :1;
//        unsigned WAKIF  :1;
//        unsigned IVRIF  :1;
//        unsigned EWARN  :1;
//        unsigned RXWAR  :1;
//        unsigned TXWAR  :1;
//        unsigned RXEP   :1;
//        unsigned TXEP   :1;
//        unsigned TXBO   :1;
//        unsigned RX1OVR :1;
//        unsigned RX0OVR :1;


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
