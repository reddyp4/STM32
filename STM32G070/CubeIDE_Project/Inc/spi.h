/* Header for SPI */
#ifndef SPI_H_
#define SPI_H_

#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_spi.h"

void spi_init(void);
void spi_interrupt_init(void);
void spi_interrupt_spi1_init2(void);
void spi_dma_init(void);

#endif  /* SPI_H_ */
