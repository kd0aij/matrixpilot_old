#include "../libUDB/libUDB.h"

#ifndef GAIN_VARIABLES_H
#define GAIN_VARIABLES_H


#define GAINS_VARIABLE			0

// Aileron/Roll Control Gains
// ROLLKP is the proportional gain, approximately 0.25
// ROLLKD is the derivative (gyro) gain, approximately 0.125
// YAWKP_AILERON is the proportional feedback gain for ailerons in response to yaw error
// YAWKD_AILERON is the derivative feedback gain for ailerons in response to yaw rotation
// AILERON_BOOST is the additional gain multiplier for the manually commanded aileron deflection

#if ((SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK) || ( GAINS_VARIABLE == 1 ))
   // MAVLINK, QGROUND CONTROL (Ground Control Station) can change these variables 
	extern int rollkp;
	extern int rollkd;
	extern int yawkpail;
	extern int yawkdail;
#else
	extern const int rollkp;
	extern const int rollkd;
	extern const int yawkpail;
	extern const int yawkdail;
#endif
//#define AILERON_BOOST						1.0

// Elevator/Pitch Control Gains
// PITCHGAIN is the pitch stabilization gain, typically around 0.125
// PITCHKD feedback gain for pitch damping, around 0.0625
// RUDDER_ELEV_MIX is the degree of elevator adjustment for rudder and banking
// AILERON_ELEV_MIX is the degree of elevator adjustment for aileron
// ELEVATOR_BOOST is the additional gain multiplier for the manually commanded elevator deflection
#if ((SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK) || ( GAINS_VARIABLE == 1 ))
	extern int pitchgain;
	extern int pitchkd;
	extern int rudderElevMixGain;
	extern int rollElevMixGain;
#else
	extern const int pitchgain;
	extern const int pitchkd;
	extern const int rudderElevMixGain;
	extern const int rollElevMixGain;
#endif
//#define ELEVATOR_BOOST						0.5

// Neutral pitch angle of the plane (in degrees) when flying inverted
// Use this to add extra "up" elevator while the plane is inverted, to avoid losing altitude.
//#define INVERTED_NEUTRAL_PITCH				8.0

// Rudder/Yaw Control Gains
// YAWKP_RUDDER is the proportional feedback gain for rudder navigation
// YAWKD_RUDDER is the yaw gyro feedback gain for the rudder in reponse to yaw rotation
// ROLLKP_RUDDER is the feedback gain for the rudder in response to the current roll angle
// ROLLKD_RUDDER is the feedback gain for the rudder in response to the rate of roll
// MANUAL_AILERON_RUDDER_MIX is the fraction of manual aileron control to mix into the rudder when
// in stabilized or waypoint mode.  This mainly helps aileron-initiated turning while in stabilized.
// RUDDER_BOOST is the additional gain multiplier for the manually commanded rudder deflection
#if ((SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK) || ( GAINS_VARIABLE == 1 ))
	extern int yawkprud;
	extern int yawkdrud;
	extern int rollkprud;
	extern int rollkdrud;
#else
	extern const int yawkprud;
	extern const int yawkdrud;
	extern const int rollkprud;
	extern const int rollkdrud;
#endif

// Gains for Hovering
// Gains are named based on plane's frame of reference (roll means ailerons)
// HOVER_ROLLKP is the roll-proportional feedback gain applied to the ailerons while navigating a hover
// HOVER_ROLLKD is the roll gyro feedback gain applied to ailerons while stabilizing a hover
// HOVER_PITCHGAIN is the pitch-proportional feedback gain applied to the elevator while stabilizing a hover
// HOVER_PITCHKD is the pitch gyro feedback gain applied to elevator while stabilizing a hover
// HOVER_PITCH_OFFSET is the neutral pitch angle for the plane (in degrees) while stabilizing a hover
// HOVER_YAWKP is the yaw-proportional feedback gain applied to the rudder while stabilizing a hover
// HOVER_YAWKD is the yaw gyro feedback gain applied to rudder while stabilizing a hover
// HOVER_YAW_OFFSET is the neutral yaw angle for the plane (in degrees) while stabilizing a hover
// HOVER_PITCH_TOWARDS_WP is the max angle in degrees to pitch the nose down towards the WP while navigating
// HOVER_NAV_MAX_PITCH_RADIUS is the radius around a waypoint in meters, within which the HOVER_PITCH_TOWARDS_WP
//                            value is proportionally scaled down.

#if ((SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK) || ( GAINS_VARIABLE == 1 ))
	extern int hoverrollkp;
	extern int hoverrollkd;
	extern int hoverpitchgain;
	extern int hoverpitchkd;
	extern int hoveryawkp;
	extern int hoveryawkd;
#else
	extern const int hoverrollkp;
	extern const int hoverrollkd;
	extern const int hoverpitchgain;
	extern const int hoverpitchkd;
	extern const int hoveryawkp;
	extern const int hoveryawkd;
#endif

//#define MANUAL_AILERON_RUDDER_MIX			0.20

#endif 	//GAIN_VARIABLES_H
