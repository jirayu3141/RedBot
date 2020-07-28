#ifndef TIMER_H_
#define TIMER_H_

/* Definitions */
#define NUM_TIMERS 3

/* Type Definitions */
typedef void (*TIMERFUNC)(void);

typedef enum {
	TIMER_NONE = 0,
	TIMER_STOPPED,
	TIMER_RUNNING,
	TIMER_TIMEOUT
} TIMER_STATE;

typedef struct {
	uint64_t tick;
	uint64_t timeout;
	TIMER_STATE state;
	TIMERFUNC func;
} TIMER;

/* Function Prototypes */
void Timer_Init();
TIMER* Timer_Add(TIMERFUNC func, uint64_t timeout);
void Timer_Start(TIMER* timer);
void Timer_Reset(TIMER* timer);
void Timer_Manager();

#endif /* TIMER_H_ */