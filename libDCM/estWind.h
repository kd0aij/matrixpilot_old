#ifndef ESTWIND_H
#define ESTWIND_H


//#define WIND_X 0
//#define WIND_Y 1
//#define WIND_Z 2

//int getWind(int wind_vector);
//int estWind(int which);

extern int estimatedWind[3] ;			// wind velocity vectors in cm / sec

void estimateWind( void );


#endif // ESTWIND_H
