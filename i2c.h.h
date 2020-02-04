/*
 * File:   i2c.h
 * Author: jamieshepherd
 *
 * Created on January 26, 2020, 2:05 PM
 */

#ifndef I2C_H
#define I2C_H


//Pages 545 - 578 - 597 in data sheet

/*
 * I2C setup - Page 564
 */
void i2C_Setup(void);



/*
 * I2C send data - Page 568
 * NOTE: i2C_address must be given as bits 7:1 Address, last bit irrelevant
 * Last byte to write at position 0
 */
void i2C_SendData(uint8_t i2C_address, uint8_t bytes[], uint8_t numberOfBytes);



/*
 * I2C receive data - Page 570
 * NOTE: i2C_address must be given as bits 7:1 Address, last bit is irrelevant
 * Last byte read at position 0
 */
void i2C_ReceiveData(uint8_t i2C_address, uint8_t *recievedBytesPointer, uint8_t numberOfReceivedBytes);

#endif //I2C_H