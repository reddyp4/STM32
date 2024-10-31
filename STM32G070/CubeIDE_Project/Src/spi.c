/* File for SPI */
#include "spi.h"
#include <stdio.h>
#include "stm32g070xx.h"

SPI_HandleTypeDef hspi2={0};

void spi_init(void)
{
    /* Constraints */
    /* PA5/6/7, PB0,12,14 - taken by boot process */
    /* GPIO Pins: SPI1
    NSS:    PA4-AF0
    CLK:    PA1-AF0
    MOSI:   PA2-AF0
    MISO:   PA11-AF0
    */

    /* GPIO Pins: SPI2
    NSS:    PD0-AF1-CN7-9
    CLK:    PD1-AF1-CN7-10
    MOSI:   PD4-AF1-CN7-15
    MISO:   PD3-AF1-CN7-11
    */
   __HAL_RCC_GPIOD_CLK_ENABLE();    //Select Pad-D
   GPIO_InitTypeDef hgpio1={0};
   hgpio1.Pin = GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4;   //Four pins
   hgpio1.Mode = GPIO_MODE_AF_PP;
   hgpio1.Pull = GPIO_NOPULL;
   hgpio1.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
   hgpio1.Alternate = GPIO_AF1_SPI2;                //As per datasheet
   HAL_GPIO_Init(GPIOD, &hgpio1);
   
   __HAL_RCC_SPI2_CLK_ENABLE(); //Clock to SPI
   hspi2.Instance = SPI2;
   hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;   //baud-rate prescalar-D
   hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;                    //2-phases for edge-D
   hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;                //polarity=low-D
   hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;   //enable crc-D
   hspi2.Init.DataSize = SPI_DATASIZE_8BIT;                  //datasize-8bit-D
   hspi2.Init.Direction = SPI_DIRECTION_2LINES;              //mosi/miso-D
   hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;                   //msb is first bit-D
   hspi2.Init.Mode = SPI_MODE_MASTER;                        //master-D
   hspi2.Init.NSS = SPI_NSS_SOFT;                            //soft nss-D
   hspi2.Init.TIMode = SPI_TIMODE_DISABLE;                   //disable TI mode-D
   HAL_SPI_Init(&hspi2);
   
    /* GPIO Pins: SPI1
    NSS:    PD0-AF1-CN7-9
    CLK:    PD1-AF1-CN7-10
    MOSI:   PC3-AF1-
    MISO:   PC2-AF1-
    */
}

void spi_interrupt_init(void)
{
    /* GPIO Pins: SPI1
    CS:     PD9-AF1
    CLK:    PD8-AF1
    MOSI:   PD6-AF1
    MISO:   PD5-AF1
    */
   __HAL_RCC_GPIOD_CLK_ENABLE();    //Select Pad-B
   GPIO_InitTypeDef hgpio1={0};
   hgpio1.Pin = GPIO_PIN_8|GPIO_PIN_6|GPIO_PIN_5;   //Four pins
   hgpio1.Mode = GPIO_MODE_AF_PP;
   hgpio1.Pull = GPIO_NOPULL;
   hgpio1.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
   hgpio1.Alternate = GPIO_AF1_SPI1;                //As per datasheet
   HAL_GPIO_Init(GPIOD, &hgpio1);
   
   __HAL_RCC_SPI1_CLK_ENABLE(); //Clock to SPI
   SPI_HandleTypeDef hspi1;
   hspi1.Instance = SPI1;
   hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;   //baud-rate prescalar-D
   hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;                    //2-phases for edge-D
   hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;                //polarity=low-D
   hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;   //enable crc-D
   hspi1.Init.DataSize = SPI_DATASIZE_8BIT;                  //datasize-8bit-D
   hspi1.Init.Direction = SPI_DIRECTION_2LINES;              //mosi/miso-D
   hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;                   //msb is first bit-D
   hspi1.Init.Mode = SPI_MODE_MASTER;                        //master-D
   hspi1.Init.NSS = SPI_NSS_SOFT;                            //soft nss-D
   hspi1.Init.TIMode = SPI_TIMODE_DISABLE;                   //disable TI mode-D
   HAL_SPI_Init(&hspi1);

   /* Setup NVIC for SPI, stm32g070xx.h */
   HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
   HAL_NVIC_EnableIRQ(SPI1_IRQn);
}

void SPI1_IRQHandler(void)
{
    /* Pass NVIC Handler to ST SPI IRQ Handler */
    HAL_SPI_IRQHandler(&hspi2);
}

void spi_dma_init(void)
{}
