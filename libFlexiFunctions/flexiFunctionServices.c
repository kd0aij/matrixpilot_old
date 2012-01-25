#include "flexiFunctionServices.h"
#include "../libUDB/events.h"
// buffer for communications or memory store/restore
;

enum
{
	FF_SERVICES_NOT_STARTED,
	FF_SERVICES_WAITING,
	FF_SERVICES_READ_EEPROM,
	FF_SERVICES_WRITE_EEPROM,
	FF_SERVICES_BUFFER_COMMITTED,
} FF_SERCICES_STATE;


unsigned int flexiFunctionServiceHandle = INVALID_HANDLE;

unsigned int flexiFunctionState = FF_SERVICES_NOT_STARTED;

unsigned int flexifunction_commited_index 	= INVALID_HANDLE;
unsigned int flexifunction_commited_compID 	= INVALID_HANDLE;


// flexifunction service routine
void flexiFunctionService(void)
{
	switch(flexiFunctionState)
	{
	case FF_SERVICES_NOT_STARTED:
		break;
	case FF_SERVICES_BUFFER_COMMITTED:
		
		break;
	}
}

// Initialise the flexifunction service
void flexiFunctionServiceInit(void)
{
	flexiFunctionServiceHandle = register_event(&flexiFunctionService);
	flexiFunctionState = FF_SERVICES_WAITING;
}

// Trigger the flexifunction service to run
void flexiFunctionServiceTrigger(void)
{
	trigger_event(flexiFunctionServiceHandle);
}


// Write a function to the buffer
boolean flexiFunction_write_buffer_function(functionSetting* pFuncSetting, unsigned int index)
{
	if(flexiFunctionState != FF_SERVICES_WAITING) return false;
	
	

	return true;
}

void flexiFunction_commit_buffer(unsigned int checksum, unsigned int compID)
{

}
