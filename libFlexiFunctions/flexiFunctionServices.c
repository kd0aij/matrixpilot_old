// Flexifunction services.  Runs all required states for handling both
// transfers from nv memory and transfers from mavlink

// There are two state machines running but the service can only
// have one state at once.  If memory transfers are in progress, mavlink
// can't have access.


#include "../libUDB/events.h"
#include "flexifunction_options.h"
// buffer for communications or memory store/restore

// Include MAVlink
//#include "../MAVLink/include/matrixpilot/version.h"
#define 	MAVLINK_MAX_PAYLOAD_LEN 	MAVLINK_MAX_DIALECT_PAYLOAD_SIZE
#include "../MAVLink/include/inttypes.h"
//   #include "../MAVlink/include/mavlink_types.h"
//#include "../MAVLink/include/matrixpilot_mavlink_bridge_header.h"
#include "../MAVlink/include/matrixpilot/mavlink.h"

// Include MAVlink library for checksums
#include "../MAVlink/include/checksum.h"

#include "flexiFunctionServices.h"

void flexifunction_commit_buffer_crc( void );

inline void flexiFunction_NAK( void ); 		// Called to flag a negative acknowlege
inline void flexiFunction_ACK( void ); 		// Called to flag a positive acknowlege


enum FLEXIFUNCTION_SERVICES_STATUS
{
	FLEXIFUNCTION_NOT_STARTED,
	FLEXIFUNCTION_WAITING,
	FLEXIFUNCTION_SEND_BUFFER_SPECIFIC,
	FLEXIFUNCTION_SEND_BUFFER_ALL,
	FLEXIFUNCTION_SENDING_BUFFER_ALL,
	FLEXIFUNCTION_SEND_STATISTICS,
	FLEXIFUNCTION_READ_EEPROM,
	FLEXIFUNCTION_READING_EEPROM,
	FLEXIFUNCTION_WRITE_EEPROM,
	FLEXIFUNCTION_WRITING_EEPROM,
	FLEXIFUNCTION_COMMIT_BUFFER,		// Request to commit buffer from mavlink
	FLEXIFUNCTION_COMMITTING_BUFFER,	// Checksum done and waiting for actual commit
	FLEXIFUNCTION_COMMITTED_BUFFER,		// Commit done, send acknowledge
	FLEXIFUNCTION_COMMAND_ACKNOWLEGE,
};


// Buffer of all flexifunction data including used register and funciton count
NVMEM_FLEXIFUNCTION_DATA flexiFunctionBuffer;


unsigned int flexiFunctionServiceHandle = INVALID_HANDLE;

unsigned int flexiFunctionState = FLEXIFUNCTION_NOT_STARTED;

unsigned int flexifunction_ref_index 	= 0;
unsigned int flexifunction_ref_checksum	= 0;
unsigned int flexifunction_ref_compID	= 0;
unsigned int flexifunction_ref_command	= 0;
unsigned int flexifunction_ref_result	= 0;
unsigned int flexifunction_ref_sysID	= 0;

// flexifunction service routine for low priority process
void flexiFunctionService(void)
{
	switch(flexiFunctionState)
	{
	case FLEXIFUNCTION_READ_EEPROM:
		break;
	case FLEXIFUNCTION_COMMIT_BUFFER:
		flexifunction_commit_buffer_crc();
		break;
	case FLEXIFUNCTION_COMMITTED_BUFFER:
		break;
	}
}

// Initialise the flexifunction service
void flexiFunctionServiceInit(void)
{
	flexiFunctionServiceHandle = register_event(&flexiFunctionService);
	flexiFunctionState = FLEXIFUNCTION_WAITING;
}

// Trigger the flexifunction service to run
void flexiFunctionServiceTrigger(void)
{
	trigger_event(flexiFunctionServiceHandle);
}



// Send a specific buffer to mavlink
boolean flexifunction_send_buffer_specific(unsigned int index)
{
	if(flexiFunctionState != FLEXIFUNCTION_WAITING) return false;

	if(index >=  FLEXIFUNCTION_MAX_FUNCS) return false;

	flexifunction_ref_index = index;
	flexiFunctionState = FLEXIFUNCTION_SEND_BUFFER_SPECIFIC;
	
	return true;
}


// Send all buffers to mavlink
void flexifunction_send_buffer_all(unsigned int index)
{
//	flexifunction_ref_command	= MAVLINK_MSG_ID_FLEXIFUNCTION_SEND_ALL;
//	flexifunction_ref_compID	= compID;
//	flexifunction_ref_sysID		= sysID;

	if(flexiFunctionState != FLEXIFUNCTION_WAITING)
	{
		flexiFunction_NAK();
		return;
	}	

	if(index >=  FLEXIFUNCTION_MAX_FUNCS)
	{
		flexiFunction_NAK();
		return;
	}	

	flexifunction_ref_index = index;
	flexiFunctionState = FLEXIFUNCTION_SEND_BUFFER_SPECIFIC;
	
	return;
}


// Calling during the sending of all buffer items
void flexifunction_sending_buffer_all()
{
	if(flexiFunctionState != FLEXIFUNCTION_SENDING_BUFFER_ALL)
	{
		flexiFunction_NAK();
		return;
	}

	// If all of the funcitons have been sent, stop and send acknowledge command
	if(flexifunction_ref_index >=  flexiFunctionBuffer.flexiFunctionsUsed) 
	{
		flexiFunction_ACK();
		return;
	}

	

	flexifunction_ref_index++;
	
	return;
}

// Write a function to the buffer
void flexiFunction_write_buffer_function(functionSetting* pFuncSetting, unsigned int index)
{
//	flexifunction_ref_command	= MAVLINK_MSG_ID_FLEXIFUNCTION_COMMIT_BUFFER;
//	flexifunction_ref_compID	= compID;
//	flexifunction_ref_sysID		= sysID;

	if(flexiFunctionState != FLEXIFUNCTION_WAITING)
	{
		flexiFunction_NAK();
		return;
	}
	
	// Write the buffer function
	
	flexiFunction_ACK();
	return;
}

void flexiFunction_commit_buffer(unsigned int checksum)
{
	if(flexiFunctionState != FLEXIFUNCTION_WAITING)	
	{
		flexifunction_ref_result = 0;
		flexiFunctionState = FLEXIFUNCTION_COMMAND_ACKNOWLEGE;
		return;
	}

	flexifunction_ref_command	= MAVLINK_MSG_ID_FLEXIFUNCTION_COMMIT_BUFFER;
	flexifunction_ref_checksum	= checksum;
//	flexifunction_ref_compID	= compID;
//	flexifunction_ref_sysID		= sysID;

	if(flexiFunctionBuffer.flexiFunctionsUsed > FLEXIFUNCTION_MAX_REGS)
	{
		flexiFunction_NAK();
		return;
	}


	// Next step is to calculate checksum
	flexiFunctionState = FLEXIFUNCTION_COMMIT_BUFFER;
}


void flexifunction_commit_buffer_crc( void )
{
	if(flexifunction_ref_checksum == crc_calculate( (uint8_t*) &flexiFunctionBuffer, sizeof(flexiFunctionBuffer) ) )
		flexiFunctionState = FLEXIFUNCTION_COMMITTING_BUFFER;
	else
		flexiFunction_NAK();
}


// Called by flexifunction loop to test for a new set of functions available
void flexiFunction_commit_buffer_check()
{
	if(flexiFunctionState != FLEXIFUNCTION_COMMITTING_BUFFER) return;
/*
	pcompRef->pComponentData->numberRegs = flexiFunctionBuffer.componentData.numberRegs;
	pcompRef->pComponentData->numberFuncs = flexiFunctionBuffer.componentData.numberFuncs;
	unsigned int byteSize = flexiFunctionBuffer.componentData.numberFuncs * pcompRef->functionSize;
	memcpy(pcompRef->pFunctionData,  flexiFunctionBuffer.flexiFunction_data, byteSize );
*/
	flexiFunction_ACK();
}

// Called to flag a negative acknowlege
inline void flexiFunction_NAK( void )
{
	flexifunction_ref_result = 0;
	flexiFunctionState = FLEXIFUNCTION_COMMAND_ACKNOWLEGE;
}

// Called to flag a positive acknowlege
inline void flexiFunction_ACK( void )
{
	flexifunction_ref_result = 1;
	flexiFunctionState = FLEXIFUNCTION_COMMAND_ACKNOWLEGE;
}


// Parse flexifunction specific messages
void flexiFunctionReceiveParser(mavlink_message_t* msg)
{
	switch (msg->msgid)
	{
	    case MAVLINK_MSG_ID_FLEXIFUNCTION_SET:
	    {
			// Do nothing with this funciton since it is obsolete
			// Must keep function defined to activate flexifunction mavlink libraries
		}
		break;
	    case MAVLINK_MSG_ID_FLEXIFUNCTION_SET_BUFFER_FUNCTION:
	    {
	        // decode
			//send_text((unsigned char*)"Param Set\r\n");
	        mavlink_flexifunction_set_buffer_function_t packet;
	        mavlink_msg_flexifunction_set_buffer_function_decode(msg, &packet);

	        if (mavlink_check_target(packet.target_system,packet.target_component)) break ;

			functionSetting fSetting;
	
			fSetting.functionType = packet.function_type;
			fSetting.setValue = packet.Action;
			fSetting.dest = packet.out_index;
			if(packet.settings_data[0] != 's') return;
			memcpy(&fSetting.data, &packet.settings_data[1], sizeof(functionData));

			flexiFunction_write_buffer_function(&fSetting, packet.func_index);
		}
		break;
	} // end case
}


void flexiFunctionTransmitService(mavlink_channel_t chan)
{
}
