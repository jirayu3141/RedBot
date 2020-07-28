/* Includes */
#include <avr/io.h>

/* Function Definitions */
void ADC_Init(void) {
	// The Power Reduction ADC bit in the Power Reduction Register (PRR0.PRADC) must be written to '0' in order to enable the ADC.
	//PRR0 = (0 << PRADC);
	
	ADCSRA = 0b011;			// 128x prescaler
	ADCSRA |= (1 << ADEN);	// Enable
}

void ADC_SetChannel(uint8_t channel) {
	ADMUX = 0b01000000 | channel;
}

unsigned int ADC_ReadRaw(void) {
	// Start conversion
	ADCSRA |= (1 << ADSC);
	
	// Wait until conversion finished
	loop_until_bit_is_clear(ADCSRA, ADSC);
	
	return ADC;
}

double ADC_ReadVoltage(void) {
	unsigned int raw = ADC_ReadRaw();
	return raw * (5.0/1024);
}