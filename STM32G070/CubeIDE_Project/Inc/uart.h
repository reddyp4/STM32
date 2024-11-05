#ifndef UART_H_
#define UART_H_
#include "stm32g0xx_hal.h"

/* For interrupt */
#include "stm32g0xx_hal_usart.h"

void uart_hw_init(void);
void uart_init(void);
void uart_interrupt_init(void);
void uart_hw_interrupt_init(void);
void uart_dma_init(void);

#endif /* UART_H_ */
