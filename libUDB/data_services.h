#ifndef DATA_SERVICES_H
#define DATA_SERVICES_H

#include "data_storage.h"

#define DATA_SERVICE_BUFFER_SIZE	256

// reference to a RAM variable/item and its size.
typedef struct tagDATA_SERVICE_ITEM
{
	unsigned char*	pData;
	unsigned int	size;
} DATA_SERVICE_ITEM;

//A list of associated variables
typedef DATA_SERVICE_ITEM DATA_SERVICE_ITEMS[];

// 
typedef struct tagDATA_SERVICE_TABLE_ENTRY
{
	unsigned int 		data_storage_handle;
	DATA_SERVICE_ITEM*	pData;
	unsigned int 		item_count;
	unsigned int 		data_type;
} DATA_SERVICE_TABLE_ENTRY;


// Collection of data on all memory areas served
extern const DATA_SERVICE_TABLE_ENTRY data_services_table[];

// Length of the data service table in entried, not bytes
extern const unsigned int data_service_table_count;

// Initialisation of data services.
void data_services_init(void);

// Trigger the event which calls low priority service routine
void data_services_trigger(void);

// Request to load all memory areas from the table
void data_services_load_all(void);

void data_services_load_specific(unsigned int data_storage_handle);

void data_services_save_specific(unsigned int data_storage_handle);

void data_services_init_specific(unsigned int data_storage_handle);


#endif	// DATA_SERVICES_H

