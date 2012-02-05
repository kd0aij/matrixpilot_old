#ifndef DATA_SERVICES_H
#define DATA_SERVICES_H

#include "data_storage.h"

#define DATA_SERVICE_BUFFER_SIZE	256

typedef enum 
{
	DATA_SERVICE_STATE_NOT_STARTED,
	DATA_SERVICE_STATE_INIT	,
	DATA_SERVICE_STATE_WAITING,
	DATA_SERVICE_STATE_WRITE,
	DATA_SERVICE_STATE_WRITING,
	DATA_SERVICE_STATE_READ,
	DATA_SERVICE_STATE_READING,
	DATA_SERVICE_STATE_READ_ALL,
	DATA_SERVICE_STATE_READING_ALL,
} DATA_SERVICE_STATE;

// reference to a RAM variable/item and its size.
typedef struct tagDATA_SERVICE_ITEM
{
	unsigned char*	pData;
	unsigned int	size;
} DATA_SERVICE_ITEM;

//A list of associated variables
typedef DATA_SERVICE_ITEM DATA_SERVICE_ITEMS[];

// 
typedef struct tagDATA_SERVICE_STRUCT
{
	unsigned int 		data_storage_handle;
	DATA_SERVICE_ITEMS*	pData;
	unsigned int 		item_count;
	unsigned int 		data_type;
} DATA_SERVICE_STRUCT;


// Collection of data on all memory areas served
extern const DATA_SERVICE_STRUCT  data_services_table[];

// Length of the data service table in entried, not bytes
extern const unsigned int data_service_entries;

void init_data_services(void);

void trigger_data_services(void);

void data_services_load_all(void);

void data_services_load_specific(unsigned int data_storage_handle);

void data_services_save_specific(unsigned int data_storage_handle);

void data_services_init_specific(unsigned int data_storage_handle);


#endif	// DATA_SERVICES_H

