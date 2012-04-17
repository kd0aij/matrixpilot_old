#ifndef MATLIBNAV_H
#define MATLIBNAV_H


int sine( signed char angle );
signed char arcsine( int y );
int cosine( signed char angle );
void rotate( struct relative2D *xy , signed char angle );
signed char rect_to_polar( struct relative2D *xy );
int rect_to_polar16( struct relative2D *xy );
unsigned int sqrt_int( unsigned int sqr );
unsigned int sqrt_long( unsigned long int sqr );
unsigned int vector2_mag( int x , int y );
unsigned int vector3_mag( int x , int y , int z );
unsigned int vector2_normalize( int result[] , int input[] );
unsigned int vector3_normalize( int result[] , int input[] );

 
#endif // MATLIBNAV_H
