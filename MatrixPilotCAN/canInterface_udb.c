// SEE END OF FILE FOR LICENSE TERMS

// This is only for the classic boards.
// The CANbus code will not work for ECAN on dsPIC33

#include "../libUDB/libUDB_internal.h"
#include "../libCAN/CANInterface_internal.h"
#include "../libCAN/CANDataProtocol.h"

#include <string.h>  	// for memcpy

#if(BOARD_GENERATION == GENERATION_CLASSIC)

int udb_pwOut[MAX_OUTPUTS+1] ;	// pulse widths for servo outputs
int udb_pwIn[MAX_INPUTS+1] ;	// pulse widths of radio inputs
int udb_pwTrim[MAX_INPUTS+1] ;	// initial pulse widths for trimming


int failSafePulses = 0 ;
int twentyHertzCounter 	= 0 ;

int outputNum ;						// Which servo data to send next.

void udb_init_canbus_interface(void);


void send_servo_outputs(void);		// Autopilot send servo data to interface
void receive_servo_inputs(void);	// Autopilot recieve servo data from interface
void setupOutputs( void ) ;

inline void ResetAllCAN1Tx(void);
inline void ResetAllCAN1Rx(void);


unsigned int ServoOutBuff[8];
unsigned int ServoInBuff[8];


//---------------------------------------------------------------------

unsigned int RxBytes = 0;

volatile unsigned int TxMsgCount	= 0xFFFF;  	// Counter for which servo tx message is being done
volatile unsigned int TxDataCount	= 0x0000;  	// Counter for data send

void init_CAN1(void);
void config_CAN1_RX_SERVO(void);
void config_CAN1_RX_COPRO(void);
void config_CAN1_TX_SERVO(void);
void config_CAN1_TX_DATA(void);

// Overide of radioIn funciton.
void udb_init_capture(void)
{
};


void udb_init_pwm( void )	// initialize the PWM
{
	PDC1 = PDC2 = PDC3 = 0 ;
	
	int i;
	for (i=0; i <= NUM_OUTPUTS; i++)
		udb_pwOut[i] = 0;
	
#if (NORADIO == 1)
	udb_flags._.radio_on = 1 ;
#endif
	
	TRISE = 0b1111111111000000 ;
	PTPER = 25000 ;	// 25 millisecond period at 16 Mz clock, prescale = 4	
	_PTCKPS = 1;	// prescaler = 4

	_PMOD1 = 1 ;	// independent PWM mode
	_PMOD2 = 1 ;
	_PMOD3 = 1 ;
	_PEN1L = 0 ; 	// low pins used as digital I/O
	_PEN2L = 0 ;
	_PEN3L = 0 ;
	
	_PTEN = 1; 		// turn on the PWM 
	_PWMIF = 0 ; 	// clear the PWM interrupt
	_PWMIP = 3 ;    // priority 3

	udb_init_canbus_interface();

	return ;
}


void udb_init_canbus_interface(void)
{
	initTelemetryManager();
	init_CAN1();
	config_CAN1_RX_SERVO();
	config_CAN1_RX_COPRO();
	config_CAN1_TX_SERVO();
	config_CAN1_TX_DATA();

 //Change to Operation Mode from Configuration Mode
 C1CTRLbits.REQOP = 0;
 while(C1CTRLbits.OPMODE != 0);//Wait for CAN1 mode change from Configuration Mode to normal mode 

 //Enable transmission
 TxMsgCount = 0;	// Clear the servo Tx message counter to indicate that CAN is ready

};



//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
				//init CAN1
//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
void init_CAN1(void)
{


	TRISFbits.TRISF1 = 0;				// CAN 1 TX set to output	
	TRISFbits.TRISF0 = 1;				// CAN 1 RX set to input

//--------------------------------------------------------------------------------------------------------------------
				//Initialization of CAN1 Module and Enabling of CAN1 Interrupts
//--------------------------------------------------------------------------------------------------------------------

 
 C1CTRLbits.CANCKS = 0;			// Select the CAN Master Clock . It is equal to 4Fcy here. 
								// (Fcy=4MHz)

 C1CFG1bits.SJW=00;				//Synchronized jump width time is 1 x TQ when SJW is equal to 00
 
 C1CFG1bits.BRP = BRP_VAL;		//((FCY/(2*NTQ*BITRATE))-1) 	

 C1CFG2 = CAN_TIMING_CONFIG2;	// See canbus config for settings

///Interrupt Section of CAN Peripheral

 C1INTF = 0;					//Reset all The CAN Interrupts 
 IFS1bits.C1IF = 0;  			//Reset the Interrupt Flag status register
 C1INTE = 0x000F;               //Enable interrupt sources
// C1INTE = 0x00FF;               //Enable interrupt sources
 IEC1bits.C1IE = 1;				//Enable the CAN1 Interrupt
};




void udb_set_action_state(boolean newValue)
{
	_LATE4 = newValue ;
}


void __attribute__((__interrupt__,__no_auto_psv__)) _PWMInterrupt(void)
{
	// interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	//	Executes whatever needs to be done every 25 milliseconds, using the PWM clock.
	//	This is a good place to run the A/D digital filters and compute pulse widths for servos.
	//	Also, this is used to wait a few pulses before recording input DC offsets.

#if ( NORADIO == 0 )
	twentyHertzCounter++ ;
	if ( twentyHertzCounter >= 2 )
	{
		if ( failSafePulses == 0 )
		{
			udb_flags._.radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
		else if ( failSafePulses >= 2 )
		{
			udb_flags._.radio_on = 1 ;
			LED_GREEN = LED_ON ;
		}
		twentyHertzCounter = 0 ;
		failSafePulses = 0 ;
	}
#endif
	
	udb_servo_callback_prepare_outputs() ;
	setupOutputs() ;
	
	_PWMIF = 0 ; /* clear the interrupt */
	
	// interrupt_restore_extended_state ;
	return ;
}



//-----------------------------------------------------------------------------------------------------------------------
		// Send servo output control data to remote servo interface(s)
//-----------------------------------------------------------------------------------------------------------------------
void send_servo_outputs(void)
{
	if(C1TX0CONbits.TXREQ == 1)		// If already transmitting, dont try again.
	{
		return;
	}

		TxMsgCount = 1;
	
		C1TX0EID = 0x0001;				// First servo address
		C1TX0B1 = ServoOutBuff[0];
		C1TX0B2 = ServoOutBuff[1];
		C1TX0B3 = ServoOutBuff[2];
		C1TX0B4 = ServoOutBuff[3];
		C1TX0CONbits.TXREQ = 1;
};


//-----------------------------------------------------------------------------------------------------------------------
		// Broadcast flight data on CANbus
//-----------------------------------------------------------------------------------------------------------------------
void send_flight_data()
{

//	requestTelemetrySend(0);	// Fast flight data is the first, highest priority queue

	if(C1TX2CONbits.TXREQ == 1)	// If already transmitting data then return
	{
		return;
	}
		
	if(requestAutoTelemetrySend())
			start_CAN_data_send(&CANxTX1ProtoStruct);
};


//-----------------------------------------------------------------------------------------------------------------------
		// Configure Receive buffer 0 and filter 1 for servo control
//-----------------------------------------------------------------------------------------------------------------------
void config_CAN1_RX_SERVO(void)
{
 // initializing the Receive Buffer 0
 CAN_SID_RX rx_sid;

 rx_sid.bb = 0;
 rx_sid.format.priority 	= CANB_PRIORITY_CRITICAL;
 rx_sid.format.source 		= CANB_SOURCE_SERVO_IF;
 rx_sid.format.protocol		= CANB_PROTOCOL_SERVO;
 rx_sid.format.EXIDE 		= 1;

 C1RX0CON =  0x0000; 	// Receive Buffer Status Reset
 
 // Acceptance Mask Registers
 C1RXM0SID  = 0x1FFD; //All of SID must be correct and extended address
 C1RXM0EIDH = 0x0000; 
 C1RXM0EIDL = 0x0000;

//Initializing of Acceptance Filters
 C1RXF0SID 	= rx_sid.bb;	//CAN1 Receive Acceptance Filter0 SID
 C1RXF0EIDH = 0x0000; 	//CAN1 Receive Acceptace  Filter0 Extended Identifier high byte
 C1RXF0EIDL = 0x0000;	//CAN1 Receive Acceptance Filter0 Extended identifier low byte
};


//-----------------------------------------------------------------------------------------------------------------------
		// Configure Receive buffer 1 for data and filter 1 for servo control
//-----------------------------------------------------------------------------------------------------------------------
void config_CAN1_RX_COPRO()
{
 // initializing the Receive Buffer 1
 CAN_SID_RX 		rx_sid;
 CAN_RX_SIDFILTER	rx_sid_filter;

 rx_sid.bb = 0;
 rx_sid.format.priority 	= CANB_PRIORITY_LOW;
 rx_sid.format.source 		= CANB_SOURCE_COPROCESSOR;
 rx_sid.format.protocol		= CANB_PROTOCOL_DATA;
 rx_sid.format.EXIDE 		= 1;

 // Acceptance Mask Registers
 rx_sid_filter.bb				= 0;
 rx_sid_filter.format.priority 	= 0;	// Do not filter by priority
 rx_sid_filter.format.protocol 	= 3;	// Filter by protocol
 rx_sid_filter.format.EXIDE		= 1;	// Extended identifier messages only
 rx_sid_filter.format.source	= 0;	// Do not filter for source

 C1RXM1SID  = rx_sid_filter.bb;	//0x1FFD;
 C1RXM1EIDH = 0x0000;
 C1RXM1EIDL = 0x0000;

//Initializing of Acceptance Filters
 C1RXF2SID 	= rx_sid.bb;	//CAN1 Receive Acceptance Filter2 SID
 C1RXF2EIDH = 0x0000; 	//CAN1 Receive Acceptace  Filter2 Extended Identifier high byte
 C1RXF2EIDL = 0x0000;	//CAN1 Receive Acceptance Filter2 Extended identifier low byte

 C1RX1CON =  0x0000; 	// Receive Buffer Status Reset
};


//-----------------------------------------------------------------------------------------------------------------------
		// Configure Transmit Register 0 for servo control data transmission
//-----------------------------------------------------------------------------------------------------------------------
void config_CAN1_TX_SERVO(void)
{
 CAN_SID_TX tx_sid;

 tx_sid.bb = 0;
 tx_sid.format.protocol 	= CANB_PROTOCOL_SERVO;
 tx_sid.format.source 		= CANB_SOURCE_AUTOPILOT;
 tx_sid.format.priority		= CANB_PRIORITY_CRITICAL;
 tx_sid.format.TXIDE 		= 1;
  
 C1TX0CON = 0x0003;     	// High priority
 C1TX0SID = tx_sid.bb;		// SID
 C1TX0EID = 0x0001;     	// EID
 C1TX0DLC = 0x040; 			// 8 byte
};


//-----------------------------------------------------------------------------------------------------------------------
		// Configure Transmit Register 0 for flight data transmission
//-----------------------------------------------------------------------------------------------------------------------
void config_CAN1_TX_DATA(void)
{
 CAN_SID_TX tx_sid;

 tx_sid.bb = 0;
 tx_sid.format.protocol 	= CANB_PROTOCOL_DATA;
 tx_sid.format.source 		= CANB_SOURCE_AUTOPILOT;
 tx_sid.format.priority		= CANB_PRIORITY_LOW;
 tx_sid.format.TXIDE 		= 1;

 C1TX1CON = 0x0001;             // Low Intermediate priority
 C1TX1SID = tx_sid.bb;          // SID
 C1TX1EID = 0x0000;             // EID                   
 C1TX1DLC = 0x0040;				// 8 bytes
};



//-----------------------------------------------------------------------------------------------------------------------
		// CAN ISR
//-----------------------------------------------------------------------------------------------------------------------
void __attribute__((interrupt, no_auto_psv)) _C1Interrupt(void)
{
	interrupt_save_extended_state ;

	switch (C1CTRLbits.ICODE) 
	{
		case 7: 
			C1INTFbits.WAKIF = 0; 
			break;
		case 6:
			if(C1RX0CONbits.FILHIT0 == 0)
			{
				switch(C1RX0EID)
				{
				case 1:
			        ServoInBuff[0] = C1RX0B1; 
			        ServoInBuff[1] = C1RX0B2;  	//Move the recieve data from Buffers to InData
			        ServoInBuff[2] = C1RX0B3;	
			        ServoInBuff[3] = C1RX0B4;
					break;
				case 2:
			        ServoInBuff[4] = C1RX0B1; 
			        ServoInBuff[5] = C1RX0B2;  	//Move the recieve data from Buffers to InData
			        ServoInBuff[6] = C1RX0B3;	
			        ServoInBuff[7] = C1RX0B4;
					receive_servo_inputs();	
					break;
				};
			};
			C1INTFbits.RX0IF = 0;
			C1RX0CONbits.RXFUL = 0;
			break;
		case 5:
		    if(C1RX1CONbits.RXFUL==1)
		    {
				parse_received_data(&CANxRX2ProtoStruct);
			}
			C1INTFbits.RX1IF = 0; // Add code to read buffer 1
			C1RX1CONbits.RXFUL = 0;
			break;
		case 4:
			C1INTFbits.TX0IF = 0;

			if(TxMsgCount == 1)
			{
				C1TX0EID = 0x0002;	// Second servo address
				C1TX0B1 = ServoOutBuff[4];
				C1TX0B2 = ServoOutBuff[5];
				C1TX0B3 = ServoOutBuff[6];
				C1TX0B4 = ServoOutBuff[7];
				TxMsgCount++;

				C1TX0CONbits.TXREQ = 1;
			}
			else
			{
				send_flight_data();	// Send servo rate flight data
				TxMsgCount = 0;
			};
			break;
		case 3: 
			C1INTFbits.TX1IF = 0; 
			transmit_data(&CANxTX1ProtoStruct);
			break;
		case 2: 
			C1INTFbits.TX2IF = 0;
			break;
		case 1: 
			if(C1INTFbits.EWARN)
			{
				if(C1INTFbits.TXWAR)
				{
					ResetAllCAN1Tx();
					C1INTFbits.TXWAR = 0;
				}

				if(C1INTFbits.RXWAR)
				{
					ResetAllCAN1Rx();
					C1INTFbits.RXWAR = 0;
				}

				if(C1INTFbits.RXEP)
				{
					ResetAllCAN1Rx();
					C1INTFbits.RXEP = 0;
				}

				if(C1INTFbits.TXEP)
				{
					ResetAllCAN1Tx();
					C1INTFbits.TXEP = 0;
				}

				C1INTFbits.EWARN = 0;
			}
			else if(C1INTFbits.TXBO)
			{
				ResetAllCAN1Tx();
				C1INTFbits.TXBO = 0;
			}

			C1INTFbits.ERRIF = 0;

			break;
		case 0:
			if(C1INTFbits.IVRIF)
			{
				ResetAllCAN1Rx();
				C1INTFbits.IVRIF = 0;
			};


			break;
	}

	ResetAllCAN1Rx();
	interrupt_restore_extended_state ;

	IFS1bits.C1IF = 0; // Clear CAN1 interrupt flag before returning
};

inline void ResetAllCAN1Tx()
{
	C1INTFbits.TX0IF = 0;
	C1INTFbits.TX1IF = 0;
	C1INTFbits.TX2IF = 0;
};


inline void ResetAllCAN1Rx()
{
	C1INTFbits.RX0IF = 0;
	C1INTFbits.RX1IF = 0;
	C1RX0CONbits.RXFUL = 0;
	C1RX1CONbits.RXFUL = 0;
	C1INTFbits.RX0OVR = 0;
	C1INTFbits.RX1OVR = 0;
};


// Autopilot recieves, reformats and acts on servo data from CAN interface
void receive_servo_inputs()
{
    int index;
	int offset_index;
	for(index = 0; index < 8; index++)
	{
		offset_index = index+1;		// correct for array offsets

		if( (ServoInBuff[index] & 0x8000) != 0)
		{
			udb_pwIn[offset_index] = ServoInBuff[index] & 0x7fff;
			if(offset_index == FAILSAFE_INPUT_CHANNEL)
			{
				if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
				{
					failSafePulses++ ;
				}
				else
				{
					failSafePulses = 0 ;
					udb_flags._.radio_on = 0;
				}

			};
		};
	};
};


// Move SetupOutputs here for CANbus overide.
void setupOutputs( void )
{
	PDC1 = udb_pwOut[1] ;
	PDC2 = udb_pwOut[2] ;
	PDC3 = udb_pwOut[3] ;

	memcpy(ServoOutBuff, &udb_pwOut[1], sizeof(ServoOutBuff));
	send_servo_outputs();
}

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
