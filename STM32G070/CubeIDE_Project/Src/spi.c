/* File for SPI */
#include "spi.h"
#include <stdio.h>
#include "stm32g070xx.h"

SPI_HandleTypeDef hspi1={0};

void spi_init(void)
{
    /* GPIO Pins: SPI1
    CS:     PA4
    CLK:    PA5
    MOSI:   PA7
    MISO:   PA6
    */
   __GPIOA_CLK_ENABLE();            //Select Pad-A
   GPIO_InitTypeDef hgpio1={0};
   hgpio1.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;   //Four pins
   hgpio1.Mode = GPIO_MODE_AF_PP;
   hgpio1.Pull = GPIO_NOPULL;
   hgpio1.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
   hgpio1.Alternate = GPIO_AF0_SPI1;                //As per datasheet
   //HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
   HAL_GPIO_Init(GPIOA, &hgpio1);
   
   __SPI1_CLK_ENABLE();     //Clock to SPI
   SPI_HandleTypeDef hspi1;
   hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;   //baud-rate prescalar
   hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;                    //2-phases for edge
   hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;                //polarity=high
   hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;   //enable crc
   //hspi1.CRCLength = SPI_CRC_LENGTH_8BIT;               //crc is 8-bits
   //hspi1.CRCPolynomial = 1;                             //crc poly-coef
   hspi1.Init.DataSize = SPI_DATASIZE_8BIT;                  //datasize-8bit
   hspi1.Init.Direction = SPI_DIRECTION_2LINES;              //mosi/miso
   hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;                   //msb is first bit
   hspi1.Init.Mode = SPI_MODE_MASTER;                        //master
   hspi1.Init.NSS = SPI_NSS_SOFT;                            //soft nss
   hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;               //enable nss
   hspi1.Init.TIMode = SPI_TIMODE_DISABLE;                   //disable TI mode
   HAL_SPI_Init(&hspi1);
}

void spi_interrupt_init(void)
{
    /* GPIO Pins: SPI1
    CS:     PA4
    CLK:    PA5
    MOSI:   PA7
    MISO:   PA6
    */
   __GPIOA_CLK_ENABLE();            //Select Pad-A
   GPIO_InitTypeDef hgpio1={0};
   hgpio1.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;   //Four pins
   hgpio1.Mode = GPIO_MODE_AF_PP;
   hgpio1.Pull = GPIO_NOPULL;
   hgpio1.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
   hgpio1.Alternate = GPIO_AF0_SPI1;                //As per datasheet
   //HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
   HAL_GPIO_Init(GPIOA, &hgpio1);
   
   __SPI1_CLK_ENABLE();     //Clock to SPI
   SPI_HandleTypeDef hspi1;
   hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;   //baud-rate prescalar
   hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;                    //2-phases for edge
   hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;                //polarity=high
   hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;   //enable crc
   //hspi1.CRCLength = SPI_CRC_LENGTH_8BIT;               //crc is 8-bits
   //hspi1.CRCPolynomial = 1;                             //crc poly-coef
   hspi1.Init.DataSize = SPI_DATASIZE_8BIT;                  //datasize-8bit
   hspi1.Init.Direction = SPI_DIRECTION_2LINES;              //mosi/miso
   hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;                   //msb is first bit
   hspi1.Init.Mode = SPI_MODE_MASTER;                        //master
   hspi1.Init.NSS = SPI_NSS_SOFT;                            //soft nss
   hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;               //enable nss
   hspi1.Init.TIMode = SPI_TIMODE_DISABLE;                   //disable TI mode
   HAL_SPI_Init(&hspi1);

   /* Setup NVIC for SPI, stm32g070xx.h */
   HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
   HAL_NVIC_EnableIRQ(SPI1_IRQn);

   /* Start interrupt */
   __HAL_SPI_ENABLE_IT(&hspi1, SPI_IT_RXNE);
}

void SPI1_IRQHandler(void)
{
    /* Pass NVIC Handler to ST SPI IRQ Handler */
    HAL_SPI_IRQHandler(&hspi1);
}

void spi_dma_init(void)
{}