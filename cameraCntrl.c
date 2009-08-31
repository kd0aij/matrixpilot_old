#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

// Basic camera stabilization control.
// Adjust the camera roll/pitch/yaw gains in controlGains.h.
// We may need to also take the rotational velocities into account.
// After getting stabilization working, look into aiming the camera at a specific location on the ground.


long lpFilteredCameraYawControl = 0 ;


void cameraCntrl( void )
{
#if ( USE_CAMERA_STABILIZATION == 1 )

	union longww cam ;
	
	
	// Adjust the roll of the camera proportionally to the current roll of the plane
	cam.WW = REVERSE_IF_NEEDED(CAMERA_ROLL_CHANNEL_REVERSED, __builtin_mulss( rmat[6] , CAMERA_ROLLKP_RM )) ;
	pwOut[CAMERA_ROLL_OUTPUT_CHANNEL] = pulsesat(3000 - cam._.W1) ;
	
	
	// Adjust the pitch of the camera proportionally to the current pitch of the plane
	cam.WW = REVERSE_IF_NEEDED(CAMERA_PITCH_CHANNEL_REVERSED, __builtin_mulss( rmat[7] , CAMERA_PITCHKP_RM )) ;
	pwOut[CAMERA_PITCH_OUTPUT_CHANNEL] = pulsesat(3000 - cam._.W1) ;
	
	
	// High pass filter the current yaw of the plane, and adjust the yaw of the camera proportionally to that
	// Bill or Pete, maybe you can improve this filtering...
	cam.WW = __builtin_mulss( rmat[1] , CAMERA_YAWKP_RM ) ;
	lpFilteredCameraYawControl -= lpFilteredCameraYawControl >> 5 ;
	lpFilteredCameraYawControl += cam._.W1 >> 5 ;
	long hpFilteredCameraYawControl = (long)cam._.W1 - lpFilteredCameraYawControl ;
	pwOut[CAMERA_YAW_OUTPUT_CHANNEL] = pulsesat(3000 - REVERSE_IF_NEEDED(CAMERA_YAW_CHANNEL_REVERSED, hpFilteredCameraYawControl)) ;

#endif
}
