// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


//******************************************************************/
// DATA STORAGE
// A lightweight file system that allows data versioning
// Does checksums on data structures or data arrays
// Has a basic directory/FAT table describing data areas
// Data areas do not have names, only the handles defined below
// 
// Uses X.25 checksum from MAVink libraries
//
//

#include "data_storage.h"
#include "nv_memory.h"
#include "events.h"
#include <string.h>

#include "../MAVlink/include/inttypes.h"
#include "../MAVlink/include/checksum.h"

enum
{
	DATA_STORAGE_STATUS_START,
	DATA_STORAGE_STATUS_INIT,
	DATA_STORAGE_CHECK_TABLE,
	DATA_STORAGE_FORMAT_TABLE,
	DATA_STORAGE_STATUS_WAITING,
	DATA_STORAGE_READING,
	DATA_STORAGE_WRITING,
	DATA_STORAGE_READ_COMPLETE,
	DATA_STORAGE_WRITE_COMPLETE,
	DATA_STORAGE_STATUS_FAILED,
	DATA_STORAGE_AREA_CREATE,
} DATA_STORAGE_STATUS;

unsigned int data_storage_status = DATA_STORAGE_STATUS_START;

// store the data storage table
boolean data_storage_store_table(void);

// Check the integrity of the data storage table
boolean data_storage_check_table(void);

// Format the data storage table
boolean data_storage_format_table(void);

// create a new data storage area
boolean storage_create_area(unsigned int data_handle, unsigned int size);

// Callbacks
// The callbacks normally set the status so that the background service routine does the work.
void data_storage_callback(boolean success);			// Callback from non volatile memory driver
void data_storage_format_callback(boolean success);		// format write is completed
void data_storage_init_read_callback(boolean success);	// initialisation read of storage table



// A constant preamble used to determine the start of a data block
// This also allows the data to be found if the FAT is broken
const unsigned char data_storage_preamble[] = {0xAA, 0x5A, 0xA5, 0x55};

// A constant preamble used to determine the start of the data storage table
const unsigned char table_storage_preamble[] = {0x55, 0xA5, 0x5A, 0xAA};

// Structure in ram of complete data directory including checksum.
DATA_STORAGE_TABLE data_storage_table;

// Callers data.  Used on initialisation of a user area.
unsigned char* pdata_storage_data = NULL;
unsigned int data_storage_type = DATA_STORAGE_NULL;
unsigned int data_storage_size = 0;

unsigned int data_storage_handle = INVALID_HANDLE;


// Initialise the storage
// If read has failed keep re-trying until the nv memory is ready.
void data_storage_service(void)
{
	switch(data_storage_status)
	{
	case DATA_STORAGE_STATUS_START:
		data_storage_table.table_preamble[0] = 0x00;		// Make sure memory contents are invalid before reading
		data_storage_table.table_checksum = 0x0000;

		// Loading the data storage table.  Set status as running initialisation.
		// If NV memory not ready, immediate return.
		if(udb_nv_memory_read( (unsigned char*) &data_storage_table, 0, sizeof(data_storage_table), &data_storage_init_read_callback) == false) return;
		data_storage_status = DATA_STORAGE_STATUS_INIT;
		break;
	case DATA_STORAGE_CHECK_TABLE:
		if(data_storage_check_table() == false)
		{
			// If table check fails then format the table
			if(!data_storage_format_table())
				data_storage_status = DATA_STORAGE_STATUS_START;
		}
		DATA_STORAGE_STATUS_WAITING;
		break;

	case DATA_STORAGE_STATUS_INIT:
		break;
	}
}

// Initialise the data storage
extern void data_storage_init(void)
{
	data_storage_handle = register_event(&data_storage_service);
}

// Trigger storage service in low priority process.
void storage_service_trigger(void)
{
	trigger_event(data_storage_handle);
}

// Callback when in intialisation
// If init read fails, keep retrying
// If success, signal checking table in background process
void data_storage_init_read_callback(boolean success)
{
	if(success == false)
	{	
		data_storage_status = DATA_STORAGE_STATUS_START;
		return;
	}

	data_storage_status = DATA_STORAGE_CHECK_TABLE;

	return;
};

// Check that the data storage table is valid with the correct checksum
boolean data_storage_check_table(void)
{
	unsigned int mem_checksum;

	// Check that the preamble is correct
	if(memcmp(data_storage_table.table_preamble, table_storage_preamble, 4) != 0) return false;

	// Calcualte the checksum
	mem_checksum = crc_calculate( (uint8_t*) data_storage_table.table, sizeof(*data_storage_table.table) );

	if(mem_checksum != data_storage_table.table_checksum) return false;

	return true;
};


// Format the data storage table
boolean data_storage_format_table(void)
{
	unsigned int mem_counter;

	//Copy the preamble
	memcpy(data_storage_table.table_preamble, table_storage_preamble, 4);

	for(mem_counter = 0; mem_counter < MAX_DATA_HANDLES; mem_counter++)
	{
		data_storage_table.table[mem_counter].data_address 	= 0;
		data_storage_table.table[mem_counter].data_type 	= DATA_STORAGE_NULL;
		data_storage_table.table[mem_counter].data_size 	= 0;
	}

	// Calcualte the checksum
	mem_counter = crc_calculate( (uint8_t*) data_storage_table.table, sizeof(*data_storage_table.table) );

	data_storage_table.table_checksum = mem_counter;

	// Store the table
	if(udb_nv_memory_write( (unsigned char*) &data_storage_table, 0, sizeof(data_storage_table), &data_storage_format_callback) == false)
		return false;
	return true;
}


// Callback after formatting
void data_storage_format_callback(boolean success)
{
	if(success == false)
	{	
		data_storage_status = DATA_STORAGE_STATUS_START;
		return;
	}

	data_storage_status = DATA_STORAGE_STATUS_WAITING;
	return;
};

boolean storage_test_handle(unsigned int data_handle)
{
	DATA_STORAGE_ENTRY* pEntry = &data_storage_table.table[data_handle];
	if(pEntry->data_address == 0) 				return false;
	if(pEntry->data_type == DATA_STORAGE_NULL) 	return false;
	if(pEntry->data_size == 0) 					return false;
	return true;
}

boolean storage_write(unsigned int data_handle, unsigned char* pwrData, unsigned int size)
{
	if(data_storage_status != DATA_STORAGE_STATUS_WAITING) return false;

	data_storage_status = DATA_STORAGE_WRITING;

	if(storage_test_handle(data_handle) == false)  
	{
		pdata_storage_data 		= pwrData;
		data_storage_type 		= data_handle;
		data_storage_size 		= size;
		storage_create_area(data_handle, size);
	}
	return true;
}

boolean storage_create_area(unsigned int data_handle, unsigned int size)
{
	return false;
}

void data_storage_callback(boolean success)
{
	if(success == false)
	{
		data_storage_status = DATA_STORAGE_STATUS_FAILED;
	};

	switch(data_storage_status)
	{
	case DATA_STORAGE_STATUS_WAITING:		
		break;

	case DATA_STORAGE_READING:
		break;

	case DATA_STORAGE_WRITING:
		break;

	case DATA_STORAGE_READ_COMPLETE:
		break;

	case DATA_STORAGE_WRITE_COMPLETE:
		break;
	}
}

