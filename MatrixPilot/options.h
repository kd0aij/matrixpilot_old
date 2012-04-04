// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


////////////////////////////////////////////////////////////////////////////////
// options.h
// Bill Premerlani's UAV Dev Board
// 
// This file includes all of the user-configuration for this firmware,
// with the exception of waypoints, which live in the waypoints.h file.
// 
// Note that there is a small but growing library of preset options.h files for
// specific planes located in the MatrixPilot/example-options-files directory.
// You can use one of those files by replacing this file with that one.


////////////////////////////////////////////////////////////////////////////////
// Set Up Board Type
// GREEN_BOARD - Board is green and includes 2 vertical gyro daugter-boards.
// RED_BOARD   - Board is red, and includes 2 vertical gyro daugter-boards.
// UDB3_BOARD  - Board is red, and includes a single, flat, multi-gyro daugter-board.
// UDB4_BOARD  - Board is red, has 8 inputs, 8 output and no gyro daughter-board.
// AUAV1_BOARD - Nick Arsov's UDB3 clone, version one
// See the MatrixPilot wiki for more details on different UDB boards.
// If building for the UDB4, use the MatrixPilot-udb4.mcw project workspace. 
#define BOARD_TYPE 							UDB3_BOARD


////////////////////////////////////////////////////////////////////////////////
// Use board orientation to change the mounting direction of the board.
// Note: For UDB3 and older versions of UDB, Y arrow points to the front, GPS connector is on the front.
//       For UDB4, X arrow points to the front, GPS connectors are on the front.
// The following 6 orientations have the board parallel with the ground.
// ORIENTATION_FORWARDS:  Component-side up,   GPS connector front
// ORIENTATION_BACKWARDS: Component-side up,   GPS connector back
// ORIENTATION_INVERTED:  Component-side down, GPS connector front
// ORIENTATION_FLIPPED:   Component-side down, GPS connector back
// ORIENTATION_YAWCW:     Component-side up,   GPS connector to the right
// ORIENTATION_YAWCCW:    Component-side up,   GPS connector to the left
// 
// The following 2 orientations are "knife edge" mountings
// ORIENTATION_ROLLCW: Rick's picture #9, board rolled 90 degrees clockwise,
//		from point of view of the pilot
// ORIENTATION_ROLLCW180: Rick's pitcure #11, board rolled 90 degrees clockwise,
//		from point of view of the pilot, then rotate the board 180 around the Z axis of the plane,
//		so that the GPS connector points toward the tail of the plane
#define BOARD_ORIENTATION					ORIENTATION_FORWARDS
// Define MAG_YAW_DRIFT to be 1 to use magnetometer for yaw drift correction.
// Otherwise, if set to 0 the GPS will be used.
// If you select this option, you also need to set magnetometer options in
// the magnetometerOptions.h file, including declination and magnetometer type.
#define MAG_YAW_DRIFT 						0

// Define BAROMETER_ALTITUDE to be 1 to use barometer for altitude correction.
// Otherwise, if set to 0 only the GPS will be used.
// If you select this option, you also need to set barometer options in
// the barometerOptions.h file, including takeoff location altitude and/or sea level pressure
// at the time of initialisation.
#define BAROMETER_ALTITUDE 					1


// Set this to 1 if you want the UAV Dev Board to fly your plane without a radio transmitter or
// receiver. (Totally autonomous.)  This is just meant for simulation and debugging.  It is not
// recommended that you actually use this option, since you'd have no manual control to fall
// back on if things go wrong.  It may not even be legal in your area.
#define NORADIO								0


////////////////////////////////////////////////////////////////////////////////
// Configure Input and Output Channels
//
// Use a single PPM input connection from the RC receiver to the UDB on RC input channel 4.
// This frees up RC inputs 3, 2, and 1 to act as RC outputs 4, 5, and 6.
// If you're not sure, leave USE_PPM_INPUT set to 0.
// PPM_NUMBER_OF_CHANNELS is the number of channels sent on the PWM signal.  This is
// often different from the NUM_INPUTS value below, and should usually be left at 8.
// If PPM_ALT_OUTPUT_PINS is set to 0, the 9 available RC outputs will be sent to the
// following pins, in this order: Out1, Out2, Out3, In3, In2, In1, RE0, RE2, RE4.
// With it set to 1, the RC outputs will be in this alternate configuration:
// Out1, Out2, Out3, RE0, RE2, RE4, In3, In2, In1.
#define USE_PPM_INPUT						0
#define PPM_NUMBER_OF_CHANNELS				8
#define PPM_SIGNAL_INVERTED					0
#define PPM_ALT_OUTPUT_PINS					0

// NUM_INPUTS: Set to 1-5 (or 1-8 when using PPM input)
//   1-4 enables only the first 1-4 of the 4 standard input channels
//   5 also enables E8 as the 5th input channel
#define NUM_INPUTS							5

// Channel numbers for each input.
// Use as is, or edit to match your setup.
//   - If you're set up to use Rudder Navigation (like MatrixNav), then you may want to swap
//     the aileron and rudder channels so that rudder is CHANNEL_1, and aileron is 5.
#define THROTTLE_INPUT_CHANNEL				CHANNEL_3
#define AILERON_INPUT_CHANNEL				CHANNEL_1
#define ELEVATOR_INPUT_CHANNEL				CHANNEL_2
//#define RUDDER_INPUT_CHANNEL				CHANNEL_5
//#define MODE_SWITCH_INPUT_CHANNEL			CHANNEL_4
#define RUDDER_INPUT_CHANNEL				CHANNEL_4
#define MODE_SWITCH_INPUT_CHANNEL			CHANNEL_5
#define CAMERA_PITCH_INPUT_CHANNEL			CHANNEL_UNUSED
#define CAMERA_YAW_INPUT_CHANNEL			CHANNEL_UNUSED
#define CAMERA_MODE_INPUT_CHANNEL			CHANNEL_UNUSED
#define OSD_MODE_SWITCH_INPUT_CHANNEL		CHANNEL_UNUSED
#define PASSTHROUGH_A_INPUT_CHANNEL			CHANNEL_UNUSED
#define PASSTHROUGH_B_INPUT_CHANNEL			CHANNEL_UNUSED
#define PASSTHROUGH_C_INPUT_CHANNEL			CHANNEL_UNUSED
#define PASSTHROUGH_D_INPUT_CHANNEL			CHANNEL_UNUSED



// NUM_OUTPUTS: Set to 3, 4, 5, or 6
//   3 enables only the standard 3 output channels
//   4 also enables E0 as the 4th output channel
//   5 also enables E2 as the 5th output channel
//   6 also enables E4 as the 6th output channel
//   NOTE: If USE_PPM_INPUT is enabled above, up to 9 outputs are available.)
#define NUM_OUTPUTS							4
// Channel numbers for each output
// Use as is, or edit to match your setup.
//   - Only assign each channel to one output purpose
//   - If you don't want to use an output channel, set it to CHANNEL_UNUSED
//   - If you're set up to use Rudder Navigation (like MatrixNav), then you may want to swap
//     the aileron and runner channels so that rudder is CHANNEL_1, and aileron is 5.
// 
// NOTE: If your board is powered from your ESC through the throttle cable, make sure to
// connect THROTTLE_OUTPUT_CHANNEL to one of the built-in Outputs (1, 2, or 3) to make
// sure your board gets power.
// 
#define THROTTLE_OUTPUT_CHANNEL				CHANNEL_1
#define AILERON_OUTPUT_CHANNEL				CHANNEL_3
#define ELEVATOR_OUTPUT_CHANNEL				CHANNEL_2
#define RUDDER_OUTPUT_CHANNEL				CHANNEL_4
#define AILERON_SECONDARY_OUTPUT_CHANNEL	CHANNEL_UNUSED
#define CAMERA_PITCH_OUTPUT_CHANNEL			CHANNEL_UNUSED
#define CAMERA_YAW_OUTPUT_CHANNEL			CHANNEL_UNUSED
#define TRIGGER_OUTPUT_CHANNEL				CHANNEL_UNUSED
#define PASSTHROUGH_A_OUTPUT_CHANNEL		CHANNEL_UNUSED
#define PASSTHROUGH_B_OUTPUT_CHANNEL		CHANNEL_UNUSED
#define PASSTHROUGH_C_OUTPUT_CHANNEL		CHANNEL_UNUSED
#define PASSTHROUGH_D_OUTPUT_CHANNEL		CHANNEL_UNUSED


////////////////////////////////////////////////////////////////////////////////
// On Screen Display
// USE_OSD enables the OSD system.  Customize the OSD Layout in the osd_layout.h file.
#define USE_OSD								1

// NUM_ANALOG_INPUTS: Set to 0, 1, or 2
//   1 enables Radio In 1 as an analog Input
//   2 also enables Radio In 2 as another analog Input
//   NOTE: Can only be set this higher than 0 if USE_PPM_INPUT is enabled above.
#define NUM_ANALOG_INPUTS					0

// Channel numbers for each analog input
//   - Only assign each channel number to one analog sensor
//   - If you don't want to use an output channel, set it to CHANNEL_UNUSED
//   - Only 2 analog inputs are available, so you can't use all the defined analog
//     sensors at once
// 
// ANALOG_CURRENT_INPUT_CHANNEL and ANALOG_VOLTAGE_INPUT_CHANNEL let you plug in and
// use this Voltage/Current sensor board from SparkFun:
//    http://www.sparkfun.com/products/9028
// Just plug the ground and signal lines of the chosen current input channel into the
// ground and current outputs of the current sensor, and the signal line of the chosen
// voltage input channel to the voltage output from the current sensor.  Values for
// instantaneous current, voltage, and mAh used will become available for use with the
// OSD layout.
// 
// ANALOG_RSSI_INPUT_CHANNEL lets you connect your RC Receiver's RSSI output to your
// UDB, in order to see the RC signal strength on your OSD.  Just plug RSSI and ground
// from your Receiver to Input2's signal and ground on your UDB.  If you use this feature,
// you'll also need to set up the RSSI_MIN_SIGNAL_VOLTAGE and RSSI_MAX_SIGNAL_VOLTAGE
// to match your Receiver's RSSI format.  Note that some receivers use a higher voltage to 
// represent a lower signal strength, so you may need to set MIN higher than MAX.

#define ANALOG_CURRENT_INPUT_CHANNEL		CHANNEL_UNUSED
#define ANALOG_VOLTAGE_INPUT_CHANNEL		CHANNEL_UNUSED
#define ANALOG_RSSI_INPUT_CHANNEL			CHANNEL_UNUSED

// RSSI - RC Receiver signal strength
#define RSSI_MIN_SIGNAL_VOLTAGE				0.5		// Voltage when RSSI should show 0%
#define RSSI_MAX_SIGNAL_VOLTAGE				3.3		// Voltage when RSSI should show 100%


////////////////////////////////////////////////////////////////////////////////
// Control gains.
// All gains should be positive real numbers.

// SERVOSAT limits servo throw by controlling pulse width saturation.
// set it to 1.0 if you want full servo throw, otherwise set it to the portion that you want
#define SERVOSAT							1.0



////////////////////////////////////////////////////////////////////////////////
// Debugging defines

// The following can be used to do a ground check of stabilization without a GPS.
// If you define TestGains, stabilization functions
// will be enabled, even without GPS or Tx turned on. (Tx is optional)
// #define TestGains						// uncomment this line if you want to test your gains without using GPS

// Set this to 1 to calculate and print out free stack space
#define RECORD_FREE_STACK_SPACE 			0

