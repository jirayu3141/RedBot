#ifndef CONTROLLOOP_H_
#define CONTROLLOOP_H_

/* Type Definitions */
typedef enum {
	STATE_NONE = 0,
	STATE_INIT = 1,
	STATE_FORWARD = 2,
	STATE_LEFT = 3,
	STATE_RIGHT = 4,
	STATE_STOP = 5,
	STATE_LITTLE_RIGHT = 6,
	STATE_LITTLE_LEFT = 7,
	STATE_OFF_TRACK= 8,
} CONTROL_STATE;


/* Function Prototypes */
void Control_Loop();

#endif /* CONTROLLOOP_H_ */