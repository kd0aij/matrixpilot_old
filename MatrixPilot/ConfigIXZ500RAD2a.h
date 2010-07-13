// used in Rusty's IXZ-500_RAD2a

#define	ADCON2CONFIG 0b0010010000011000 ; // Vref+ ref, scana ch0, int every 7, 16word, usa A only


#define	yrateBUFF	ADCBUF3 
#define	zrateBUFF	ADCBUF1
#define	xrateBUFF	ADCBUF2
#define	xaccelBUFF	ADCBUF4
#define	yaccelBUFF	ADCBUF5
#define	zaccelBUFF	ADCBUF6

#define XSIGN +
#define YSIGN +
#define ZSIGN -

//#define VREF

#define SCALEGYRO 4.95
#define SCALEACCEL 2.64
