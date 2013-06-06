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
// Waypoint handling

// Move on to the next waypoint when getting within this distance of the current goal (in meters)
#define WAYPOINT_RADIUS 		5

// Origin Location
// When using relative waypoints, the default is to interpret those waypoints as relative to the
// plane's power-up location.  Here you can choose to use any specific, fixed 3D location as the
// origin point for your relative waypoints.
//
// USE_FIXED_ORIGIN should be 0 to use the power-up location as the origin for relative waypoints.
// Set it to 1 to use a fixed location as the origin, no matter where you power up.
// FIXED_ORIGIN_LOCATION is the location to use as the origin for relative waypoints.  It uses the
// format { X, Y, Z } where:
// X is Longitude in degrees * 10^7
// Y is Latitude in degrees * 10^7
// Z is altitude above sea level, in meters, as a floating point value.
// 
// If you are using waypoints for an autonomous landing, it is a good idea to set the altitude value
// to be the altitude of the landing point, and then express the heights of all of the waypoints with
// respect to the landing point.
// If you are using OpenLog, an easy way to determine the altitude of your landing point is to
// examine the telemetry after a flight, take a look in the .csv file, it will be easy to spot the
// altitude, expressed in meters.

////////////////////////////////////////////////////////////////////////////////
// This is an AVC lefthand course for takeoff to the west

#pragma message "avc lefthand course shifted to AAM east field, west X"

#define USE_FIXED_ORIGIN		1

// center of launch zone 40 4' 22.35"N 105 13' 48.88"W
//#define FIXED_ORIGIN_LOCATION	{ -1052302444, 400728750, 1587.7 }

// AAM East Field runway center 39°50'31.83"N  105°12'44.81"W
//#define FIXED_ORIGIN_LOCATION	{ -1052124472, 398421750, 1812.0 }

// AAM East Field runway west X
#define FIXED_ORIGIN_LOCATION	{ -1052136160, 398424410, 1812.0 }

// AAM East Field runway east X
//#define FIXED_ORIGIN_LOCATION	{ -1052112480,  39841910, 1812.0 }

// AAM West Field runway center  39°50'31.97"N  105°13'10.17"W (105.2194917, 39.842213889)
//#define FIXED_ORIGIN_LOCATION	{ -1052194917, 398422138, 1817.0 }

const struct waypointDef waypoints[] = {
	{ { 44, 10, 20 } , F_TAKEOFF , CAM_VIEW_LAUNCH } , //Waypoint 1
	{ { 58, 50, 35 } , F_CROSS_TRACK , CAM_VIEW_LAUNCH } , //Waypoint 2
	{ { -172, 330, 35 } , F_CROSS_TRACK , CAM_VIEW_LAUNCH } , //Waypoint 3
	{ { -101, 24, 35 } , F_CROSS_TRACK , CAM_VIEW_LAUNCH } , //Waypoint 4
	{ { -81, -14, 20 } , F_CROSS_TRACK , CAM_VIEW_LAUNCH } , //Waypoint 5
	{ { -44, -15, 10 } , F_CROSS_TRACK , CAM_VIEW_LAUNCH } , //Waypoint 6
	{ { 51, 19, -10 } , F_LAND , CAM_VIEW_LAUNCH } , //Waypoint 7
};


////////////////////////////////////////////////////////////////////////////////
// rtlWaypoints[]
// 
// This set of waypoints describes what to do when entering RTL mode.
// By default the only RTL waypoint is defined to be at the starting point, and to fly there unpowered.
// 
// Note that this set of waypoints is only used if FAILSAFE_TYPE is set to FAILSAFE_RTL in options.h.
// 
// WARNING: If you set this not to include the F_LAND flag, then be very careful during ground testing
// and after flights, since turning off the transmitter will cause the throttle to come on.

const struct waypointDef rtlWaypoints[] = {
		{ { 0, 0,  50 } , F_LOITER + F_LAND, CAM_VIEW_LAUNCH } ,
} ;




////////////////////////////////////////////////////////////////////////////////
// Example waypoint lists
//
// Here are more examples of waypoints lists, commented out.  Note that these are
// all definitions of waypoints[], and if you want to use any of these as rtl waypoints,
// you'll have to change them to define rtlWaypoints[] instead of waypoints[].



////////////////////////////////////////////////////////////////////////////////
// This is an example course that makes a 100 meter square, 75 meters above the starting point, and
// then takes a photo and lands.
// 
// We first go to the south east corner of the square.
// Then on to the north east corner.
// The plane then uses ailerons to flip upside down, and heads towards the north west corner.
// Then we flip back over and head back to the south west corner.  
// We then take a photo, turn off the motor and head towards the middle of the square.
// When we fly past the middle, we turn back towards the middle, still without throttle, over and over until "landing".
// 
// Note that this is not likely to be an especially smooth landing...

/*
const struct waypointDef waypoints[] = {
		{ { 100,   0  , 75 } , F_NORMAL,   CAM_VIEW_LAUNCH } ,
		{ { 100, 100  , 75 } , F_NORMAL,   CAM_VIEW_LAUNCH } ,
		{ {   0, 100  , 75 } , F_INVERTED, CAM_VIEW_LAUNCH } ,
		{ {   0,   0  , 75 } , F_NORMAL,   CAM_VIEW_LAUNCH } ,
		{ {  50,  50  , 75 } , F_LOITER + F_TRIGGER + F_LAND, CAM_VIEW_LAUNCH } ,
} ;
*/


////////////////////////////////////////////////////////////////////////////////
// DIY Drones T3-2 Course
// 
// As a more complex example, here is the DIY Drones T3-2 contest course
// 
// Prior to flight, initialize the board at the center of the course.

/*
// CORNER is the absolute value of the X or Y coordinate at the corners of the course. 
#define CORNER 100

// CLEARANCE is an allowance for obstacles.
#define CLEARANCE 25

#define CAM_VIEW_2  { CORNER, CORNER, 0 } // Define a Camera ViewPoint to look at 100 ,100, 0

// Here is the T3 course definition:

const struct waypointDef waypoints[] = {
		{ {    CORNER  ,    CORNER  , CLEARANCE + 100 } , F_NORMAL, CAM_VIEW_LAUNCH } ,
		{ {    CORNER  ,  - CORNER  , CLEARANCE +  75 } , F_NORMAL, CAM_VIEW_LAUNCH } ,
		{ {  - CORNER  ,    CORNER  , CLEARANCE +  50 } , F_NORMAL, CAM_VIEW_LAUNCH } ,
		{ {  - CORNER  ,  - CORNER  , CLEARANCE +  25 } , F_NORMAL, CAM_VIEW_LAUNCH } ,
		{ {    CORNER  ,    CORNER  , CLEARANCE +  50 } , F_NORMAL, CAM_VIEW_LAUNCH } ,
		{ {    CORNER  ,  - CORNER  , CLEARANCE +  75 } , F_NORMAL, CAM_VIEW_LAUNCH } ,
		{ {  - CORNER  ,    CORNER  , CLEARANCE + 100 } , F_NORMAL, CAM_VIEW_LAUNCH } ,
		{ {  - CORNER  ,  - CORNER  , CLEARANCE +  75 } , F_NORMAL, CAM_VIEW_2 } ,
		{ {    CORNER  ,    CORNER  , CLEARANCE +  50 } , F_NORMAL, CAM_VIEW_2 } ,
		{ {    CORNER  ,  - CORNER  , CLEARANCE +  25 } , F_NORMAL, CAM_VIEW_2 } ,
		{ {  - CORNER  ,    CORNER  , CLEARANCE +  50 } , F_NORMAL, CAM_VIEW_2 } ,
		{ {  - CORNER  ,  - CORNER  , CLEARANCE +  75 } , F_NORMAL, CAM_VIEW_2 } ,
} ;
*/
