#ifndef TIMER_H_
#define TIMER_H_

/* Definitions */
#define NUM_TIMERS 3

/* Type Definitions */
typedef void (*TIMERFUNC)(void);

typedef struct timer_s TIMER;
struct timer_s {
	uint64_t tick;
	uint64_t timeout;
	TIMERFUNC func;
	struct timer_s* next;
};

/* Function Prototypes */
void Timer_Init();
void Timer_Add(TIMER* timer, uint64_t timeout, TIMERFUNC func);
void Timer_Manager();
uint64_t Timer_GetSysTick();

#endif /* TIMER_H_ */