
#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define TRIMPOT1      TRISA0
#define VREF 5.0   // tensão analógica máxima que corresponde ao maior código digital do A/D

void adc_init(void);
uint16_t adc_read(uint8_t canal);

#endif	

