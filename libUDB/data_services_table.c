#include "data_services.h"
#include "libUDB_internal.h"

// List of imu calibration variable items
const DATA_SERVICE_ITEM data_service_imu_calib_items[] =
{
	{ (unsigned char*) &udb_xaccel.offset,  sizeof(udb_xaccel.offset)},
	{ (unsigned char*) &udb_yaccel.offset,  sizeof(udb_yaccel.offset)},
	{ (unsigned char*) &udb_zaccel.offset,  sizeof(udb_zaccel.offset)},

	{ (unsigned char*) &udb_xrate.offset,	sizeof(udb_xrate.offset)},
	{ (unsigned char*) &udb_yrate.offset,	sizeof(udb_yrate.offset)},
	{ (unsigned char*) &udb_zrate.offset,	sizeof(udb_zrate.offset)},

	{ (unsigned char*) &udb_vref.offset,	sizeof(udb_vref.offset)},
};

#define DATA_SERVICE_IMU_CALIB_COUNT sizeof(data_service_imu_calib_items) / sizeof(DATA_SERVICE_ITEM)

// List of trim calibration variable items
const DATA_SERVICE_ITEM data_service_trim_calib_items[] =
{
	{ (unsigned char*) udb_pwTrim,  sizeof(udb_pwTrim)},
};


const DATA_SERVICE_TABLE_ENTRY data_services_table[] = 
{
	{DATA_HANDLE_IMU_CALIB, 	&data_service_imu_calib_items[0], 	DATA_SERVICE_IMU_CALIB_COUNT , 	DATA_STORAGE_CHECKSUM_STRUCT},
	{DATA_HANDLE_TRIM_CALIB, 	&data_service_trim_calib_items[0], 	1, 								DATA_STORAGE_CHECKSUM_STRUCT},
};

const unsigned int data_service_table_count = sizeof(data_services_table) / sizeof(DATA_SERVICE_TABLE_ENTRY);
