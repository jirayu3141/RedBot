#ifndef HARDWARECONFIGURATION_H_
#define HARDWARECONFIGURATION_H_

//#define DEBUG_SENSOR_VOLTAGE
//#define DEBUG_STATE

/* Port B */
#define R_CTRL_2	(1 << 0)	// PB0

/* Port D */
#define L_CTRL_1	(1 << 2)	// PD2
#define L_CTRL_2	(1 << 4)	// PD4
#define R_CTRL_1	(1 << 7)	// PD7
#define PWML		(1 << 5)	// PD5
#define PWMR		(1 << 6)	// PD6

#endif /* HARDWARECONFIGURATION_H_ */