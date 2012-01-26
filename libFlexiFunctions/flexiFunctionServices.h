#ifndef FLEXIFUNCTION_SERVICES
#define FLEXIFUNCTION_SERVICES

#include "flexiFunctionTypes.h"
#include "../libUDB/events.h"
#include "../libUDB/libUDB_internal.h"
#include "flexifunction_options.h"
#include "../MAVlink/include/mavlink_types.h"


typedef struct tagNVMEM_FLEXIFUNCTION_DATA
{
	unsigned int				flexiFunctionsUsed;
	functionSetting 			flexiFunction_data[FLEXIFUNCTION_MAX_FUNCS];
} NVMEM_FLEXIFUNCTION_DATA;

// Initialise the flexifunction low priority service
void flexiFunctionServiceInit(void);

// Trigger the flexifunction low priority service to run
void flexiFunctionServiceTrigger(void);

void flexiFunctionTransmitService(mavlink_channel_t chan);

// Parse flexifunction specific messages
void flexiFunctionReceiveParser(mavlink_message_t* msg);

// Called by flexifunction loop to test for a new set of functions available
void flexiFunction_commit_buffer_check( void );

// Read running flexifunctions to the buffer with sizes
void flexiFunction_read_to_buffer(void);

// Read function settings from nv memory to buffer
void flexiFunction_read_nv_memory(void);

// Commit buffer to nv memory
void flexiFunction_write_nv_memory(void);

// Load function settings from nv memory, test checksum and then commit
void flexiFunction_load_nv_memory(void);

#endif 	//FLEXIFUNCTION_SERVICES

