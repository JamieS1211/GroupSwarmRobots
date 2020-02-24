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

void comp_reconfig_standby()
{
    //write_register(address,register,value)
    //write_register(QMC5883L_ADDR,QMC5883L_CONFIG,QMC5883L_CONFIG_OS128|QMC5883L_CONFIG_2GAUSS|QMC5883L_CONFIG_10HZ|QMC5883L_CONFIG_STANDBY);
    uint8_t standbyte[1] = {QMC5883L_CONFIG_OS128|QMC5883L_CONFIG_2GAUSS|QMC5883L_CONFIG_10HZ|QMC5883L_CONFIG_STANDBY};
    uint8_t addr = QMC5883L_ADDR;
    //void i2C_SendData(addr, standbyte, 1);
}
    
void comp_reset()
{
    //write_register(QMC5883L_ADDR,QMC5883L_RESET,0x01);
    comp_reconfig_standby();
}
void comp_reconfig_cont()
{
    //write_register(address,register,value)
    //write_register(QMC5883L_ADDR,QMC5883L_CONFIG,QMC5883L_CONFIG_OS128|QMC5883L_CONFIG_2GAUSS|QMC5883L_CONFIG_10HZ|QMC5883L_CONFIG_CONT);
    uint8_t contbyte[1] = {QMC5883L_CONFIG_OS128|QMC5883L_CONFIG_2GAUSS|QMC5883L_CONFIG_10HZ|QMC5883L_CONFIG_CONT};
    uint8_t addr = QMC5883L_ADDR;
    //void i2C_SendData(addr, contbyte, uint8_t 1);
}

int comp_readRaw( int16_t *x, int16_t *y, int16_t *z, int16_t *t )
{
//  *x = Wire.read() | (Wire.read()<<8);
//  *y = Wire.read() | (Wire.read()<<8);
//  *z = Wire.read() | (Wire.read()<<8);

  return 1;
}

float comp_head()
{
    // Compass to continous
    comp_reconfig_cont();
    
    // Read
    int16_t x, y, z, t;
    comp_readRaw(&x,&y,&z,&t);

    // Compass to standby
    comp_reconfig_standby();
    
    // Calculate angle
    float heading = atan2(y,x);
  
    return heading;
}          