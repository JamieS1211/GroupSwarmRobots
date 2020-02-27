/* 
 * File:   Code.c
 * Author: Chloe
 *
 * Created on 30 January 2020, 18:11
 */
#define _XTAL_FREQ 20000000
#include <xc.h>
#include <stdint.h>
#include <pic18f27K42.h>
#include <math.h>

#include "globals.h"
#include "VL53L0X.h"
#include "motor.h"

uint8_t collide_check(uint16_t distance) {
    uint16_t value = VL53L0X_ReadRange(0x52);       //Lidar 1
    uint16_t value2 = VL53L0X_ReadRange(0x00);      //Lidar 2, on the right
    
    // Try to get 10 values for average
    // Ensure all numbers and one not wildly different

    uint16_t dist = distance + 500; // As can only move this at a time

    if (distance > 500) { // Value of 500, dont want to move more than this at a time.
        //Send back invalid movement
    } else if (dist < value || dist < value2) {
        return 1; // You can move so send 1.
    } else if (value < 100 || value2 < 100 ) { // Change dependent on stopping distance
        // Turn on the spot or something
        motor_stop();
    } else if (value2 < value) { // If only right reads a value, turn right. 
        //motor_spin()    //Turn right
        return 0;
    } else if (value < value2) { // If only left reads, turn left.
        //turn left
    } else {
        //Invalid movement
    }
    
    return 0;
    while (receive != 0x44) {
       uint8_t data[1] = {0x40};
       i2C_SendData(0x0F,data, 0x01);
       i2C_ReceiveData(0x0F, &point, 0x02);
       
       receive = point;
}
    uint8_t data2[2]={0x0B, 0x01};
    uint8_t data3[2]={0x00, 0x00};
    uint8_t data4[2]={0x01, 0xE8};
        i2C_SendData(0x0F, data2, 0x02);
        i2C_SendData(0x0F, data3, 0x02);
        i2C_SendData(0x0F, data4, 0x02);
        
    LATAbits.LATA7=1; //Lidar 1 high
    
    vl5310x_Setup(0x52);
}

uint8_t collide_check(uint16_t distance) {
uint16_t value = vl5310x_ReadRange(0x52);       //Lidar 1
//uint16_t value2 = vl5310x_ReadRange(0x0F);      //Lidar 2, on the right
//Try to get 10 values for average
//Ensure all numbers and one not wildly different

uint16_t dist = distance + 500;      //As can only move this at a time
if (value>20) {
    TRISBbits.TRISB5=0;
    LATBbits.LATB5=1;
}
/*
if (distance > 500) {     //Value of 500, don't want to move more than this at a time.
    //Send back invalid movement
}

else if (dist < value || dist < value2) {
   uint8_t check = 0x01;
    return check;           // You can move so send 1.
}

else if (value < 100 || value2 < 100 ) {    //Change dependent on stopping distance
    //motor_stop();
//Turn on the spot or something
}

//If only right reads a value, turn right. 

else if (value2 < value) {
//motor_spin()    //Turn right
 uint8_t  check = 0x00;
 return check;
}
 // If only left reads, turn left.

else if (value < value2) {
     //turn left
 }

else {
    //Invalid movement
}
 */
}
