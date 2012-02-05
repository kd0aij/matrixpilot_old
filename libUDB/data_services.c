#include "data_services.h"
#include "events.h"
#include <string.h>

// Data Services
// Responsible for serialisation of sets of variables
// Reponsible for recalling sets data storage on startup
// Reponsible for initialising data storage at startup

// Data buffer used for services
unsigned char data_services_buffer[DATA_SERVICE_BUFFER_SIZE];

// All the states of the service
typedef enum 
{
	DATA_SERVICE_STATE_NOT_STARTED,
	DATA_SERVICE_STATE_INIT_ALL	,			// Initialise memory areas for all table entries
	DATA_SERVICE_STATE_INIT_WAIT ,			// Waiting for initialise of a table entry
	DATA_SERVICE_STATE_INIT ,				// Initialise the next area
	DATA_SERVICE_STATE_WAITING,				// Ready and waiting
	DATA_SERVICE_STATE_WRITE,				// A single write
	DATA_SERVICE_STATE_WRITING,				// Waiting for single write to complete
	DATA_SERVICE_STATE_READ,				// A single read
	DATA_SERVICE_STATE_READING,				// Waiting for single read to complete
	DATA_SERVICE_STATE_READ_ALL,			// Start of read all
	DATA_SERVICE_STATE_WAITING_READ_ALL,	// Waiting for a read all to complete
	DATA_SERVICE_STATE_READ_ALL_DONE_AREA,	// Done reading an area during read all, commit it to ram.
	DATA_SERVICE_STATE_READING_ALL,			// Do the next read of read all
} DATA_SERVICE_STATE;

// service state variable
unsigned int data_service_state = DATA_SERVICE_STATE_NOT_STARTED;

// Handle to event that will trigger the low priority service routine
unsigned int data_service_event_handle = INVALID_HANDLE;

// Low priority service routine
void data_services(void);

// Start init of all memory areas in the services table
void data_services_init_all(void);

// Service intialisation of memory areas starting at the tracking index
void data_services_init_table_index(void);

// Callback for completetion of memory area init
void data_services_init_all_callback(boolean success);

// Start of reading all areas in the table
void data_services_read_all( void );

// Read data area at index for reading all areas
void data_services_read_all_index( void );

// callback for reading all areas in the table
void data_services_read_all_callback(boolean success);

// When finished reading an area, call to commit area to ram
void data_services_read_all_done_area( void );

// Serialise a list of data items/variables to the buffer
void serialise_items_to_buffer(unsigned int table_index);

// Serialise the buffer to a list of data items/variables
void serialise_buffer_to_items(unsigned int table_index);



// Calculate the size of the complete list of variable items in bytes
unsigned int data_services_calc_item_size(unsigned int table_index);

// Tracking index into table
unsigned int data_services_table_index = 0;


void data_services_init(void)
{
	if(data_service_state != DATA_SERVICE_STATE_NOT_STARTED) return;
	if( (data_service_event_handle = data_service_event_handle = register_event(&data_services)) == INVALID_HANDLE)
		return;
	data_service_state = DATA_SERVICE_STATE_INIT;
};


// Low priority service routine trigger
inline void data_services_trigger(void)
{
	trigger_event(data_service_event_handle);
}

void data_services(void)
{
	switch(data_service_state)
	{
	case  DATA_SERVICE_STATE_INIT:
		data_services_init_all();
		break;
	case  DATA_SERVICE_STATE_INIT_ALL:
		data_services_init_table_index();
		break;
	case DATA_SERVICE_STATE_READ_ALL:
		data_services_read_all();
		break;
	case DATA_SERVICE_STATE_READING_ALL:
		data_services_read_all_index();
		break;
	case DATA_SERVICE_STATE_READ_ALL_DONE_AREA:
		data_services_read_all_done_area();
		break;
	}
}

void data_services_init_all(void)
{
	data_services_table_index = 0;
	data_service_state =	DATA_SERVICE_STATE_INIT_ALL;
}

void data_services_init_table_index(void)
{
	while(data_services_table_index < data_service_table_count)
	{
		if(storage_services_started())
		{
			if ( storage_check_area_exists(
						data_services_table[data_services_table_index].data_storage_handle,
						data_services_calc_item_size(data_services_table_index),
						data_services_table[data_services_table_index].data_type) == true)
			{
				data_services_table_index++;
			}
			else
			{
				// Storage area does not exist so request to create it
				if(storage_create_area(	data_services_table[data_services_table_index].data_storage_handle, 
										data_services_calc_item_size(data_services_table_index), 
										data_services_table[data_services_table_index].data_type, 
										&data_services_init_all_callback) == true)
				{
					// If the request succeeds, wait for it to complete
					data_service_state = DATA_SERVICE_STATE_READ_ALL;
					return;
				}
				else
				{
					// if the request failed, try again.
					return;					
				}
			}			
		}

		return;
	}

	data_service_state = DATA_SERVICE_STATE_WAITING;
}


void data_services_init_all_callback(boolean success)
{
	if(success) data_services_table_index++;
	data_service_state =	DATA_SERVICE_STATE_INIT_ALL;
}


// Calculate the size of the complete list of variable items in bytes
unsigned int data_services_calc_item_size(unsigned int table_index)
{
	unsigned int item_index;
	unsigned int size = 0;

	for(item_index = 0; item_index < data_services_table[table_index].item_count; item_index++)
	{
		size += data_services_table[table_index].pData[item_index].size;
	}
	return size;
}


// Read data area at index for reading all areas
void data_services_read_all_index( void )
{
	// If beyond end of table return to waiting.
	if(data_services_table_index >= data_service_table_count)
	{
		data_service_state =	DATA_SERVICE_STATE_WAITING;
		return;
	}

	unsigned int handle = data_services_table[data_services_table_index].data_storage_handle;
	unsigned int size = data_services_calc_item_size(handle);
	unsigned int type = data_services_table[data_services_table_index].data_type;

	if(type == DATA_STORAGE_CHECKSUM_STRUCT)
	{
		if(storage_read(handle, data_services_buffer, size, &data_services_read_all_callback) == true)
			data_service_state =	DATA_SERVICE_STATE_WAITING_READ_ALL;
		else
			data_services_table_index++;
		return;
	}
	data_services_table_index++;
}

// Test data and commit it
void data_services_read_all_done_area( void )
{
	data_services_table_index++;
	data_service_state =	DATA_SERVICE_STATE_READ_ALL;
}

// Called when storage manager data read has finished
void data_services_read_all_callback(boolean success)
{
	if(success)
		data_service_state =	DATA_SERVICE_STATE_READ_ALL_DONE_AREA;
	else
		data_services_table_index++;
		data_service_state =	DATA_SERVICE_STATE_READ_ALL;
}


// Serialise a list of data items/variables to the buffer
void serialise_items_to_buffer(unsigned int table_index)
{
	if(table_index >= data_service_table_count) return;

	DATA_SERVICE_TABLE_ENTRY* 	pTableEntry = &data_services_table[table_index];
	DATA_SERVICE_ITEM* 			pDataItem;
	unsigned char*				pData;

	unsigned int 	item_index;
	unsigned int 	buffer_index;
	unsigned int 	item_size;

	for(item_index = 0; item_index < pTableEntry->item_count; item_index++)
	{
		pDataItem 	= &(pTableEntry->pData[item_index]);
		pData 		= pDataItem->pData;
		item_size 	= pDataItem->size;
		if( (buffer_index + item_size) > DATA_SERVICE_BUFFER_SIZE )
			return;
		memcpy(&data_services_buffer[buffer_index], pDataItem, item_size);
		buffer_index += item_size;
	}
}


// Serialise the buffer to a list of data items/variables
void serialise_buffer_to_items(unsigned int table_index)
{
	if(table_index >= data_service_table_count) return;

	DATA_SERVICE_TABLE_ENTRY* 	pTableEntry = &data_services_table[table_index];
	DATA_SERVICE_ITEM* 			pDataItem;
	unsigned char*				pData;

	unsigned int 	item_index;
	unsigned int 	buffer_index;
	unsigned int 	item_size;

	for(item_index = 0; item_index < pTableEntry->item_count; item_index++)
	{
		pDataItem 	= &(pTableEntry->pData[item_index]);
		pData 		= pDataItem->pData;
		item_size 	= pDataItem->size;
		if( (buffer_index + item_size) > DATA_SERVICE_BUFFER_SIZE )
			return;
		memcpy(pDataItem, &data_services_buffer[buffer_index], item_size);
		buffer_index += item_size;
	}
}
