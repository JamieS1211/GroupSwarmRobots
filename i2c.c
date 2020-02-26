/*
 * File:   i2c.c
 * Author: jamieshepherd
 *
 * Created on January 26, 2020, 2:05 PM
 */


#include <xc.h>

#include "globals.h"
#include "i2c.h"

//Pages 545 - 578 - 597 in data sheet

/*
 * I2C setup - Page 564
 */
void i2C_Setup(void) {
    // Select use of I2C 2 peripheral to RB1 and RB2 pins - Page 275 - 286
    I2C2SCLPPS = 0b01001; // Page 280
    I2C2SDAPPS = 0b01010; 
    
    RB1PPS = 0b100011; // SCL - Page 282
    RB2PPS = 0b100100; // SDA
    
    // Set TRIS & ODCON bits - Page 548
    TRISBbits.TRISB1 = 0; // Page 265
    TRISBbits.TRISB2 = 0;
    
    ODCONBbits.ODCB1 = 1; // Page 269
    ODCONBbits.ODCB2 = 1;
    
    ANSELBbits.ANSELB1 = 0;
    ANSELBbits.ANSELB2 = 0;
    
    I2C2CON0bits.EN = 1; // Enable I2C module 2
    I2C2CON0bits.MODE2 = 1; // Sets mode to 100 - 7-bit address single master
    I2C2CON0bits.MODE1 = 0;
    I2C2CON0bits.MODE0 = 0;
    
    I2C2CON1bits.ACKCNT = 1;
        
    I2C2CLKbits.CLK = 0b0011;
}


#define _XTAL_FREQ 20000000

/*
 * I2C send data - Page 568
 * NOTE: i2C_address must be given as bits 7:1 Address, last bit irrelevant
 * Last byte to write at position 0
 */
void i2C_SendData(uint8_t i2C_address, uint8_t bytes[], uint8_t numberOfBytes) {
    I2C2CNT = numberOfBytes;
    
    I2C2ADB1 = i2C_address & 0b11111110; // Masks last bit to 0
    
    I2C2TXB = bytes[I2C2CNT - 1];
    I2C2CON0bits.S = 1;
    
    while(I2C2STAT0bits.MMA == 1) {
        while(I2C2CON0bits.MDR == 0);
        
        __delay_us(1);
        I2C2TXB = bytes[I2C2CNT - 1];
    }
}



/*
 * I2C receive data - Page 570
 * NOTE: i2C_address must be given as bits 7:1 Address, last bit is irrelevant
 * Last byte read at position 0
 */
void i2C_ReceiveData(uint8_t i2C_address, uint8_t *recievedBytesPointer, uint8_t numberOfReceivedBytes) {
    I2C2CNT = numberOfReceivedBytes;
    
    I2C2ADB1 = i2C_address | 0b00000001; // Masks last bit to 0
    
    
    while(I2C2STAT0bits.MMA == 1) {
        while(I2C2STAT1bits.RXBF == 0);
        
        recievedBytesPointer[I2C2CNT - 1] = I2C2RXB;
    }
}