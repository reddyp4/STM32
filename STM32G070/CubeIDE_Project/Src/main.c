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
#include "spi.h"


#define BUTTON_AS_INTERRUPT     2   /* 0=Manual input, 1=interrupt, 2=no LED, PA5 for SPI */
#define ADC_CONTINUOUS_CONV     4   /* 0=Single Conversion, 1=Continuous conversion
                                       2=Interrupt Driven
                                       3=DMA 
                                       4=No ADC*/
#define SPI_MODE    1   /* 0-polling, 1-interrupt, 2-dma*/

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern SPI_HandleTypeDef hspi2;

void pc13_btn_init(void);

int counter;
uint8_t buttonStatus;
char message[20] = "Hello from STM32\n";
uint32_t sensor_value_polled=0;
uint32_t sensor_value_conv=0;
uint32_t sensor_value_int=0;
uint32_t sensor_value_dma[1];
uint32_t sensor_SPI_polling=0;
uint32_t sensor_SPI_IT=0;
uint32_t time_Main=0;       /* Time for each main loop */
/* SPI Buffer */
uint8_t tx_buffer[10]={10,20,30,40,50,60,70,80,90,100};
uint8_t rx_buffer[10];

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    //ISR after tx/rx complete
    //do something
   //__HAL_SPI_ENABLE_IT(&hspi1, SPI_IT_RXNE);
   sensor_SPI_IT++;
   printf("Inside SPI Interrupt Callback!\n");
}

int main()
{
    HAL_Init(); //Initialize all HAL

    uart_init();       //USART initialization
    printf("Initiated UART!\n");

#if 0
    tim_timebase_init();

    /* Commented out for setting up as an interrupt driven LED */
    if(BUTTON_AS_INTERRUPT==0)
    {
        pa5_led_init(); //Initialize LED
        pc13_btn_init();    //Initialize Button*/
    }
    else if(BUTTON_AS_INTERRUPT==1)
    {
        gpio_pc13_interrupt_init();     // Interrupt based LED/GPIO
    }

    if(ADC_CONTINUOUS_CONV==0)
    {
        adc_single_conv_init(); //ADC Initialization
        HAL_ADC_Start(&hadc1);
    }
    if(ADC_CONTINUOUS_CONV==1)
        adc_init_start();     //ADC Initialization
    else if(ADC_CONTINUOUS_CONV==2)
    {
        adc_interrupt_init();   //ADC in interrupt mode
    }
    else if(ADC_CONTINUOUS_CONV==3)
    {
        adc_dma_init();   //ADC in dma mode
        HAL_ADC_Start_DMA(&hadc1,(uint32_t*)sensor_value_dma,1);  //Start the dma
    }

    /* Setup spi */
    if(SPI_MODE==0)
#endif
        printf("Before   SPI: %c, %c, %c, %c, %c, %c, %c, %c, %c, %c\n",rx_buffer[0],rx_buffer[1],rx_buffer[2],rx_buffer[3],rx_buffer[4],rx_buffer[5],rx_buffer[6],rx_buffer[7],rx_buffer[8],rx_buffer[9]);
        spi_init();
        HAL_SPI_TransmitReceive(&hspi2,tx_buffer,rx_buffer,10,1000);
        sensor_SPI_polling++;
        printf("Finished SPI: %c, %c, %c, %c, %c, %c, %c, %c, %c, %c\n",rx_buffer[0],rx_buffer[1],rx_buffer[2],rx_buffer[3],rx_buffer[4],rx_buffer[5],rx_buffer[6],rx_buffer[7],rx_buffer[8],rx_buffer[9]);
#if 0
    else if (SPI_MODE==1)
    {
        //spi_interrupt_init();
        //spi_interrupt_spi2();
        //HAL_SPI_TransmitReceive_IT(&hspi1,tx_buffer,rx_buffer,1);
    }
    else if(SPI_MODE==2)
        spi_dma_init();
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
            sensor_value_polled = pa0_adc_read();
        }
        else if(ADC_CONTINUOUS_CONV==1)
        {
            /* ADC MODULE*/
            sensor_value_conv = pa0_adc_read();
            printf("In the ADC continuos conversion\n");
        }
        else if(ADC_CONTINUOUS_CONV==3)
        {
            /* ADC MODULE*/
            printf("In the ADC dma configuration\n");
        }
        counter++;
        if(SPI_MODE==0) /* polling only */
        {
            printf("SPI in polling mode! \n\r");
            HAL_SPI_TransmitReceive(&hspi1,tx_buffer,rx_buffer,1,100);
        }
    }
#endif
}

/* Callback as per HAL_TIM_IRQHandler */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
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

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    //ISR
	sensor_value_int = pa0_adc_read();
    HAL_ADC_Start_IT(&hadc1);
    printf("Inside ADC Callback!\n");
}

void SysTick_Handler(void)
{
    //Increment the clock
    HAL_IncTick();  //Update tick based on clock
}

//20170705-J0680523
