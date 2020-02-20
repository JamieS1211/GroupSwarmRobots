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
#include "i2c.h"
#include "Lidar.h"


void Lidar_Change_Address() {


    TRISAbits.TRISA7 = 0; //OUTPUT
    TRISAbits.TRISA6 = 0; 
    LATAbits.LATA7=0;
    LATAbits.LATA6=0;  //Turn off both lidars
    __delay_ms(10);        
    LATAbits.LATA7=1;
    LATAbits.LATA6=1;  //Turn on both lidars
    LATAbits.LATA7=0; //Lidar 1 low
    
    uint8_t point;
    //uint8_t *point;
    //uint8_t &point = {0x00};
    uint8_t sendata[1]={0x40};
    i2C_SendData(0x0F,sendata, 0x01);
    i2C_ReceiveData(0x0F,&point, 0x02);
    uint8_t receive = point;
    
    while (receive != 0x44) {
       uint8_t data[1]={0x40};
       i2C_SendData(0x0F,data, 0x01);
       i2C_ReceiveData(0x0F, &point, 0x02);
       
       receive = point;
}
    uint8_t data2[2]={0x0B01};
    uint8_t data3[2]={0x0000};
    uint8_t data4[2]={0x01E8};
        i2C_SendData(0x0F, data2, 0x02);
        i2C_SendData(0x0F, data3, 0x02);
        i2C_SendData(0x0F, data4, 0x02);
        
    LATAbits.LATA7=1; //Lidar 1 high
}

uint8_t collide_check(uint8_t distance) {
uint16_t value = vl5310x_ReadRange(0x52);       //Lidar 1
uint16_t value2 = vl5310x_ReadRange(0x0F);      //Lidar 2, on the right

uint8_t dist=distance+0x1F4;      //As can only move this at a time

if (distance > 0x1F4) {     //Value of 500, dont want to move more than this at a time.
    //Send back invalid movement
}

else if (dist < value || dist < value2) {
   uint8_t check = 0x01;
    return check;           // You can move so send 1.
}
//Try to get 10 values for average
//Ensure all numbers and one not wildly different

//Change dependent on stopping distance
//else if (value < 0x64 || value2 < 0x64 ) {    //Might not need just a stop function or at least stop then do something???
//Stop
//}

//If only right reads a value, turn right. 

else if (value2 < value) {
    //Turn right
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

/*
If both sensor reads the same or similar value, object is dead ahead and cannnot fit through
so only need to turn slighly to avoid.

Remeber instead of letting the Lidar read
Out of range, I set it to be a widely big 
number which could help with coding.
*/




}
