// In M0, IOPORT, while in F4 it is clock access
// BTN=PC12, Bus=AHB1, RCC_IOPENR, bit 2
// LED=PA5, Bus=AHB1, RCC_IOPENR, bit 0
#include "stm32g070xx.h"
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_gpio.h"

#define LED_PORT    GPIOA
#define LED_PIN     GPIO_PIN_5
#define BTN_PORT    GPIOC
#define BTN_PIN     GPIO_PIN_12

void pc12_btn_init();
void pa5_led_init();

int counter;
uint8_t buttonStatus;

int main()
{
    HAL_Init(); //Initialize all HAL
    pa5_led_init(); //Initialize LED
    pc12_btn_init();    //Initialize Button
    while(1)
    {
        //Read button state and 
        buttonStatus = HAL_GPIO_ReadPin(GPIOC,BTN_PORT);
        HAL_GPIO_WritePin(GPIOA,LED_PORT,buttonStatus);
        counter++;
    }
}

void pa5_led_init()
{
    //1. LED=PA5 as output
    GPIO_InitTypeDef GPIO_InitStruct={
        LED_PIN,  //Pin
        GPIO_MODE_OUTPUT_PP,  //Mode
        GPIO_NOPULL,  //Pull
        GPIO_SPEED_FREQ_LOW,  //Speed
        0,  //Alternate
        };
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void pc12_btn_init()
{
    //1. BTN=PC12 as input
    GPIO_InitTypeDef GPIO_InitStruct={
        BTN_PORT,  //Pin
        GPIO_MODE_INPUT,  //Mode
        GPIO_NOPULL,  //Pull
        GPIO_SPEED_FREQ_LOW,  //Speed
        0,  //Alternate
        };
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void SysTick_Handler(void)
{
    //Increment the clock
    HAL_IncTick();  //Update tick based on clock
}