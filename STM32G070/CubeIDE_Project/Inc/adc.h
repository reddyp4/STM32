#ifndef ADC_H_
#define ADC_H_

#include "stm32g0xx_hal.h"

/* Result of adc reading */
uint32_t pa0_adc_read(void);
void adc_continuous_conv_init();
void adc_init_start(void);
void adc_single_conv_init(void);
void adc_interrupt_init(void);

#endif  /* ADC_H_ */