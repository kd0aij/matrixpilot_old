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
	DATA_STORAGE_READ_HEADER,
	DATA_STORAGE_READING_HEADER,
	DATA_STORAGE_READ,
	DATA_STORAGE_READING,
	DATA_STORAGE_WRITE,
	DATA_STORAGE_WRITING,
	DATA_STORAGE_READ_COMPLETE,
	DATA_STORAGE_WRITE_COMPLETE,
	DATA_STORAGE_STATUS_FAILED,
	DATA_STORAGE_AREA_CREATE,
	DATA_STORAGE_AREA_CREATING,
} DATA_STORAGE_STATUS;

unsigned int data_storage_status = DATA_STORAGE_STATUS_START;

// store the data storage table
boolean data_storage_store_table(void);

// Check the integrity of the data storage table
boolean data_storage_check_table(void);

// Format the data storage table
boolean data_storage_format_table(void);

// Find a hole of size data_storage_size and return its address.
unsigned int data_storage_find_hole(unsigned int data_storage_size);

// Callbacks
// The callbacks normally set the status so that the background service routine does the work.
void data_storage_callback(boolean success);			// Callback from non volatile memory driver
void data_storage_format_callback(boolean success);		// format write is completed
void data_storage_init_read_callback(boolean success);	// initialisation read of storage table
void storage_write_callback(boolean success);			// Data write callback
void storage_read_callback(boolean success);			// Data read callback
void data_storage_write_table_callback(boolean success);// Table write callback

// A constant preamble used to determine the start of a data block
// This also allows the data to be found if the FAT is broken
const unsigned char data_storage_preamble[] = {0xAA, 0x5A, 0xA5, 0x55};

// A constant preamble used to determine the start of the data storage table
const unsigned char table_storage_preamble[] = {0x55, 0xA5, 0x5A, 0xAA};

// Structure in ram of complete data directory including checksum.
DATA_STORAGE_TABLE data_storage_table;

// Callers data.  Used on initialisation, readinng or writing an area.
unsigned char* 	pdata_storage_data 	= NULL;
unsigned int 	data_storage_type 	= DATA_STORAGE_NULL;
unsigned int 	data_storage_size 	= 0;
unsigned int 	data_storage_handle = INVALID_HANDLE;
DS_callbackFunc data_storage_user_callback = NULL;

unsigned int 	data_storage_event_handle = INVALID_HANDLE;

// Status of sotage services
boolean storage_services_started()
{
	switch(data_storage_status)
	{
	case DATA_STORAGE_STATUS_START:
	case DATA_STORAGE_CHECK_TABLE:
	case DATA_STORAGE_STATUS_INIT:
		return false;
	}
	return true;
}


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
		else
		{
			data_storage_status = DATA_STORAGE_STATUS_WAITING;
		}
		break;
	case DATA_STORAGE_WRITE:
		// Write data to nv memory
		// If NV memory not ready, immediate return.
		if(udb_nv_memory_write( pdata_storage_data, data_storage_table.table[data_storage_handle].data_address, data_storage_size, &storage_write_callback) == false)
		{
			if(data_storage_user_callback != NULL)
				data_storage_user_callback(false);
		}

		data_storage_status = DATA_STORAGE_WRITING;	
		break;

	case DATA_STORAGE_READ:
		// Read data from nv memory
		// If NV memory not ready, immediate return.
		if(udb_nv_memory_read( pdata_storage_data, data_storage_table.table[data_storage_handle].data_address, data_storage_size, &storage_read_callback) == false)
		{
			if(data_storage_user_callback != NULL)
				data_storage_user_callback(false);
		}

		data_storage_status = DATA_STORAGE_READING;	
		break;

	case DATA_STORAGE_AREA_CREATE:
		if( (data_storage_table.table[data_storage_handle].data_address = data_storage_find_hole(data_storage_size)) == 0)
		{
			// Failed to find space for new data area
			if(data_storage_user_callback != NULL)
				data_storage_user_callback(false);
		}
		
		data_storage_table.table[data_storage_handle].data_size = data_storage_size;
		data_storage_table.table[data_storage_handle].data_type = data_storage_type;

		data_storage_status = DATA_STORAGE_AREA_CREATING;

		// Calculate the checksum
		data_storage_table.table_checksum = crc_calculate( (uint8_t*) data_storage_table.table, sizeof(*data_storage_table.table) );

		// Store the table
		if(udb_nv_memory_write( (unsigned char*) &data_storage_table, 0, sizeof(data_storage_table), &data_storage_write_table_callback) == false)
		{
			data_storage_table.table[data_storage_handle].data_size = 0;
			data_storage_table.table[data_storage_handle].data_type = 0;
			data_storage_table.table[data_storage_handle].data_address = 0;

			if(data_storage_user_callback != NULL)
				data_storage_user_callback(false);

			data_storage_status = DATA_STORAGE_STATUS_WAITING;	
		}

		data_storage_status = DATA_STORAGE_AREA_CREATING;	

		break;

	case DATA_STORAGE_STATUS_INIT:
		break;
	}
}

void data_storage_write_table_callback(boolean success)
{
	if(data_storage_user_callback != NULL)
		data_storage_user_callback(success);

	data_storage_status = DATA_STORAGE_STATUS_WAITING;	
}

// Initialise the data storage
extern void data_storage_init(void)
{
	data_storage_event_handle = register_event(&data_storage_service);
}

// Trigger storage service in low priority process.
void storage_service_trigger(void)
{
	trigger_event(data_storage_event_handle);
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

	// Calculate the checksum
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

// Test the data handle to see if it has allocated storage
// return true if space is allocated
boolean storage_test_handle(unsigned int data_handle)
{
	DATA_STORAGE_ENTRY* pEntry = &data_storage_table.table[data_handle];
	if(pEntry->data_address == 0) 				return false;
	if(pEntry->data_type == DATA_STORAGE_NULL) 	return false;
	if(pEntry->data_size == 0) 					return false;
	if(data_handle >= DATA_HANDLE_MAX)			return false;
	return true;
}

boolean storage_write(unsigned int data_handle, unsigned char* pwrData, unsigned int size, DS_callbackFunc callback)
{
	if(data_storage_status != DATA_STORAGE_STATUS_WAITING) return false;

	// If the data storage area has not been created, return false
	if(storage_test_handle(data_handle) == false)
		return false;

	// If the allocated storage area is the wrong size, return false
	if(data_storage_table.table[data_handle].data_size != size) return false;

	pdata_storage_data 	= pwrData;
	data_storage_size 	= size;
	data_storage_handle = data_handle;
	data_storage_user_callback = callback;

	data_storage_status = DATA_STORAGE_WRITE;

	return true;
}

void storage_write_callback(boolean success)
{
	data_storage_user_callback(success);
	data_storage_status = DATA_STORAGE_STATUS_WAITING;
}


boolean storage_read(unsigned int data_handle, unsigned char* pwrData, unsigned int size, DS_callbackFunc callback)
{
	if(data_storage_status != DATA_STORAGE_STATUS_WAITING) return false;

	// If the data storage area has not been created, return false
	if(storage_test_handle(data_handle) == false)
		return false;

	// If the allocated storage area is the wrong size, return false
	if(data_storage_table.table[data_handle].data_size != size) return false;

	pdata_storage_data 	= pwrData;
	data_storage_size 	= size;
	data_storage_handle = data_handle;
	data_storage_user_callback = callback;

	data_storage_status = DATA_STORAGE_READ;

	return true;
}

void storage_read_callback(boolean success)
{
	data_storage_user_callback(success);
	data_storage_status = DATA_STORAGE_STATUS_WAITING;
}



// Lookup the data storage table to see if an area exists
// Does not require callback.  Always has immediate return
boolean storage_check_area_exists(unsigned int data_handle, unsigned int size, unsigned int type)
{
	if(data_storage_table.table[data_handle].data_address == 0) return false;
	if(data_storage_table.table[data_handle].data_size != size) return false;
	if(data_storage_table.table[data_handle].data_type != type) return false;
	return true;
}


// Create a storage area
// Size = size in bytes
// type = data management type
// callback = user callback for when process finished
boolean storage_create_area(unsigned int data_handle, unsigned int size, unsigned int type, DS_callbackFunc callback)
{
	if(data_storage_status != DATA_STORAGE_STATUS_WAITING) return false;

	pdata_storage_data 			= NULL;
	data_storage_type 			= type;
	data_storage_size 			= size;
	data_storage_handle 		= data_handle;
	data_storage_user_callback 	= callback;

	data_storage_status = DATA_STORAGE_AREA_CREATE;
	return true;
}


// Find the address of the next page start
inline unsigned int find_next_page_address(unsigned int address)
{
	unsigned int temp = address / FAT_CHUNK_BYTE_SIZE;
	temp++;
	return temp * FAT_CHUNK_BYTE_SIZE;
}


// Find a hole of size data_storage_size and return its address.
//
// TEMPORARY:  Finds next available space after all areas.
// TEMPORARY:  Does not find holes yet.  Does not check max size
//
unsigned int data_storage_find_hole(unsigned int data_storage_size)
{
	unsigned int lowestAddr = find_next_page_address(sizeof(data_storage_table));
	
	unsigned int scanAddr 	= 0;
	unsigned int maxAddr 	= 0;

	unsigned int handle 	= 0;
	
	for(handle = 0; handle <= DATA_HANDLE_MAX; handle++)
	{
		scanAddr = data_storage_table.table[handle].data_address;
		maxAddr = scanAddr + data_storage_table.table[handle].data_size;
		maxAddr = find_next_page_address(maxAddr);

		if(maxAddr > lowestAddr)
			lowestAddr = maxAddr;
	}

	return lowestAddr;
}
