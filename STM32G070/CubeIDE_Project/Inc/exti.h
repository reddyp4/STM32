#ifndef EXTI_H_
#define EXTI_H_

#define BTN_PORT    GPIOC
#define BTN_PIN     GPIO_PIN_13


void gpio_pc13_interrupt_init(void);
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin);
void EXTI4_15_IRQHandler(void);
void EXTI0_IRQHandler(void);

#endif  /* EXTI_H_ */