#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Timer.h"

/* Static Variables */
static TIMER timers[NUM_TIMERS] = {0};
static TIMER* timer_head = timers;
static uint64_t ticks = 0;

/* Body */
void Timer_Init() {
	/* Setup Timer1 (For software timers) */
	TCCR1A	= 0b00;			// CTC mode
	TCCR1B	= 0b01011;		// 64 Prescaler (4us interval)
	OCR1A	= 250 - 1;		// Compare A value (250 * 4us = 1ms)
	TIMSK1 = 0b010;			// OCA Enable
}

TIMER* Timer_Add(TIMERFUNC func, uint64_t timeout) {
	if (timer_head - timers >= NUM_TIMERS)
		return NULL;
	
	TIMER* timer = timer_head;	
	timer_head->func = func;
	timer_head->state = TIMER_RUNNING;
	timer_head->tick = 0;
	timer_head->timeout = timeout;
	
	timer_head++;
	
	return timer;
}

void Timer_Manager() {
	// Update timers
	uint64_t cur_ticks = ticks;
	for (int i = 0; i < NUM_TIMERS; i++) {
		if (timers[i].state == TIMER_RUNNING) {
			timers[i].tick += cur_ticks;
			
			// Check if expired
			uint64_t tick = timers[i].tick;
			// Check for timeout
			if (tick >= timers[i].timeout) {
				
				if (timers[i].func != NULL)
					timers[i].func();
					
				timers[i].tick -= timers[i].timeout;
			}
		}
	}
	ticks -= cur_ticks;
}

ISR (TIMER1_COMPA_vect) {
	ticks++;
}