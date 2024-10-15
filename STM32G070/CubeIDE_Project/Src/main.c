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

#define BUTTON_AS_INTERRUPT     1   /* 0=Manual input, 1=interrupt */

void pc13_btn_init(void);
void pa5_led_init(void);
void gpio_pc13_interrupt_init(void);

int counter;
uint8_t buttonStatus;
char message[20] = "Hello from STM32\n";
uint32_t sensor_value;

int main()
{
    HAL_Init(); //Initialize all HAL

    /* Commented out for setting up as an interrupt driven LED */
    if(BUTTON_AS_INTERRUPT==0)
    {
        pa5_led_init(); //Initialize LED
        pc13_btn_init();    //Initialize Button*/
    }
    else
    {
        gpio_pc13_interrupt_init();     /* Interrupt based LED/GPIO */
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
        printf("Using printf\n");
        //HAL_Delay(20);

        /* ADC MODULE*/
        sensor_value = pa0_adc_read();
        counter++;
    }
}

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

void gpio_pc13_interrupt_init()
{
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /* PC13 Button in interrupt mode */
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = BTN_PIN;  /* PC13 */
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; /* Mode: Interrupt */
    GPIO_InitStruct.Pull = GPIO_NOPULL; /* No Pull */
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; /* Low Speed */
    HAL_GPIO_Init(BTN_PORT, &GPIO_InitStruct);

    /* Configure LED - PA5 as output */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = LED_PIN;   /* PA5 */
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; /* Output Push-pull */
    GPIO_InitStruct.Pull = GPIO_NOPULL; /* No Pull */
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; /* Low Speed */
    HAL_GPIO_Init(LED_PORT,&GPIO_InitStruct);

    /* Set up Interrupt EXTI in NVIC */
    HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}

/* Callback for the Interrupt, as per  HAL_GPIO_EXTI_IRQHandler */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
    /* Toggle the LED */
    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
}

/* ISR called by Interrupt line 15
    Name as per the start-up file .s */
void EXTI4_15_IRQHandler(void)
{
    /* When rising edge detected, this IRQ is serviced */
    HAL_GPIO_EXTI_IRQHandler(BTN_PIN);
}
