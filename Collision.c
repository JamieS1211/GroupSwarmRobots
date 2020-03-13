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


uint16_t read_range(uint8_t address) {
    uint16_t value[9];
    uint16_t total=0;
    motor_stop();//Ensure stop before reading values
    for (int i=0; i <=10; ++i ) {
        value[i] = VL53L0X_ReadRange(address);  //Lidar 1, Left
    while (value[i] > 3000) {
        value [i] = VL53L0X_ReadRange (address);    
    }
     __delay_ms(500);
    cereal_uint16_t(value[i]);
    total = total + value[i];
    }


    uint16_t Lidar =( total / 10);
        cereal_str("final");
    cereal_uint16_t(Lidar);
    
    //cereal_uint16_t(Lidar);
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
    
    uint16_t value = read_range(0x28);       //Lidar 1
    uint16_t value2 = read_range(0x29);      //Lidar 2, on the right
    
    if (value >3000 && value2 > 3000) {
        move_dist(0,15, false);
        motor_spin(direc2);
        motor_spin(direc2);
        
        uint16_t value = read_range(0x28);       //Lidar 1
        uint16_t value2 = read_range(0x29);      //Lidar 2, on the right
        
        if (value < 3000 || value2 < 3000) {
            motor_spin(direc);
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
    
    uint16_t value = read_range(0x28);       //Lidar 1
    uint16_t value2 = read_range(0x29);      //Lidar 2, on the right
    while (value < 3000 && value2 < 3000) {
        motor_spin(direc); 
    if (direc==0.785) {
        cereal_str("turning left");
    }
        if (direc==-0.785) {
            cereal_str("turning right");
        }
        __delay_ms(100);
        uint16_t value = read_range(0x28);       //Lidar 1
        uint16_t value2 = read_range(0x29);      //Lidar 2, on the right    
        //Move the biggest between distance and distance2 plus some leeway
    }
    if (direc == 0.785) {
        second_avoid (true);
    }
    if (direc == -0.785) {
        second_avoid (false);
    }
}


void collision_avoid(void) {
    motor_stop();
    uint16_t value = read_range(0x28);       //Lidar 1
    uint16_t value2 = read_range(0x29);      //Lidar 2, on the right
    int x=1;
    while (x==1) {

            if (value2 < value) {  
                cereal_str("Right lidar less");
                initial_avoid(false);
                
            }
            else if (value <= value2) { 
                cereal_str("left lidar less");
                initial_avoid(false);
                
            }
        
        if (value > 3000 && value2 < 3000) {
            motor_spin(0.785);  //Left
            uint16_t distance = ((value2/10)+10);
            move_dist(0, distance, false ); //Move forward, check how you set the amount to go forward.//Move the value of value2 + some leeway. 
            motor_spin(-0.785); //Right
            motor_spin(-0.785); //Right
            move_dist(0, (distance+100), false); 
            motor_spin(-0.785);
            
            uint16_t value = read_range(0x28);       //Lidar 1
            uint16_t value2 = read_range(0x29);      //Lidar 2, on the right
            if (value > 3000 && value2 > 3000) {
                // Move to get back to original position
            }
            else {
                motor_spin(0.785);
                move_dist(0,10, false);
                // Repeat until get past.
            }
        
            x=2; //Goes to two as avoided obstacle so get out of the loop
        }
        if (value < 3000 && value2 > 3000) {
            motor_spin(-0.785);  //right
            uint16_t distance = ((value/10)+10);
            move_dist(0, distance, false ); //Move forward, check how you set the amount to go forward.//Move the value of value2 + some leeway. 
            motor_spin(0.785);
            move_dist(0, (distance+100), false);   
            x=2; //Goes to two as avoided obstacle so get out of the loop
    }
        if (value > 3000 && value2 > 3000) {
        // Have something here in case?
        }
    }  
}

// 1 is you can move, 0 is cannot. 

uint8_t collide_check(uint16_t move) {
    
    if (move>500) {
        return 2; //Don't want to do movements further than 500mm
    }
    uint16_t value = read_range(0x28);
    uint16_t value2 = read_range(0x29);

    //If only right reads a value, turn right.
     //If only left reads, turn left.
    uint16_t distance = value+20; //For some leeway
    uint16_t distance2 = value2+20;
    if (move >= distance || move >= distance2) {
        return 0;
    }
    if (move< distance || move < distance2) {
        return 1;
    }
}   





