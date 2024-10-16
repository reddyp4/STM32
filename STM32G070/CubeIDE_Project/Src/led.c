#include "stm32g0xx_hal.h"
#include "led.h"

/* Setup LED as GPIO output */
void pa5_led_init()
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    //1. LED=PA5 as output
    GPIO_InitTypeDef GPIO_InitStruct={
        LED_PIN,  //Pin
        GPIO_MODE_OUTPUT_PP,  //Mode
        GPIO_NOPULL,  //Pull
        GPIO_SPEED_FREQ_LOW,  //Speed
        0,  //Alternate
        };
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
}
