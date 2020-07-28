/* ECE 3411 
 * UConn - Spring 2019
 * RedBot Racer - 'BigPD'
 * By Brandon D'Agostino & Jirayu 'Peter' Sirivorawong */

/* Definitions */
#define CONTROL_INTERVAL	5

/* Includes */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "hardwareConfiguration.h"
#include "Motor.h"
#include "Timer.h"
#include "uart.h"
#include "Sensor.h"
#include "ADC.h"
#include "ControlLoop.h"

/* Static Variables */
static FILE uart_stream = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

/* Function Prototypes */
void GPIO_Init();

/* Function Definitions */
int main(void)
{
	/* Initialize Everything */
	sei();
	Timer_Init();
	GPIO_Init();
	Motor_Init();
	uart_init();
	ADC_Init();
	stdin = stdout = stderr = &uart_stream;
	puts("\x1B[2J");
	/* Add Tasks */
	Timer_Add(Control_Loop, CONTROL_INTERVAL);

    while (1) {
		Sensors_Read();		// Read sensors every loop. We want DATA.
		Timer_Manager();
		}
}

void GPIO_Init() {
	// D13 LED (PB5)
	DDRB |= (1 << DDB5);
	DDRB |= (1 << DDB4);
	PORTB |= (1<< PORTB4);
}