/* Header for DATA_FORMAT_RI2C */

#ifndef I2C_H_
#define I2C_H_

#include<stdint.h>
#include<stdio.h>
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_i2c.h"

/* Accelerometer: ADXL345 */
#define DEVID_R         0x00
#define POWER_CTL_R     0x2D
#define DATA_FORMAT_R   0x31

#define DEVICE_ADDRESS  0x53<<1
#define ADXL_WRITE      0x3A
#define ADXL_READ       0x3B

#define FOUR_G          0x01

#define RESET           0x00
#define SET_MEASURE_B   0x08

#define DATA_START_ADDR 0x32

#define FOUR_G_SCALE_FACT 0.0078

void i2c_hw_init(void);
void adxl_write(uint8_t reg, uint8_t value);
void adxl_read_values(uint8_t reg);
void adxl_read_address(uint8_t reg);
void adxl_init(void);


#endif  /* I2C_H_ */