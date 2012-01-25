#ifndef FLEXIFUNCTION_SERVICES
#define FLEXIFUNCTION_SERVICES

#include "flexiFunctionTypes.h"
#include "../libUDB/events.h"
#include "../libUDB/libUDB_internal.h"
#include "flexifunction_options.h"

typedef struct tagNVMEM_FLEXIFUNCTION_DATA
{
	flexiFunctionComponentData;
	functionSetting flexiFunction_buffer[MAX_BUFFER_FUNCS];
} NVMEM_FLEXIFUNCTION_DATA;

// Initialise the flexifunction service
void flexiFunctionServiceInit(void);

// Trigger the flexifunction service to run
void flexiFunctionServiceTrigger(void);

// Write a function to the buffer
boolean flexiFunction_write_buffer_function(functionSetting* pFuncSetting, unsigned int index); 

// Read a function from the buffer
void flexiFunction_read_buffer_function(functionSetting* pFuncSetting, unsigned int index); 

// Write statistics to the buffer
void flexifunction_write_statistics(unsigned int register_count, unsigned int function_count);

// Read statistics from the buffer
void flexifunction_read_statistics(unsigned int* register_count, unsigned int* function_count);

// Commit the buffer to running flexifunctions
void flexiFunction_commit_buffer(unsigned int checksum, unsigned int compID);

// Read running flexifunctions to the buffer with sizes
void flexiFunction_read_to_buffer(unsigned int compID, unsigned int* register_count, unsigned int* function_count);

void flexiFunction_read_nv_memory(void);

// Commit buffer to nv memory
void flexiFunction_write_nv_memory(void);

#endif 	//FLEXIFUNCTION_SERVICES

