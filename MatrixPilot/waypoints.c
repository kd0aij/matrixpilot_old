#include "p30f4011.h"
#include "definesRmat.h"
#include "defines.h"

struct waypoint3D GPSlocation = { 0 , 0 , 0 } ;
struct waypoint3D GPSvelocity = { 0 , 0 , 0 } ;

#include "waypoints.h"

#define NUMBERPOINTS (( sizeof waypoints ) / sizeof ( struct waypointDef ))

int waypointIndex = 0 ;							
struct waypointparameters goal ;
struct relative2D togoal = { 0 , 0 } ;
int tofinish  = 0 ;
int progress_to_goal = 0 ;
int crosstrack = 0 ;
signed char desired_dir_waypoint = 0 ;

extern signed char bearing_to_origin ;


#if ( WAYPOINT_TYPE == WP_ABSOLUTE )
// If using absolute waypoints, ABS_TO_REL_IF_NEEDED() is a function that converts 
// a waypoint from absolute to relative.
struct waypoint3D ABS_TO_REL_IF_NEEDED(struct waypoint3D wp)
{
	union longww accum_nav;
	
	wp.y = (wp.y - lat_origin.WW)/90 ; // in meters
	
	accum_nav.WW = ((wp.x - long_origin.WW)/90) ; // in meters
	accum_nav.WW = ((__builtin_mulss ( cos_lat , accum_nav._.W0 )<<2)) ;
	wp.x = accum_nav._.W1 ;
	
	return wp;
}

#elif ( WAYPOINT_TYPE == WP_RELATIVE )
// If using relative waypoints, ABS_TO_REL_IF_NEEDED() is a macro that just
// passes the relative waypoint through unchanged.
#define ABS_TO_REL_IF_NEEDED(x) (x)
#endif


void set_goal( struct waypoint3D fromPoint , struct waypoint3D toPoint )
{
	struct relative2D courseLeg ;
	goal.x = toPoint.x ;
	goal.y = toPoint.y ;
	goal.height = toPoint.z ;
	goal.fromHeight = fromPoint.z ;
	courseLeg.x = toPoint.x - fromPoint.x ;
	courseLeg.y = toPoint.y - fromPoint.y ;
	goal.phi = rect_to_polar ( &courseLeg ) ;
	goal.legDist = courseLeg.x ;
	goal.cosphi = cosine( goal.phi ) ;
	goal.sinphi = sine( goal.phi ) ;
	return ;
}

void init_waypoints ( void )
{
	waypointIndex = 0 ;
	set_goal( GPSlocation , ABS_TO_REL_IF_NEEDED(waypoints[0].loc) ) ;
	desired_behavior.W = waypoints[0].flags ;
	return ;
}

void compute_waypoint ( void )
{
	union longww temporary ;
	// compute the goal vector from present position to waypoint target in meters:
	
	togoal.x =  goal.x  - GPSlocation.x  ;
	togoal.y =  goal.y  - GPSlocation.y  ;
	
	// project the goal vector onto the direction vector between waypoints
	// to get the distance to the "finish" line:
	
	temporary.WW = (	__builtin_mulss( togoal.x , goal.cosphi )
				+ __builtin_mulss( togoal.y , goal.sinphi ))<<2 ;
	
	tofinish = temporary._.W1 ;
	
#if ( USE_CROSSTRACKING == 1 )
	
	// project the goal vector perpendicular to the desired direction vector
	// to get the crosstrack error
	
	temporary.WW = ( __builtin_mulss( togoal.y , goal.cosphi )
				   - __builtin_mulss( togoal.x , goal.sinphi ))<<2 ;
	
	crosstrack = temporary._.W1 ;
	
	// crosstrack is measured in meters
	// angles are measured as an 8 bit signed character, so 90 degrees is 64 binary.
	
	if ( crosstrack > 32 )  // more than 32 meters to the right, steer 45 degrees to the left
	{
		desired_dir_waypoint = goal.phi + 32 ; // 45 degrees maximum
	}
	else if ( crosstrack < -32 ) // more than 32 meters to the left, steer 45 degrees to the right
	{
		desired_dir_waypoint = goal.phi - 32 ; // -45 degress minimum
	}
	else  // within 32 meters of the desired track, steer in proportion to the cross track error
	{
		desired_dir_waypoint = goal.phi + crosstrack ;
	}
#else
	desired_dir_waypoint = rect_to_polar ( & togoal ) ;
#endif
}


void next_waypoint ( void ) 
{
	union longww temporary ;
	
	if ( desired_behavior._.loiter )
	{
		set_goal( GPSlocation , ABS_TO_REL_IF_NEEDED(waypoints[waypointIndex].loc) ) ;
	}
	else
	{
		waypointIndex++ ;
		
		if ( waypointIndex >= NUMBERPOINTS ) waypointIndex = 0 ;
		
		if ( waypointIndex == 0 )
		{
			if (NUMBERPOINTS > 1)
			{
				set_goal( ABS_TO_REL_IF_NEEDED(waypoints[NUMBERPOINTS-1].loc),
							ABS_TO_REL_IF_NEEDED(waypoints[0].loc) ) ;
			}
			else
			{
				set_goal( GPSlocation , ABS_TO_REL_IF_NEEDED(waypoints[0].loc) ) ;
			}
			desired_behavior.W = waypoints[0].flags ;
		}
		else
		{
			set_goal( ABS_TO_REL_IF_NEEDED(waypoints[waypointIndex-1].loc),
						ABS_TO_REL_IF_NEEDED(waypoints[waypointIndex].loc) ) ;
			desired_behavior.W = waypoints[waypointIndex].flags ;
		}
	}
	
	compute_waypoint() ;
	return ;
}


void processwaypoints(void)
{
	if ( gps_nav_valid() && (flags._.use_waypoints == 1) )
	{
		// steering is based on cross track error.
	 	// waypoint arrival is detected computing distance to the "finish line".
		
		// note: locations are measured in meters
		//		 velocities are in centimeters per second
		
		// locations have a range of +-32000 meters (20 miles) from origin
		
		compute_waypoint() ;
		
#if ( USE_CROSSTRACKING == 1 )
		if ( tofinish < WAYPOINT_RADIUS ) next_waypoint() ; // crossed the finish line
#else
		if (( tofinish < WAYPOINT_RADIUS )|| ( togoal.x < WAYPOINT_RADIUS)) next_waypoint() ; // crossed the finish line
#endif
	}
	
	if ( flags._.use_waypoints == 1 )
	{
		desired_dir = desired_dir_waypoint ;
		
		if (goal.legDist > 0)
		{
			// progress_to_goal is the fraction of the distance from the start to the finish of
			// the current waypoint leg, that is still remaining.  it ranges from 0 - 1<<12.
			progress_to_goal = (((long)goal.legDist - tofinish + velocity_magnitude/100)<<12) / goal.legDist ;
			if (progress_to_goal < 0) progress_to_goal = 0 ;
			if (progress_to_goal > (long)1<<12) progress_to_goal = (long)1<<12 ;
		}
		else
		{
			progress_to_goal = (long)1<<12 ;
		}
	}
	else
	{
		desired_dir = bearing_to_origin ;
		progress_to_goal = 0 ;
	}
	return ;
}


