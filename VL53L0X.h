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
 * Send data to VL53L0X using I2C
 */
void VL53L0X_SendData(uint8_t slave_address, uint8_t device_register, uint8_t value);


/*
 * Receive data from VL53L0X using I2C
 */
uint8_t VL53L0X_Read_Register(uint8_t slave_address, uint8_t register_value);


/*
 * Change the I2C address of the VL53L0X 
 */
void VL53L0X_Change_Address (uint8_t oldAddress, uint8_t newAddress);


/*
 * Setup VL53L0X to desired settings using I2C
 */
void VL53L0X_Setup(uint8_t slave_address);


/*
 * Setup VL53L0X with initial values
 */
void VL53L0X_Initialisation(uint8_t slave_address);


/*
 * Setup VL53L0X to recommended tuning values
 */
void VL53L0X_Tuning(uint8_t slave_address);

uint8_t Lidar_Read_Register(uint8_t slave_address, uint8_t device_register);

/*
 * Read range from VL53L0X
 */
uint16_t VL53L0X_ReadRange(uint8_t slave_address);
void Lidar_Change_Address();
void collide();

#endif //VL53L0X