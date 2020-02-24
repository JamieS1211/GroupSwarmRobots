/*
 * File:   compass.c
 * Author: willrice
 *
 * Created on February 7, 2020, 21:50
 * 
* Modified based on:
 * https://github.com/dthain/QMC5883L
 * Declination angle is removed. Compass points to magnetic North
 * Not true North
 */

#include "globals.h"
#include "i2c.h"

/*
 * QMC5883L
 * http://wiki.epalsite.com/images/7/72/QMC5883L-Datasheet-1.0.pdf
 */

/* The default I2C address of this chip */
#define QMC5883L_ADDR 0x0D

/* Register numbers */
#define QMC5883L_X_LSB 0
#define QMC5883L_X_MSB 1
#define QMC5883L_Y_LSB 2
#define QMC5883L_Y_MSB 3
#define QMC5883L_Z_LSB 4
#define QMC5883L_Z_MSB 5
#define QMC5883L_STATUS 6
#define QMC5883L_TEMP_LSB 7
#define QMC5883L_TEMP_MSB 8
#define QMC5883L_CONFIG 9
#define QMC5883L_CONFIG2 10
#define QMC5883L_RESET 11
#define QMC5883L_RESERVED 12
#define QMC5883L_CHIP_ID 13

/* Bit values for the STATUS register */
#define QMC5883L_STATUS_DRDY 1
#define QMC5883L_STATUS_OVL 2
#define QMC5883L_STATUS_DOR 4

/* Oversampling values for the CONFIG register */
#define QMC5883L_CONFIG_OS512 0b00000000
#define QMC5883L_CONFIG_OS256 0b01000000
#define QMC5883L_CONFIG_OS128 0b10000000
#define QMC5883L_CONFIG_OS64  0b11000000

/* Range values for the CONFIG register */
#define QMC5883L_CONFIG_2GAUSS 0b00000000
#define QMC5883L_CONFIG_8GAUSS 0b00010000

/* Rate values for the CONFIG register */
#define QMC5883L_CONFIG_10HZ   0b00000000
#define QMC5883L_CONFIG_50HZ   0b00000100
#define QMC5883L_CONFIG_100HZ  0b00001000
#define QMC5883L_CONFIG_200HZ  0b00001100

/* Mode values for the CONFIG register */
#define QMC5883L_CONFIG_STANDBY 0b00000000
#define QMC5883L_CONFIG_CONT    0b00000001

void comp_i2C_SendData(uint8_t slave_address, uint8_t device_register, uint8_t value) {
    uint8_t data[2] = {device_register, value};
    i2C_SendData(slave_address, data, 2);
}

int8_t comp_Read_Register(uint8_t slave_address, uint8_t register_value) {
    uint8_t pointt;
    uint8_t reg[1]={register_value};
    i2C_SendData(slave_address, reg, 0x01);
    i2C_ReceiveData(slave_address, &pointt, 0x01);
    
    uint8_t value=pointt;
    return value;
}

void comp_reconfig_standby()
{
    //write_register(address,register,value)
    //write_register(QMC5883L_ADDR,QMC5883L_CONFIG,QMC5883L_CONFIG_OS128|QMC5883L_CONFIG_2GAUSS|QMC5883L_CONFIG_10HZ|QMC5883L_CONFIG_STANDBY);
    comp_i2C_SendData(QMC5883L_ADDR, QMC5883L_CONFIG, QMC5883L_CONFIG_OS128|QMC5883L_CONFIG_2GAUSS|QMC5883L_CONFIG_10HZ|QMC5883L_CONFIG_STANDBY);
}

void comp_reconfig_cont()
{
    //write_register(address,register,value)
    //write_register(QMC5883L_ADDR,QMC5883L_CONFIG,QMC5883L_CONFIG_OS128|QMC5883L_CONFIG_2GAUSS|QMC5883L_CONFIG_10HZ|QMC5883L_CONFIG_CONT);
    comp_i2C_SendData(QMC5883L_ADDR, QMC5883L_CONFIG, QMC5883L_CONFIG_OS128|QMC5883L_CONFIG_2GAUSS|QMC5883L_CONFIG_10HZ|QMC5883L_CONFIG_CONT);
}
    
void comp_reset()
{
    //write_register(QMC5883L_ADDR,QMC5883L_RESET,0x01);
    comp_i2C_SendData(QMC5883L_ADDR, QMC5883L_RESET, 0x01);
    comp_reconfig_standby();
}

void comp_readRaw( int16_t *x, int16_t *y)
{
    uint8_t x_lsb = comp_Read_Register(QMC5883L_ADDR, QMC5883L_X_LSB);
    uint8_t x_msb = comp_Read_Register(QMC5883L_ADDR, QMC5883L_X_MSB);
    
    uint8_t y_lsb = comp_Read_Register(QMC5883L_ADDR, QMC5883L_Y_LSB);
    uint8_t y_msb = comp_Read_Register(QMC5883L_ADDR, QMC5883L_Y_MSB);
    
    *x = (x_msb << 8) | x_lsb;
    *y = (y_msb << 8) | y_lsb;
}

float comp_head()
{
    // Compass to continous
    comp_reconfig_cont();
    
    // Read
    int16_t x, y;
    comp_readRaw(&x,&y);

    // Compass to standby
    comp_reconfig_standby();
    
    // Calculate angle
    float heading = atan2(y,x);
  
    return heading;
}          