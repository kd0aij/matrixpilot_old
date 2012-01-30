#ifndef NV_MEMORY_H
#define NV_MEMORY_H

#include "libUDB_internal.h"

typedef void (*NVMemory_callbackFunc)(boolean);

// Trigger service of nv memory in low priority process
void nv_memory_service_trigger( void );

// Initialise non volatile memory service
void nv_memory_init( void );

boolean udb_nv_memory_read( unsigned char* rdBuffer, unsigned int address, unsigned int rdSize, NVMemory_callbackFunc pCallback);

boolean udb_nv_memory_write( unsigned char* wrBuffer, unsigned int address, unsigned int wrSize, NVMemory_callbackFunc pCallback);

#endif

