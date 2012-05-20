#ifndef HILSIM_H
#define HILSIM_H


int HILSIM_bodyrates_len(void);
void HILSIM_bodyrates_data(int index, char data);
void HILSIM_read_gyro(int* omegagyro);
void HILSIM_read_accel(int* gplane);

void HILSIM_send_outputs( void );
void HILSIM_commit_bodyrate_data( void );


#endif // HILSIM_H
