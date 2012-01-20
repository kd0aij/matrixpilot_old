#ifndef NV_MEMORY_H
#define NV_MEMORY_H

#include "libUDB_internal.h"

typedef void (*NVMemory_callbackFunc)(boolean);

void udb_nv_memory_init( void );

void udb_nv_memory_service( void );

boolean udb_nv_memory_read( unsigned char* rdBuffer, unsigned int address, unsigned int rdSize, NVMemory_callbackFunc pCallback);

boolean udb_nv_memory_write( unsigned char* wrBuffer, unsigned int address, unsigned int wrSize, NVMemory_callbackFunc pCallback);

#endif

