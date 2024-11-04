/* File for I2C */
#include "i2c.h"

I2C_HandleTypeDef hi2c1={0};

/* I2C Data */
uint8_t DATA_RECORD[6];
uint8_t device_id;
/* Accelerometer data */
int16_t x,y,z;
float xg, yg, zg;

void i2c_hw_init(void)
{
    /* Constraints */
    /* PA5/6/7, PB0,12,14 - taken by boot process */
    /* GPIO Pins: I2C1
    NSS:    PB6-I2C1-SCL
    CLK:    PB7-I2C1-SDA */
    /* GPIO */
    GPIO_InitTypeDef hgpio1={0};
    hgpio1.Speed = GPIO_SPEED_FREQ_VERY_HIGH;       //i2c speed
    hgpio1.Pull = GPIO_PULLUP;                      //pull-up for open-drain
    hgpio1.Pin = GPIO_PIN_6|GPIO_PIN_7;             //PB6/7
    hgpio1.Mode = GPIO_MODE_AF_OD;      //Alternate function, open drain
    hgpio1.Alternate = GPIO_AF6_I2C1;   //_gpio_ex.h
    HAL_GPIO_Init(GPIOB,&hgpio1);

    /* i2c driver setting */
    /* enable clock access */
    __HAL_RCC_I2C1_CLK_ENABLE();
	hi2c1.Instance = I2C1;
    hi2c1.Init.OwnAddress1 = 0x00;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    hi2c1.Memaddress = 0x0;                          //Own address
	hi2c1.Mode = HAL_I2C_MODE_MASTER;               //Master mode
	hi2c1.State = HAL_I2C_STATE_READY;              //Set ready state
    HAL_I2C_Init(&hi2c1);
}

void adxl_write(uint8_t reg, uint8_t value)
{
    uint8_t data[2];
    data[0]=reg;
    data[1]=value;
    HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS, data, 2, 100);
}

void adxl_read_values(uint8_t reg)
{
    HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDRESS, reg, 1, (uint8_t *)DATA_RECORD, 2, 100);
}

void adxl_read_address(uint8_t reg)
{
    HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDRESS, reg, 1, &device_id, 1, 100);
}

void adxl_init(void)
{
    //Read device ID
    adxl_read_address(DEVID_R);
    //Set data format to +/- 4g
    adxl_write(DATA_FORMAT_R, FOUR_G);
    //Reset all bits in control register 
    adxl_write(POWER_CTL_R, RESET);
    //Config PWR control
    adxl_write(POWER_CTL_R, SET_MEASURE_B);

}
