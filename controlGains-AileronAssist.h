// control gains.
// All gains should be positive real numbers.

// YAWKP is the proportional feedback gain for the rudder
// YAWKD is the yaw gyro feedback gain for the rudder
// YAWBOOST is the additional gain multiplier for the manually commanded rudder deflection
#define YAWKP 0.0625 // 0.100
#define YAWKD (0.5*SCALEGYRO)
#define YAWBOOST 1.0

// Roll stabilization gains.
// ROLLKP is the proportional gain, approximately 0.25
// ROLLKD is the deriviate (gyro) gain, approximately 0.125
#define ROLLKP 0.25
#define ROLLKD (0.125*SCALEGYRO)

// PITCHGAIN is the pitch stabilization gain, typically around 0.125
// PITCHKD feedback gain for pitch damping, around 0.0625
// PITCHBOOST is optional (I do not use it myself), around 0.25
// RUDDERELEVMIX is the degree of elevator adjustment for rudder and banking
#define PITCHGAIN 0.150  //0.225
#define PITCHKD (0.0625*SCALEGYRO)
#define PITCHBOOST 1.0

#define RUDDERELEVMIX 1.0

// the real number SERVOSAT limits servo throw by controlling pulse width saturation.
// set it to 1.0 if you want full servo throw, otherwise set it to the portion that you want
#define SERVOSAT 1.0


// the following section is for altitude hold
#define HEIGHTMAX 100.0 // maximum target height in meters
#define MINIMUMTHROTTLE 0.35 // minimum throttle
#define PITCHATMINTHROTTLE 0.0  // target pitch angle in degrees at minimum throttle
#define PITCHATMAXTHROTTLE 15.0 // target pitch angle in degrees at maximum throttle
#define PITCHATZEROTHROTTLE 0.0 // target pitch angle in degrees while gliding


// The following section is for camera stabilization
// These values are untested and will need adjustment
#define CAMERA_ROLLKP	0.5
#define CAMERA_PITCHKP	0.5
#define CAMERA_YAWKP	0.5


// the following define is used to test the above gains and parameters.
// if you define TestGains, there functions will be enabled, even without GPS or Tx turned on.
//#define TestGains		// uncomment this line if you want to test your gains without using GPS
