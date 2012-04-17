#ifndef DEADRECON_H
#define DEADRECON_H


#define IMUheight IMUlocationz._.W1

// velocity, as estimated by the IMU
extern union longww IMUvelocityx ;
extern union longww IMUvelocityy ;
extern union longww IMUvelocityz ;

// location, as estimated by the IMU
extern union longww IMUlocationx ;
extern union longww IMUlocationy ;
extern union longww IMUlocationz ;

extern unsigned int air_speed_3DIMU ;

extern int total_energy; ;
extern int errorYawground[] ;


void dead_reckon(void);


#endif // DEADRECON_H
