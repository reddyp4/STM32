/* adc.c */
#include "stm32g070xx.h"
#include "stm32g0xx_hal.h"

ADC_HandleTypeDef hadc1={0};
DMA_HandleTypeDef hdma_adc1;

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
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc1.Init.Resolution = ADC_RESOLUTION12b;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    //HAL_ADC_Init(ADC_HandleTypeDef *hadc)
    HAL_ADC_Init(&hadc1);

    adc_ch.Channel = ADC_CHANNEL_0;     //PA0
    adc_ch.Rank = 1;    //Only one adc
    adc_ch.SamplingTime = ADC_SAMPLETIME_160CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1,&adc_ch);
}

void adc_single_conv_init()
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
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc1.Init.Resolution = ADC_RESOLUTION12b;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    //HAL_ADC_Init(ADC_HandleTypeDef *hadc)
    HAL_ADC_Init(&hadc1);

    adc_ch.Channel = ADC_CHANNEL_0;     //PA0
    adc_ch.Rank = 1;    //Only one adc
    adc_ch.SamplingTime = ADC_SAMPLETIME_160CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1,&adc_ch);
}

void adc_interrupt_init()
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
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION12b;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    //HAL_ADC_Init(ADC_HandleTypeDef *hadc)
    HAL_ADC_Init(&hadc1);

    adc_ch.Channel = ADC_CHANNEL_0;     //PA0
    adc_ch.Rank = 1;    //Only one adc
    adc_ch.SamplingTime = ADC_SAMPLETIME_160CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1,&adc_ch);

    HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC1_IRQn);

    HAL_ADC_Start_IT(&hadc1);
}

void adc_dma_init()
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
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION12b;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = ENABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    //HAL_ADC_Init(ADC_HandleTypeDef *hadc)
    HAL_ADC_Init(&hadc1);

    adc_ch.Channel = ADC_CHANNEL_0;     //PA0
    adc_ch.Rank = 1;    //Only one adc
    adc_ch.SamplingTime = ADC_SAMPLETIME_160CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1,&adc_ch);

    HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC1_IRQn);

    /* Enable clock access to DMA */
    __HAL_RCC_DMA1_CLK_ENABLE();
    /* Set interrupt for DMA */
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

    /**/
    hdma_adc1.Instance = DMA1;                      //DMA_Channel_TypeDef
    hdma_adc1.ChannelIndex = DMA1_Channel1;         //Channel
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;    //Direction of dma
    hdma_adc1.Init.PeriphInc = DMA_PINC_ENABLE;     //Enable peripheral
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;   //Halfword align
    hdma_adc1.Init.Mode = DMA_CIRCULAR;     //CIRCULAR for periph to memory
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
    HAL_DMA_Init(&hdma_adc1);   /* Initialize the dma */
    
    //ADC_HandleTypeDef has DMA Handle
    /* Link the dma handle of ADC to the DMA_Handle above */
    __HAL_LINKDMA(&hadc1,DMA_Handle,hdma_adc1);
}

void DMA1_Channel1_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&hdma_adc1);
    /* Do a half complete callback */
}

void ADC_IRQHandler(void)
{
    printf("In the ADC IRQHandler\n");
    HAL_ADC_IRQHandler(&hadc1);
}

void adc_init_start(void)
{
    /* Setup the adc for conversion */
    adc_continuous_conv_init();
    /* Start ADC */
    HAL_ADC_Start(&hadc1);
}
