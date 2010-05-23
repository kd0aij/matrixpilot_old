#include "options.h"
#include "libUDB_defines.h"
#include "magnetometerOptions.h"
#include <dsp.h>

// libUDB.h defines the API for accessing the UDB hardware through libUDB
//
// libUDB requires an options.h file be provided that defines at least the following constants:
// 
// #define NUM_INPUTS
// #define NUM_OUTPUTS
// 
// #define FAILSAFE_INPUT_CHANNEL
// #define FAILSAFE_INPUT_MIN
// #define FAILSAFE_INPUT_MAX
// 
// #define NORADIO


// Initialize the UDB
void udb_init(void);


// Run Background Tasks
extern unsigned int cpu_timer;
void udb_background(void);								// Callback
int  udb_cpu_load(void);


// Radio Inputs / Servo Outputs
extern int udb_pwIn[MAX_INPUTS+1];		// pulse widths of radio inputs
extern int udb_pwTrim[MAX_INPUTS+1];	// initial pulse widths for trimming
extern int udb_pwOut[MAX_OUTPUTS+1];	// pulse widths for servo outputs
extern boolean udb_radio_on;

int  udb_servo_pulsesat(long pw);
void udb_servo_record_trims(void);
void udb_servo_callback_prepare_outputs(void);			// Callback


// Accelerometer and Gyroscope Values
extern struct ADchannel udb_xaccel, udb_yaccel, udb_zaccel;	// x, y, and z accelerometer channels
extern struct ADchannel udb_xrate, udb_yrate, udb_zrate;	// x, y, and z gyro channels
extern struct ADchannel udb_vref;							// reference voltage

void udb_a2d_record_offsets(void);


// Magnetometer
extern fractional udb_magFieldBody[3];
extern fractional udb_magOffset[3];

void udb_magnetometer_callback_data_available(void);	// Callback


// LEDs
#define udb_led_toggle(x)		((x) = !(x))


// GPS IO
void udb_gps_set_rate(int rate);
void udb_gps_send_char(char txchar);
void udb_gps_callback_received_char(char rxchar);		// Callback


// Serial IO
void udb_serial_set_rate(int rate);
void udb_serial_start_sending(void);
char udb_serial_callback_sent_char(void);				// Callback
void udb_serial_callback_received_char(char rxchar);	// Callback
