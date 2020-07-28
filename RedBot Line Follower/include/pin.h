/*
 * pin.h
 *
 * Created: 22-Apr-19 3:05:17 PM
 *  Author: BTone
 */ 


#ifndef PIN_H_
#define PIN_H_

#include <stdint.h>

typedef union {
	uint8_t reg;
	struct {
		uint8_t b0: 1;
		uint8_t b1: 1;
		uint8_t b2: 1;
		uint8_t b3: 1;
		uint8_t b4: 1;
		uint8_t b5: 1;
		uint8_t b6: 1;
		uint8_t b7: 1;
		};
} BIT_REG;


#endif /* PIN_H_ */