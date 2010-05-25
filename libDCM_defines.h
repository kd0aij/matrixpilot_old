#ifndef DCM_DEFINES_H
#define DCM_DEFINES_H

// Types
struct waypoint2D { long x ; long y ; } ;
struct waypoint3D { long x ; long y ; int z ; } ;
struct waypointDef { struct waypoint3D loc ; int flags ; struct waypoint3D viewpoint ; } ;
struct velocity3D { int x ; int y ; int z ; } ;


// Defines
// GPS Type
#define GPS_STD				1
#define GPS_UBX_2HZ			2
#define GPS_UBX_4HZ			4

#define GPS_RATE			GPS_TYPE //Hah hah, this works for now

// If GPS data has not been received for this many state machine cycles, consider the GPS lock to be lost.
#define GPS_DATA_MAX_AGE	9

#define LONGDEG_2_BYTECIR 305 // = (256/360)*((256)**4)/(10**7)
#define COURSEDEG_2_BYTECIR 466 // = (256/360)*((256)**2)/(10**2)

#endif
