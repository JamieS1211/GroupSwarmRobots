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

#include <xc.h> // Make int16_t work
#include "globals.h"
#include "mcc_generated_files/examples/i2c2_master_example.h"
#include "compass.h"
#include "mcc_generated_files/mcc.h"
#include "cereal.h"


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
    I2C2_WriteNBytes(slave_address, data, 2);
}

uint8_t comp_Read_Register(uint8_t slave_address, uint8_t register_value) {
    uint8_t value;    
    I2C2_ReadDataBlock(slave_address, register_value, &value, 1);
    return value;
}

void comp_reconfig_standby() {
    comp_i2C_SendData(0x0D, 11, 0x01);  // Define set/Reset period
    comp_i2C_SendData(0x0D, 9, 0x00);   // set standby
}

void comp_reconfig_cont() {
    comp_i2C_SendData(0x0D, 11, 0x01);  // Define set/Reset period
    comp_i2C_SendData(0x0D, 9, 0x81);   // OSR = 128, Range = 2 Gauss, ODR = 10Hz, set continous measurement
}
    
void comp_reset() {
    comp_i2C_SendData(0x0D, 10, 0x80);  // Soft reset (clears previous values)
    comp_reconfig_cont();
}

void comp_readRaw( int16_t *x, int16_t *y) {
    // Set compass to read
    comp_reset();
    
    // Waiting for ready
    while (!(comp_Read_Register(0x0D, 6) & 1));
    
    // Read 2 axis values (may need to reconfigure if compass x isn't forwards)
    // For future reference the First value in the MSB is +/-
    uint8_t x_lsb = comp_Read_Register(0x0D, 0);
    uint8_t x_msb = comp_Read_Register(0x0D, 1);
    
    uint8_t y_lsb = comp_Read_Register(0x0D, 2);
    uint8_t y_msb = comp_Read_Register(0x0D, 3);
    
    // Turn compass to standby
    comp_reconfig_standby();
    
    // Bit shift to values, returned via pointer
    *x = ((int16_t)x_msb << 8) + x_lsb;
    *y = ((int16_t)y_msb << 8) + y_lsb;
}

float comp_head() {
    // Read
    int16_t x, y;
    comp_readRaw(&x,&y);
    
    // Calculate angle
    float heading = atan2(y,x);
    
    // Print to cereal
    cereal_str("Compass Reading:$");
    cereal_float(heading);
  
    return heading;
}