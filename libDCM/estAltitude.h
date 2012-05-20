#ifndef ESTALTITUDE_H
#define ESTALTITUDE_H


//extern signed char actual_altitude;
//extern signed char calculated_altitude;

void udb_barometer_callback(long pressure, int temperature, char status);
void estAltitude(void);

long get_barometer_pressure(void);
int get_barometer_temperature(void);


#endif // ESTALTITUDE_H
