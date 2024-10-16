#include "stm32g0xx_hal.h"
#include "exti.h"
#include "led.h"

void gpio_pc13_interrupt_init()
{
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /* PC13 Button in interrupt mode */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = BTN_PIN;  /* PC13 */
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING; /* Mode: Interrupt */
    GPIO_InitStruct.Pull = GPIO_NOPULL; /* No Pull */
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; /* Low Speed */
    GPIO_InitStruct.Alternate = 0;
    HAL_GPIO_Init(BTN_PORT, &GPIO_InitStruct);

    /* Configure LED - PA5 as output */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = LED_PIN;   /* PA5 */
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; /* Output Push-pull */
    GPIO_InitStruct.Pull = GPIO_NOPULL; /* No Pull */
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; /* Low Speed */
    HAL_GPIO_Init(LED_PORT,&GPIO_InitStruct);

    /* Configure PA0 for ADC for multiple interrupts */
    /*
    GPIO_InitStruct.Pin = GPIO_PIN_0;   // PA0
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING; // Output Push-pull
    GPIO_InitStruct.Pull = GPIO_NOPULL; // No Pull
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Low Speed 
    HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI015_IRQn);
    */

    /* Set up Interrupt EXTI in NVIC */
    HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}


/* Callback for the Interrupt, as per  HAL_GPIO_EXTI_IRQHandler */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin==BTN_PIN)
    {
        /* Toggle the LED */
        HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
        printf("User button pressed\n");
    }
    else if (GPIO_Pin==GPIO_PIN_0)
    {
        // Toggle the LED
        printf("PA0 button pressed\n");
    }
}


/* ISR called by Interrupt line 15
    Name as per the start-up file .s */
void EXTI4_15_IRQHandler(void)
{
    /* When rising edge detected, this IRQ is serviced */
    HAL_GPIO_EXTI_IRQHandler(BTN_PIN);
}

/* Used in muliple interrupt  */
void EXTI0_IRQHandler(void)
{
    /* Second Interrupt, on PA0, same handler */
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}