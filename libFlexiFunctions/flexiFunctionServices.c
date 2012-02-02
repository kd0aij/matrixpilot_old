// Flexifunction services.  Runs all required states for handling both
// transfers from nv memory and transfers from mavlink

// There are two state machines running but the service can only
// have one state at once.  If memory transfers are in progress, mavlink
// can't have access.

#include <string.h>
#include "defines.h"
#include "../libDCM/libDCM_internal.h" // Needed for access to internal DCM value

#include "../libUDB/events.h"
#include "flexifunction_options.h"
#include "flexiFunctionServices.h"

// Include MAVlink library for checksums
#include "../MAVlink/include/mavlink_types.h"
#include "../MAVlink/include/checksum.h"


void flexifunction_commit_buffer_crc( void );

inline void flexiFunction_NAK( void ); 		// Called to flag a negative acknowlege
inline void flexiFunction_ACK( void ); 		// Called to flag a positive acknowlege


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
	if(index >=  FLEXIFUNCTION_MAX_FUNCS)
	{
		flexifunction_ref_result = 0;
		flexiFunctionState = FLEXIFUNCTION_BUFFER_FUNCTION_ACKNOWLEDGE;
		return;
	}	

	memcpy(&flexiFunctionBuffer.flexiFunction_data[index], pFuncSetting, sizeof(functionSetting));
			
	flexifunction_ref_result = 1;
	flexiFunctionState = FLEXIFUNCTION_BUFFER_FUNCTION_ACKNOWLEDGE;
	return;
}


// Write a functions count to the buffer
void flexiFunction_write_functions_count(unsigned int funcCount)
{
	if(funcCount >= FLEXIFUNCTION_MAX_FUNCS)
	{
		flexifunction_ref_result = 0;
		flexiFunctionState = FLEXIFUNCTION_SIZES_ACKNOWLEDGE;
		return;
	}
	
	flexiFunctionBuffer.flexiFunctionsUsed = funcCount;
	flexifunction_ref_result = 1;
	flexiFunctionState = FLEXIFUNCTION_SIZES_ACKNOWLEDGE;
	return;
}

// Get functions count from buffer
unsigned int flexiFunction_get_functions_count( void )
{
	return flexiFunctionBuffer.flexiFunctionsUsed;
}


void flexiFunction_commit_buffer()
{
	if(flexiFunctionState != FLEXIFUNCTION_WAITING)	
	{
		flexifunction_ref_result = 0;
		flexiFunctionState = FLEXIFUNCTION_COMMAND_ACKNOWLEDGE;
		return;
	}

	if(flexiFunctionBuffer.flexiFunctionsUsed > FLEXIFUNCTION_MAX_REGS)
	{
		flexiFunction_NAK();
		return;
	}


	// Next step is to calculate checksum
	flexiFunctionState = FLEXIFUNCTION_COMMIT_BUFFER;
}

// A place to do checksums if it is ever implemented
void flexifunction_commit_buffer_crc( void )
{
//	if(flexifunction_ref_checksum == crc_calculate( (uint8_t*) &flexiFunctionBuffer, sizeof(flexiFunctionBuffer) ) )
	flexiFunctionState = FLEXIFUNCTION_COMMITTING_BUFFER;
//	else
//		flexiFunction_NAK();
}


// Called by flexifunction loop to test for a new set of functions available
void flexiFunction_commit_buffer_check()
{
	if(flexiFunctionState != FLEXIFUNCTION_COMMITTING_BUFFER) return;

	unsigned int index;
	functionSetting* pTarget;
	functionSetting* pSource;

	for( index = 0; index < flexiFunctionBuffer.flexiFunctionsUsed; index++)
	{
		pTarget = &flexiFunction_data[index];
		pSource = &flexiFunctionBuffer.flexiFunction_data[index];

		memcpy((unsigned char*) pTarget, (unsigned char*) pSource, sizeof(functionSetting));
	}

	flexiFunctionsUsed = flexiFunctionBuffer.flexiFunctionsUsed;

	flexifunction_ref_command = FLEXIFUNCTION_COMMAND_COMMIT_BUFFER;

	flexiFunction_ACK();
}

// Called to flag a negative acknowlege
inline void flexiFunction_NAK( void )
{
	flexifunction_ref_result = 0;
	flexiFunctionState = FLEXIFUNCTION_COMMAND_ACKNOWLEDGE;
}

// Called to flag a positive acknowlege
inline void flexiFunction_ACK( void )
{
	flexifunction_ref_result = 1;
	flexiFunctionState = FLEXIFUNCTION_COMMAND_ACKNOWLEDGE;
}
