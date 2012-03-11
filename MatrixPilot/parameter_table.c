// pyparam generated file - DO NOT EDIT


#include "parameter_table.h"
#include "data_storage.h"
const mavlink_parameter_parser    mavlink_parameter_parsers[] = {
    { &mavlink_send_param_int16, &mavlink_set_param_int16, MAVLINK_TYPE_INT32_T},
    { &mavlink_send_param_Q14, &mavlink_set_param_Q14, MAVLINK_TYPE_FLOAT},
    { &mavlink_send_param_pwtrim, &mavlink_set_param_pwtrim, MAVLINK_TYPE_FLOAT},
    { &mavlink_send_param_gyroscale_Q14, &mavlink_set_param_gyroscale_Q14, MAVLINK_TYPE_FLOAT},
    };

const mavlink_parameter mavlink_parameters_list[] = {
     {"PID_ROLLKP" , {.param_float=0.0} , {.param_float=0.4} , UDB_TYPE_Q14, PARAMETER_READWRITE, (void*) &rollkp, sizeof(rollkp) },
    {"PID_ROLLKD" , {.param_float=0.0} , {.param_float=0.4} , UDB_TYPE_GYROSCALE_Q14, PARAMETER_READWRITE, (void*) &rollkd, sizeof(rollkd) },
    {"PID_YAWKPAIL" , {.param_float=0.0} , {.param_float=0.4} , UDB_TYPE_Q14, PARAMETER_READWRITE, (void*) &yawkpail, sizeof(yawkpail) },
    {"PID_YAWKDAIL" , {.param_float=0.0} , {.param_float=0.4} , UDB_TYPE_GYROSCALE_Q14, PARAMETER_READWRITE, (void*) &yawkdail, sizeof(yawkdail) },
    {"PID_YAWKPRUD" , {.param_float=0.0} , {.param_float=0.4} , UDB_TYPE_Q14, PARAMETER_READWRITE, (void*) &yawkprud, sizeof(yawkprud) },
    {"PID_ROLLKPRUD" , {.param_float=0.0} , {.param_float=0.4} , UDB_TYPE_Q14, PARAMETER_READWRITE, (void*) &rollkprud, sizeof(rollkprud) },
    {"PID_PITCHGAIN" , {.param_float=0.0} , {.param_float=0.4} , UDB_TYPE_Q14, PARAMETER_READWRITE, (void*) &pitchgain, sizeof(pitchgain) },
    {"PID_RUDELEVMIXGAIN" , {.param_float=0.0} , {.param_float=0.4} , UDB_TYPE_Q14, PARAMETER_READWRITE, (void*) &rudderElevMixGain, sizeof(rudderElevMixGain) },


    };

const int count_of_parameters_list = sizeof(mavlink_parameters_list) / sizeof(mavlink_parameter);


