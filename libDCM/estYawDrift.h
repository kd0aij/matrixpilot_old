#ifndef ESTYAWDRIFT_H
#define ESTYAWDRIFT_H


#if (MAG_YAW_DRIFT == 1)
void udb_magnetometer_callback(void);
#endif


// Allows disabling yaw drift estimation.
// Starts off enabled.  Call this to disable and to then re-enable.
void dcm_enable_yaw_drift_correction(boolean enabled);


extern signed char actual_dir ;
extern signed char calculated_heading ;

void estYawDrift(void);


#endif // ESTYAWDRIFT_H
