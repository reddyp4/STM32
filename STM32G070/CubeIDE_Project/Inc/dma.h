#ifndef DMA_H_
#define DMA_H_

#include "stm32g070xx.h"
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_dma.h"

void dma_mem_to_mem(void);
static void TransferError(DMA_HandleTypeDef *hdma);
static void TransferComplete(DMA_HandleTypeDef *hdma);


#endif  /* DMA_H_ */