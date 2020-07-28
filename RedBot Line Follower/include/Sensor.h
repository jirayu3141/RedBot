#ifndef SENSOR_H_
#define SENSOR_H_

#define VOLTAGE_THRESHOLD	4.7

/* Includes */
#include <stdint.h>

/* Type Definitions */
typedef struct {
	float voltages[3];
	union {
		uint8_t	combined: 3;
		struct {
			uint8_t right: 1;
			uint8_t mid: 1;
			uint8_t left: 1;
		};
	};
} SENSOR_DATA;

/* Exposed Variables */
extern SENSOR_DATA _sensors_current;
extern SENSOR_DATA _sensors_last;

/* Function Prototypes */
void Sensors_Read();

#endif /* SENSOR_H_ */
