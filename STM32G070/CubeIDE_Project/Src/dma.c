#include "dma.h"

DMA_HandleTypeDef hdma_mem2mem;

/* Buffer for dma-memory to memory transfer */
#define BUFFER_SIZE 32
static const uint32_t srcBuffer[BUFFER_SIZE] = {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
static uint32_t dstBuffer[BUFFER_SIZE];

/* Setup DMA for memory transfer*/
void dma_mem_to_mem(void)
{
    //Clock access for DMA1
    __HAL_RCC_DMA1_CLK_ENABLE();
    //Configure USART2 RX DMA
    hdma_mem2mem.Instance = DMA1_Channel1;    //DMA_Channel_TypeDef-stm32g070xx.h
    hdma_mem2mem.Init.Direction = DMA_MEMORY_TO_MEMORY;
    hdma_mem2mem.Init.PeriphInc = DMA_PINC_ENABLE;
    hdma_mem2mem.Init.MemInc = DMA_MINC_ENABLE;
    hdma_mem2mem.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_mem2mem.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_mem2mem.Init.Mode = DMA_NORMAL;
    hdma_mem2mem.Init.Priority = DMA_PRIORITY_HIGH;
    hdma_mem2mem.Init.Request = DMA_REQUEST_USART1_RX;
    HAL_DMA_Init(&hdma_mem2mem);

    //Register callback functions
    HAL_DMA_RegisterCallback(&hdma_mem2mem, HAL_DMA_XFER_CPLT_CB_ID, TransferComplete);
    HAL_DMA_RegisterCallback(&hdma_mem2mem, HAL_DMA_XFER_ERROR_CB_ID, TransferError);
    //Set NVIC
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

    //Tranfer once Interrupt occurs
    HAL_DMA_Start_IT(&hdma_mem2mem, srcBuffer, dstBuffer, BUFFER_SIZE);
}

/* Function handle for dma callback */
static void TransferComplete(DMA_HandleTypeDef *hdma)
{
    //Do something
    printf("Inside transfer callback\n");
}

/* Function handle for dma error callback */
static void TransferError(DMA_HandleTypeDef *hdma)
{
    //Do something
    printf("Inside transfer error callback\n");
}

void DMA_Channel1_IRQHandler(void)
{
    //Call ST DMA Handler
    HAL_DMA_IRQHandler(&hdma_mem2mem);
}