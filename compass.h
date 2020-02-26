/*
 * File:   compass.h
 * Author: willrice
 *
 * Created on February 7, 2020, 16:05
 * 
 * Modified based on:
 * https://github.com/dthain/QMC5883L
 * Declination angle is removed. Compass points to magnetic North
 * Not true North
 */

#ifndef COMPASS_H
#define COMPASS_H

void comp_i2C_SendData(uint8_t slave_address, uint8_t device_register, uint8_t value);
uint8_t comp_Read_Register(uint8_t slave_address, uint8_t register_value);

void comp_reset();          // reset()
void comp_reconfig_standby();       // reconfig()
void comp_reconfig_cont();

float comp_head();            //readHeading()
void comp_readRaw( int16_t *x, int16_t *y); //readRar()

#endif  //COMPASS_H