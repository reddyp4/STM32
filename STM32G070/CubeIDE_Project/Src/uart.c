#include "uart.h"
//#include <stdio.h>

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_rx,hdma_usart1_tx;

uint32_t uart_tx_counter=0, uart_rx_counter=0, uart_rx_tx_counter=0;

/* Using printf to retarget the data */
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 10);
    return ch;
}

void uart_hw_init(void)
{
    //alternate function AF00 for PA14 and PA15
    //Enable clock for GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();

    //Enable UART module clock access
    __HAL_RCC_USART2_CLK_ENABLE();

    //Configure pins to alternate functions-UART
    GPIO_InitTypeDef GPIO_UART={0};
    GPIO_UART.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_UART.Mode = GPIO_MODE_AF_PP;
    GPIO_UART.Alternate = GPIO_AF1_USART2;   //As per manual
    GPIO_UART.Pull = GPIO_NOPULL;
    GPIO_UART.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    HAL_GPIO_Init(GPIOA, &GPIO_UART);

    //Configure UART, as per HAL UART driver registers
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;                          /* Baud rate*/
    huart2.Init.WordLength = UART_WORDLENGTH_8B;            /* 8-bit word */
    huart2.Init.StopBits = UART_STOPBITS_1;                 /* Single stop bit */
    huart2.Init.Parity = UART_PARITY_NONE;                  /* No Parity */
    huart2.Init.Mode = UART_MODE_TX;                        /* TX only to PC */
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;			/* No flow control */
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;        /* 16-bit oversampling*/
    HAL_UART_Init(&huart2);
}

void uart_hw_interrupt_init(void)
{
    //alternate function AF00 for PA14 and PA15
    //Enable clock for GPIOA
    __HAL_RCC_GPIOA_CLK_ENABLE();

    //Enable UART module clock access
    __HAL_RCC_USART2_CLK_ENABLE();

    //Configure pins to alternate functions-UART
    GPIO_InitTypeDef GPIO_UART={0};
    GPIO_UART.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_UART.Mode = GPIO_MODE_AF_PP;
    GPIO_UART.Alternate = GPIO_AF1_USART2;   //As per manual
    GPIO_UART.Pull = GPIO_NOPULL;
    GPIO_UART.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    HAL_GPIO_Init(GPIOA, &GPIO_UART);

    //Configure UART, as per HAL UART driver registers
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;                          /* Baud rate*/
    huart2.Init.WordLength = UART_WORDLENGTH_8B;            /* 8-bit word */
    huart2.Init.StopBits = UART_STOPBITS_1;                 /* Single stop bit */
    huart2.Init.Parity = UART_PARITY_NONE;                  /* No Parity */
    huart2.Init.Mode = UART_MODE_TX_RX;                        /* TX only to PC */
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;			/* No flow control */
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;        /* 16-bit oversampling*/
    HAL_UART_Init(&huart2);
}

void uart_init(void)
{
    uart_hw_init();
}

void uart_interrupt_init(void)
{
    uart_hw_interrupt_init();
    /* Setup the interrupt */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
}

void USART2_IRQHandler(void)
{
    /* Call the ST USART2 IRQ Handler */
    HAL_UART_IRQHandler(&huart2);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uart_tx_counter++;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uart_rx_counter++;
}

void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{
    /* Do something when Wake up */
    uart_rx_tx_counter++;
}

void HAL_UARTEx_TxFifoEmptyCallback(UART_HandleTypeDef *huart)
{
    uart_tx_counter++;
    /* Do something when Tx FIFO is empty */
}

void HAL_UARTEx_RxFifoFullCallback(UART_HandleTypeDef *huart)
{
    uart_rx_counter++;
    /* Do something when Rx FIFO is full */
}

/**********************************************************/
/**********************************************************/
/**********************************************************/

void uart_dma_init(void)
{
    /* User action on dma completion */
    /* Both reception and transmit using dma */
    /* Setup UART in interrupt mode */
    uart_hw_interrupt_init();
    //Clock access to DMA 
    __HAL_RCC_DMA1_CLK_ENABLE();
    //Do not need NVIC
    //Configure USART2 RX DMA
    hdma_usart1_rx.Instance = DMA1_Channel1;    //DMA_Channel_TypeDef-stm32g070xx.h
    //hdma_usart1_rx.ChannelIndex = DMA_REQUEST_USART1_RX;    //Handled by HAL_DMA_Init()
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_rx.Init.Request = DMA_REQUEST_USART1_RX;
    HAL_DMA_Init(&hdma_usart1_rx);
    //Link USART2 to DMA
    huart2.hdmarx = &hdma_usart1_rx;

    //Setup the TX DMA channel
    //Configure UART2 TX DMA
    hdma_usart1_tx.Instance = DMA1_Channel2;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart1_tx.Init.Request = DMA_REQUEST_USART1_TX;
    HAL_DMA_Init(&hdma_usart1_tx);
    //Link USART1 to DMA
    huart2.hdmatx = &hdma_usart1_tx;

    //Setup NVIC for DMA transfer
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
    //Setup NVIC for DMA transfer
    HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);
}

#if (UART_MODE==2)
/* Link NVIC IRQHandler to ST IRQHandler */
void DMA_Channel1_IRQHandler(void)
{
    /* Link to ST */
    HAL_DMA_IRQHandler(&hdma_usart1_rx);
}
#endif

/* Link NVIC IRQHandler to ST IRQHandler */
void DMA_Channel2_3_IRQHandler(void)
{
    /* Link to ST */
    HAL_DMA_IRQHandler(&hdma_usart1_tx);
}
