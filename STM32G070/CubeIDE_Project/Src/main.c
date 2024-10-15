// In M0, IOPORT, while in F4 it is clock access
// BTN=PC13, Bus=AHB1, RCC_IOPENR, bit 3
// LED=PA5, Bus=AHB1, RCC_IOPENR, bit 0
//#include "stm32g070xx.h"
#include "stm32g0xx_hal.h"
#include "uart.h"
#include "adc.h"
#include <stdio.h>

#define LED_PORT    GPIOA
#define LED_PIN     GPIO_PIN_5
#define BTN_PORT    GPIOC
#define BTN_PIN     GPIO_PIN_13

void pc13_btn_init(void);
void pa5_led_init(void);

int counter;
uint8_t buttonStatus;
char message[20] = "Hello from STM32\n";
uint32_t sensor_value;

int main()
{
    HAL_Init(); //Initialize all HAL
    pa5_led_init(); //Initialize LED
    pc13_btn_init();    //Initialize Button
    uart_init();       //USART initialization
    adc_init_start();     //ADC Initialization
    while(1)
    {
        /* GPIO MODULE */
        //Read button state and 
        buttonStatus = HAL_GPIO_ReadPin(BTN_PORT,BTN_PIN);
        HAL_GPIO_WritePin(LED_PORT,LED_PIN,buttonStatus);

        /* UART transmit */
        /* Option1: HAL directly */
        //HAL_UART_Transmit(&huart2, (uint8_t *) message, 20, 100);
        /* Option2: use printf */
        //printf("Using printf\n");
        //HAL_Delay(20);

        /* ADC MODULE*/
        sensor_value = pa0_adc_read();
        counter++;
    }
}

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
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void pc13_btn_init()
{
    __HAL_RCC_GPIOC_CLK_ENABLE();
    //1. BTN=PC12 as input
    GPIO_InitTypeDef GPIO_InitStruct={
        BTN_PIN,  //Pin
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



void adc_init()
{
    //ADC_HandleTypeDef ADC = {0};
    //ADC.Init
    //HAL_ADC_Init();
}
