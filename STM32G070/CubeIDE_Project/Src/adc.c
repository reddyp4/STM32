/* adc.c */
#include "stm32g070xx.h"
#include "stm32g0xx_hal.h"

ADC_HandleTypeDef hadc1={0};

/* Result of adc reading */
uint32_t pa0_adc_read(void)
{
    return HAL_ADC_GetValue(&hadc1);    /* Just return adc value of pa0 in count */
}

void adc_continuous_conv_init()
{
    GPIO_InitTypeDef gpio_pa0_str = {0};
    ADC_ChannelConfTypeDef adc_ch = {0};

    /* Enable clock access on PA0 - GPIOA */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Configure PA0 for analog pin */
    gpio_pa0_str.Pin = GPIO_PIN_0;
    gpio_pa0_str.Mode = GPIO_MODE_ANALOG;
    gpio_pa0_str.Pull = GPIO_NOPULL;
    //HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
    HAL_GPIO_Init(GPIOA, &gpio_pa0_str);

    /* Type of Conversion as continuous for PA0 */
    /* Enable clock access for ADC */
    __HAL_RCC_ADC_CLK_ENABLE();
    /* Initialize the adc structure */
    ADC_InitTypeDef adc_init1;
    hadc1.Instance = ADC1;
    adc_init1.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    adc_init1.Resolution = ADC_RESOLUTION12b;
    adc_init1.ContinuousConvMode = ENABLE;
    adc_init1.DiscontinuousConvMode = DISABLE;
    adc_init1.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    adc_init1.DataAlign = ADC_DATAALIGN_RIGHT;
    adc_init1.NbrOfConversion = 1;
    adc_init1.DMAContinuousRequests = DISABLE;
    adc_init1.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc1.Init = adc_init1;
    //HAL_ADC_Init(ADC_HandleTypeDef *hadc)
    HAL_ADC_Init(&hadc1);

    adc_ch.Channel = ADC_CHANNEL_0;     //PA0
    adc_ch.Rank = 1;    //Only one adc
    adc_ch.SamplingTime = ADC_SAMPLETIME_160CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1,&adc_ch);
}

void adc_init_start(void)
{
    /* Setup the adc for conversion */
    adc_continuous_conv_init();
    /* Start ADC */
    HAL_ADC_Start(&hadc1);
}