#ifndef ADC_H_
#define ADC_H_

/* Definitions */
#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7
#define ADC8 8

/* Function Prototypes */
void ADC_Init(void);
unsigned int ADC_ReadRaw(void);
double ADC_ReadVoltage(void);
void ADC_SetChannel(uint8_t channel); 

#endif /* ADC_H_ */