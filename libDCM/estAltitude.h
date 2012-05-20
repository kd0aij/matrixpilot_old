#ifndef ESTALTITUDE_H
#define ESTALTITUDE_H


void udb_barometer_callback(long pressure, int temperature, char status);
void altimeter_calibrate(void);
void estAltitude(void);

long get_barometer_altitude(void);
long get_barometer_pressure(void);
int get_barometer_temperature(void);


#endif // ESTALTITUDE_H
