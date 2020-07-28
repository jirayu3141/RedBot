/* ECE 3411 
 * UConn - Spring 2019
 * RedBot Racer - 'BigPID'
 * By Brandon D'Agostino & Jirayu 'Peter' Sirivorawong */

/* Definitions */
#define PID_INTERVAL	10

#define F_CPU 16E6

/* Includes */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "hardwareConfiguration.h"
#include "Motor.h"
#include "Timer.h"
#include "uart.h"
#include "Sensor.h"
#include "ADC.h"
#include "Control.h"
#include "i2c_master.h"
#include "BNO.h"

/* Static Variables */
static TIMER PID_timer;
//static TIMER print_timer;
static BNO_DATA bno_data = {0};

/* Function Prototypes */
void GPIO_Init();

/* Function Definitions */
int main(void)
{
	/* Initialize Everything */
	Timer_Init();
	GPIO_Init();
	Motor_Init();
	uart_init();
	ADC_Init();
	i2c_init();
	sei();
	
	/* Probe and setup BNO */
	if (BNO_Probe()) {
		puts("Restarting...");
		return 1;
	}
	_delay_ms(20);
	BNO_SetIMU();
	_delay_ms(20);
	BNO_CalibrateEuler();
	
	/* Add Tasks */
	Timer_Add(&PID_timer, PID_INTERVAL, PID_Loop);
	
	/* Start Motors */
	Motor_SetMode(MOTOR_FORWARD);
	
	/* Main Loop (Elegance is ...) */
    while (1) {
		Sensors_Read();
		Timer_Manager();
	}
}

void GPIO_Init() {
	// D13 LED (PB5)
	DDRB |= (1 << DDB5);
}