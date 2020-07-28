#ifndef MOTOR_H_
#define MOTOR_H_

/* Type Definitions */
typedef enum {
	MOTOR_STOP = 0,
	MOTOR_FORWARD,
	MOTOR_REVERSE
} MOTOR_STATE;

/* Function Prototypes */
void Motor_Init();
void Motor_SetDuty(float left, float right);
void Motor_SetDutyDelta(float leftDelta, float rightDelta);
void Motor_SetMode(MOTOR_STATE mode);
float* Motor_GetDuty();

#endif /* MOTOR_H_ */