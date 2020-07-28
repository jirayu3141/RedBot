#include <stdlib.h>
#include <stdio.h>
#include "Sensor.h"
#include "ADC.h"
#include "hardwareConfiguration.h"

/* Global Variables */
SENSOR_DATA _sensors_current = {0};
SENSOR_DATA _sensors_last = {0};

/* Function Definitions */
void Sensors_Read() {
	// ADC0 - Left
	// ADC1 - Mid
	// ADC2 - Right
	ADC_SetChannel(ADC0);
	_sensors_current.voltages[0] = ADC_ReadVoltage();
	ADC_SetChannel(ADC1);
	_sensors_current.voltages[1] = ADC_ReadVoltage();
	ADC_SetChannel(ADC2);
	_sensors_current.voltages[2] = ADC_ReadVoltage();
	
	_sensors_last = _sensors_current;
	
	if (_sensors_current.voltages[0] >= VOLTAGE_THRESHOLD)
		_sensors_current.left = 1;
	else
		_sensors_current.left = 0;
		
	if (_sensors_current.voltages[1] >= VOLTAGE_THRESHOLD)
		_sensors_current.mid = 1;
	else
		_sensors_current.mid = 0;
	
	if (_sensors_current.voltages[2] >= VOLTAGE_THRESHOLD)
		_sensors_current.right = 1;
	else
		_sensors_current.right = 0;
}

void Sensors_Print() {
	static char temp[5];
	for (int i = 0; i < 3; i++) {
		dtostrf(_sensors_current.voltages[i], 5, 2, temp);
		printf("Voltage %u: %s\n", i, temp);
	}
	puts("");
}