#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "Timer.h"

/* Static Variables */
static TIMER* timer_head = NULL;
static TIMER* timer_tail = NULL;
static uint64_t ticks = 0;

/* Function Definitions */
void Timer_Init() {
	/* Setup Timer1 (For software timers) */
	TCCR1A = 0b00;			// CTC mode
	TCCR1B = 0b01011;		// 64 Prescaler (4us interval)
	OCR1A = 250 - 1;		// Compare A value (250 * 4us = 1ms)
	TIMSK1 = 0b010;			// OCA INT Enable
}

void Timer_Add(TIMER* timer, uint64_t timeout, TIMERFUNC func) {
	/* If first timer, make head of list */	
	if (timer_head == NULL)
		timer_head = timer;
	
	/* Initialize Timer */
	timer->func = func;
	timer->tick = 0;
	timer->timeout = timeout;
	timer->next = NULL;
	
	/* Last timer points to this timer */
	if (timer_tail != NULL)
		timer_tail->next = timer;
	timer_tail = timer;
}

uint64_t Timer_GetSysTick() {
	return ticks;
}

void Timer_Manager() {
	static TIMER* timer;
	static uint64_t cur_tick;
	
	/* Update timers */
	timer = timer_head;
	while (timer != NULL) {
		/* Save current tick */
		cur_tick = ticks;
		
		/* Check if timer has expired */
		if (cur_tick - timer->tick >= timer->timeout) {
			timer->tick = cur_tick;		// Update timer's last timeout tick
			
			/* Run timer function */
			if (timer->func != NULL)
				timer->func();
		}
		
		/* Process next timer */
		timer = timer->next;
	}
}

ISR (TIMER1_COMPA_vect) {
	ticks++;
}