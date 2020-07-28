#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include "Sensor.h"
#include "Control.h"
#include "Motor.h"
#include "hardwareConfiguration.h"
#include "Timer.h"
#include "BNO.h"

/* Definitions */
#define MAX_SPEED_L		1.0
#define MAX_SPEED_R		0.975
#define TARGET_DTHETA   1.75

#define KP	0.1

/* Static Variables */
static BNO_DATA bno_data;
static double error = 0;
static double last_error = 0;
static double heading = 0;
static double last_heading = 0;
static double dheading = 0;
static double speed = 0;

/* Function Definitions */
void PID_Loop() {
	/* Get heading */
	last_heading = heading;
	heading = BNO_GetHeading();
	dheading = heading - last_heading;
	if (abs(dheading) > 180)
		dheading = 0;
	
	/* Calculate Error */
	last_error = error;	// Last error
	// If error < 0, need tighter circle
	// If error > 0, need bigger circle
	error = TARGET_DTHETA - dheading;
	speed = KP * error;
	
	/* Set L/R motor speed
	 * Error > 0 when we need to turn right
	 * Error < 0 when we need to turn left */
	Motor_SetDuty(MAX_SPEED_L, MAX_SPEED_R - speed);
	
	//printf("error: %f\n"
	//		"Heading: %f\n"
	//		"Delta Heading: %f\n\n", error, heading, dheading);
	//BNO_GetData(&bno_data);
	//BNO_PrintData(&bno_data);
}