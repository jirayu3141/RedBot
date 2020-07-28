/* Includes */
#include <avr/interrupt.h>
#include "hardwareConfiguration.h"
#include "Motor.h"

/* Define */
#define DUTY_MIN	0.0

/* Static Variables */
static MOTOR_STATE state = MOTOR_STOP;
static float motor_duty[2] = {0};

/* Function Definitions */
void Motor_Init() {
	/* Configure Pin Directions */
	// Port B
	DDRB |= R_CTRL_1;
		
	// Port D
	DDRD |= L_CTRL_1 | L_CTRL_2 | R_CTRL_1 | PWML | PWMR;
	
	/* Setup Timer0 for Left Motor PWM */
	// 1kHz period
	TCCR0A	= 0b11;	// Fast-PWM Mode
	TCCR0B	= 0b1011;	// Fast-PWM, 64 Prescaler
	OCR0A	= 250 - 1;		// Compare A value (500 * 4us = 1Khz)
	OCR0B	= 0;
	TIMSK0 = 0b110;
	
	/* Setup Timer2 for Right Motor PWM */
	// 1kHz period
	TCCR2A	= 0b11;		// Fast-PWM Mode
	TCCR2B	= 0b1100;	// Fast-PWM, 64 Prescaler
	OCR2A	= 250 - 1;	// Compare A value (500 * 4us = 1Khz)
	OCR2B	= 0;
	TIMSK2 = 0b110;
}

float* Motor_GetDuty() {
	return motor_duty;
}

void Motor_SetDuty(float left, float right) {
	/* Left Motor */
	if (left >= 1.0) {
		OCR0B = OCR0A + 1;
		left = 1.0;
	} else if (left <= 0.0) {
		left = 0.0;
		OCR0B = 0;
	} else {
		OCR0B	= (uint16_t) (left * (1 + OCR0A) - 1);	
	}
	
	/* Right Motor */
	if (right >= 1.0) {
		OCR2B = OCR2A + 1;
		right = 1.0;
	} else if (right <= 0.0) {
		right = 0.0;
		OCR2B	= 0;
	} else {
		OCR2B	= (uint16_t) (right * (1 + OCR2A) - 1);
	}
	 
	 /* Update Duty */
	 motor_duty[0] = left;
	 motor_duty[1] = right;
	 
}

void Motor_SetDutyDelta(float leftDelta, float rightDelta) {
	Motor_SetDuty(motor_duty[0] + leftDelta, motor_duty[1] + rightDelta);
}

void Motor_SetMode(MOTOR_STATE mode) {
	switch (mode) {
		case MOTOR_FORWARD:
			/* Left */
			PORTD &= ~(L_CTRL_1);
			PORTD |= L_CTRL_2;
			/* Right */
			PORTB |= R_CTRL_2;
			PORTD &= ~(R_CTRL_1);
			break;
			
		case MOTOR_REVERSE:
			/* Left */
			PORTD |= L_CTRL_1;
			PORTD &= ~(L_CTRL_2);
			/* Right */
			PORTD |= R_CTRL_1;
			PORTB &= ~(R_CTRL_2);
			break;
			
		case MOTOR_STOP:
			PORTD = 0;
			PORTB &= ~(R_CTRL_2);
			break;
	}
	state = mode;
}

ISR (TIMER0_COMPA_vect) {
	PORTD |= PWML;
}

ISR (TIMER0_COMPB_vect) {
	PORTD &= ~PWML;
}

ISR (TIMER2_COMPA_vect) {
	PORTD |= PWMR;
}

ISR (TIMER2_COMPB_vect) {
	PORTD &= ~PWMR;
}