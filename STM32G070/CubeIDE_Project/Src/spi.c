/* File for SPI */
#include "spi.h"
#include <stdio.h>
#include "stm32g070xx.h"
#include "stm32g0xx_hal.h"

SPI_HandleTypeDef hspi1={0};

void spi_init(void)
{
    /* GPIO Pins: */
}