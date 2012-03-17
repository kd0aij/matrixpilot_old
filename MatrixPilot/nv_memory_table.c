// pyparam generated file - DO NOT EDIT


#include "parameter_table.h"
#include "data_services.h"


const mavlink_parameter_block    mavlink_parameter_blocks[] = {
    { DATA_HANDLE_CONTROL_LOOP_SETTINGS , 0 , 8 , DS_LOAD_AT_STARTUP | DS_LOAD_AT_REBOOT | DS_STORE_CALIB , NULL },
    { DATA_HANDLE_TRIM_CALIB , 8 , 15 , DS_LOAD_AT_STARTUP | DS_LOAD_AT_REBOOT | DS_STORE_CALIB , &udb_skip_radio_trim },
    { DATA_HANDLE_IMU_CALIB , 23 , 7 , DS_LOAD_AT_REBOOT | DS_STORE_CALIB , &udb_skip_imu_calibration },
    };


const unsigned int mavlink_parameter_block_count = sizeof(mavlink_parameter_blocks) / sizeof(mavlink_parameter_block);


