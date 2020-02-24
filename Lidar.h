/* 
 * File:   Lidar.h
 * Author: Chloe
 *
 * Created on 07 February 2020
 */

#ifndef VL53L0X_H
#define VL53L0X_H

#include "globals.h"

/*
 * Send data to VL5310X using I2C
 */
void vl53l0x_I2C_SendData(uint8_t slave_address, uint8_t device_register, uint8_t value);


/*
 * Receive data from VL5310X using I2C
 */
uint8_t vl53l0x_I2C_ReceiveData(uint8_t slave_address, uint8_t device_register);


/*
 * Setup VL5310X to desired settings using I2C
 */
void vl5310x_Setup(uint8_t slave_address);


/*
 * Setup VL5310X with initial values
 */
void vl5310x_Initialisation(uint8_t slave_address);


/*
 * Setup VL5310X to recommended tuning values
 */
void vl5310x_Tuning(uint8_t slave_address);

uint8_t Lidar_Read_Register(uint8_t slave_address, uint8_t device_register);

/*
 * Read range from VL5310X
 */
uint16_t vl5310x_ReadRange(uint8_t slave_address);
void Lidar_Change_Address();
void collide_Check();

#endif //VL53L0X