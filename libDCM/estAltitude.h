#ifndef ESTALTITUDE_H
#define ESTALTITUDE_H


//extern signed char actual_altitude;
//extern signed char calculated_altitude;

void udb_barometer_callback(long pressure, int temperature, char status);
void estAltitude(void);


#endif // ESTALTITUDE_H
