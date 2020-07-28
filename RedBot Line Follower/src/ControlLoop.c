#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Sensor.h"
#include "ControlLoop.h"
#include "Motor.h"
#include "hardwareConfiguration.h"
#include <avr/io.h>
/* Definitions */
#define MAX_SPEED_L		1.0
#define MAX_SPEED_R		0.975
#define MAX_ERR			0.5

#define KP	1
#define KD	0.5

/* Static Variables */
static CONTROL_STATE state = STATE_INIT;
static CONTROL_STATE last_state = STATE_NONE;
static CONTROL_STATE next_state = STATE_NONE;
static float error = 0;
static float pre_error = 0;
static float speed = 0;


/* Function Definitions */
void Control_Loop() {
	/* Process sensor input and determine next state */
	pre_error = error;
	error = (_sensors_current.voltages[2] - _sensors_current.voltages[1]) - (_sensors_current.voltages[0] - _sensors_current.voltages[1]);
	
	switch (_sensors_current.combined) {
		case 0b000:	// All white
			error = pre_error;
			next_state = last_state;
			break;
			
		case 0b001:	// Right
			next_state = STATE_LEFT;
			break;
		
		case 0b010:	// Mid
			next_state = STATE_FORWARD;
			break;
		
		case 0b011:	// Right & Mid
			next_state = STATE_LEFT;
			break;
		
		case 0b100:	// Left
			next_state = STATE_RIGHT;
			break;
		
		case 0b101:	// Left & Right
			next_state = STATE_FORWARD;
			break;
		
		case 0b110:	// Left & Mid
			next_state = STATE_RIGHT;
			break;
		
		case 0b111:	// All
			error = pre_error;
			next_state = STATE_FORWARD;
			break;
	}
	
	speed = KP*error + KD*(error - pre_error);
		
	/* Process State Outputs/Actions */
	switch (state) {
		case STATE_INIT:
			Motor_SetMode(MOTOR_FORWARD);
			next_state = STATE_FORWARD;
			break;
			
		case STATE_FORWARD:
			Motor_SetDuty(MAX_SPEED_L, MAX_SPEED_R);
			break;
			
		case STATE_LEFT:
			Motor_SetDuty(MAX_SPEED_L, MAX_SPEED_R - speed);
			break;
			
		case STATE_RIGHT:
			Motor_SetDuty(MAX_SPEED_L + speed, MAX_SPEED_R);
			break;
			
		case STATE_STOP:
			Motor_SetMode(MOTOR_STOP);
			break;
		default:
			next_state = STATE_INIT;
			break;
	}
	#ifdef DEBUG_STATE
	char temp[10];
	dtostrf(error, 5, 2, temp);
	printf("Err: %s\n", temp);
	dtostrf(pre_error, 5, 2, temp);
	printf("PreErr: %s\n", temp);
	//printf("State = %u, Next = %u, last = %u, Sensors = %u\n", state, next_state, last_state, _sensors_current.combined);
	#endif
	last_state = state;
	state = next_state;
	
}