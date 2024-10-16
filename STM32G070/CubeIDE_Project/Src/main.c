// In M0, IOPORT, while in F4 it is clock access
// BTN=PC13, Bus=AHB1, RCC_IOPENR, bit 3
// LED=PA5, Bus=AHB1, RCC_IOPENR, bit 0
// ADC=PA0, GPIOA, Input
//#include "stm32g070xx.h"
#include "stm32g0xx_hal.h"
#include "uart.h"
#include "adc.h"
#include "exti.h"
#include "led.h"
#include "tim.h"
#include <stdio.h>


#define BUTTON_AS_INTERRUPT     1   /* 0=Manual input, 1=interrupt */
#define ADC_CONTINUOUS_CONV     0   /* 0=Single Conversion, 1=Continuous conversion*/

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;


void pc13_btn_init(void);

int counter;
uint8_t buttonStatus;
char message[20] = "Hello from STM32\n";
uint32_t sensor_value;

int main()
{
    HAL_Init(); //Initialize all HAL
    tim_timebase_init();

    /* Commented out for setting up as an interrupt driven LED */
    if(BUTTON_AS_INTERRUPT==0)
    {
        pa5_led_init(); //Initialize LED
        pc13_btn_init();    //Initialize Button*/
    }
    else
    {
        gpio_pc13_interrupt_init();     // Interrupt based LED/GPIO
    }

    uart_init();       //USART initialization
    adc_init_start();     //ADC Initialization
    
    while(1)
    {
        /* GPIO MODULE */
        /* Read button state continuously */
        /* This is not needed when interrupt is used to commented out */
        if(BUTTON_AS_INTERRUPT==0)
        {
            buttonStatus = HAL_GPIO_ReadPin(BTN_PORT,BTN_PIN);
            HAL_GPIO_WritePin(LED_PORT,LED_PIN,buttonStatus);
        }

        /* UART transmit */
        /* Option1: HAL directly */
        //HAL_UART_Transmit(&huart2, (uint8_t *) message, 20, 100);
        /* Option2: use printf */
        //printf("Using printf\n");
        //HAL_Delay(20);

        if(ADC_CONTINUOUS_CONV==0)
        {
            //Single Conversion
            HAL_ADC_Start(&hadc1);
            //Start adc
            HAL_ADC_PollForConversion(&hadc1, 1);
            //Convert
            sensor_value = pa0_adc_read();
        }
        else
        {
            /* ADC MODULE*/
            sensor_value = pa0_adc_read();
        }
        counter++;
    }
}

/* Callback as per HAL_TIM_IRQHandler */
HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /**/
    printf("A second elapsed! \n\r");
}


/* Setup Button as GPIO input */
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
    HAL_GPIO_Init(BTN_PORT, &GPIO_InitStruct);
}

void SysTick_Handler(void)
{
    //Increment the clock
    HAL_IncTick();  //Update tick based on clock
}

