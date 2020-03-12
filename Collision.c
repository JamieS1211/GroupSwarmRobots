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
#include "mcc_generated_files/examples/i2c2_master_example.h"
#include "cereal.h"

uint16_t read_value(uint8_t address) {
    uint16_t value[10];
    uint16_t value2[10];
    uint16_t total=0;
    uint16_t total2=0;
    motor_stop();//Ensure stop before reading values
    for (int i=0; i <11; ++i ) {
        value[i] = VL53L0X_ReadRange(address);  //Lidar 1, Left
    while (value[i] > 3000) {
        value [i] = VL53L0X_ReadRange (address);    
    }
    total = total + value[i];
    }
    uint16_t Lidar = total / 10;
    return Lidar;
}

void second_avoid( bool direction) {
    float direc;
    float direc2;
    if (direction == true) {
        direc = 0.785;
        direc2 = -0.785;
    }
    else {
        direc = -0.785;
        direc2 = 0.785;
    }
    
    uint16_t value = VL53L0X_ReadRange(0x28);       //Lidar 1
    uint16_t value2 = VL53L0X_ReadRange(0x29);      //Lidar 2, on the right
    
    if (value >3000 && value2 > 3000) {
        move_dist(0,15, false);
        motor_spin(direc2);
        motor_spin(direc2);
        
        uint16_t value = VL53L0X_ReadRange(0x28);       //Lidar 1
        uint16_t value2 = VL53L0X_ReadRange(0x29);      //Lidar 2, on the right
        
        if (value < 3000 || value2 < 3000) {
            move_spin(direc);
            // Move biggest between value and value2 plus some leeway
            
        }
    }
    else {
        
    }
}
        
     
void initial_avoid(bool direction) {
    float direc;
    if (direction == true) {
        direc = 0.785;          //To default turn left
    }
    else {
        direc = -0.785;         // To default turn right
    }
    
    uint16_t value = VL53L0X_ReadRange(0x28);       //Lidar 1
    uint16_t value2 = VL53L0X_ReadRange(0x29);      //Lidar 2, on the right
    while (value < 3000 && value2 < 3000) {
        motor_spin(direc); 
        cereal_str("turning");
        __delay_ms(100);
        uint16_t value = VL53L0X_ReadRange(0x28);       //Lidar 1
        uint16_t value2 = VL53L0X_ReadRange(0x29);      //Lidar 2, on the right    
        //Move the biggest between distance and distance2 plus some leeway
    }
    if (direc == 0.785) {
        second_avoid (true);
    }
    if (direc == 0.785) {
        second_avoid (false);
    }
}


        

// 1 is you can move, 0 is cannot. 

uint8_t collide_check(uint16_t move) {
        uint16_t value[10];
        uint16_t value2[10];
        uint16_t total=0;
        uint16_t total2=0;
    motor_stop();//Ensure stop before reading values
    for (int i=0; i <11; ++i ) {
        value[i] = VL53L0X_ReadRange(0x52);  //Lidar 1, Left
    while (value[i] > 3000) {
        value [i] = VL53L0X_ReadRange (0x52);    
    }
    total = total + value[i];
        value2[i] = VL53L0X_ReadRange(0x00);      //Lidar 2, on the right
    while (value[i] >3000) {
        value2[i] = VL53L0X_ReadRange(0x00);
    }
    total2 = total2 +value2[i];
    }
    uint16_t Lidar = total / 10;
    uint16_t Lidar2 = total2 / 10;

    cereal_int16_t(Lidar);
    int input = 1;
    cereal_int(input);
    
    cereal_int16_t(Lidar2);
    int input1 = 2;
    cereal_int(input1);

    //If only right reads a value, turn right.
     //If only left reads, turn left.
    uint16_t distance = Lidar+20; //For some leeway
    uint16_t distance2 = Lidar2+20;
    if (move >= distance || move >= distance2) {
        return 0;
    }
    if (move< distance || move < distance2) {
        return 1;
    }
}
