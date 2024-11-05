#include "uart.h"
//#include <stdio.h>

UART_HandleTypeDef huart2;
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

void uart_dma_init(void)
{
    /* User action on dma completion */
}
