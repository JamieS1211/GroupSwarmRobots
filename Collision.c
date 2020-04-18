/* 
 * File:   Code.c
 * Author: Chloe
 *
 * Created on 30 January 2020, 18:11
 */

//#define _XTAL_FREQ 20000000
#include <xc.h>
#include <stdint.h>
//#include <pic18f27K42.h>
#include <math.h>

#include "globals.h"
#include "VL53L0X.h"
#include "motor.h"
#include "mcc_generated_files/examples/i2c2_master_example.h"
#include "mcc_generated_files/mcc.h"
#include "cereal.h"


uint16_t read_range(uint8_t address) {
    __delay_ms(50);
    uint24_t value[9] = {0};
    uint24_t total=0;
    motor_stop();//Ensure stop before reading values
    for (int i=0; i <=9; ++i ) {
        value[i] = VL53L0X_ReadRange(address);  //Lidar 1, Left
//    while (value[i] > 3000) {
//        value [i] = VL53L0X_ReadRange (address);    
//    }    
    total = total + value[i];
    }

    uint16_t Lidar = (total/10);
        cereal_str("final$");
    cereal_uint16_t(Lidar);
    
    return Lidar;
    
}


void second_avoid( bool direction) {
    float direc;
    float direc2;
    if (direction == true) {
        direc = 0.785;
        direc2 = -0.785;
        cereal_str("Second avoid true$");
    }
    else {
        direc = -0.785;
        direc2 = 0.785;
        cereal_str("second avoid false$");
    }
    
    uint16_t value = read_range(0x28);       //Lidar 1
    __delay_ms(50);
    uint16_t value2 = read_range(0x29);      //Lidar 2, on the right
    
    if (value >3000 && value2 > 3000) {

        move_dist(0,15, false);
        motor_spin(direc2);
        motor_spin(direc2);
        
        value = read_range(0x28);       //Lidar 1
        value2 = read_range(0x29);      //Lidar 2, on the right
        
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
        cereal_str("initial avoid true$");
    }
    else {
        direc = -0.785;         // To default turn right
        cereal_str("initial avoid false$");
    }        
    uint16_t value = read_range(0x28);       //Lidar 1
    uint16_t value2 = read_range(0x29);      //Lidar 2, on the right
    while (value < 2000 && value2 < 2000) {
        motor_spin(direc);
        value = read_range(0x28);       //Lidar 1
        value2 = read_range(0x29);      //Lidar 2, on the right    
        //Move the biggest between distance and distance2 plus some leeway
        cereal_str("In loop$");
    }
    if (direc == 0.785) {
        motor_stop();
        __delay_ms(1000);
        second_avoid(true);
        cereal_str("Second true$");
    }
    if (direc == -0.785) {
        motor_stop();
        __delay_ms(1000);
        second_avoid(false);
        cereal_str("Second false$");
    }
    
    cereal_str("Loop exit$");
    return;
}


void collision_avoid(void) {
    motor_stop();
    uint16_t value = read_range(0x28);       //Lidar 1
    __delay_ms(50);
    uint16_t value2 = read_range(0x29);      //Lidar 2, on the right
    //Turn in the way of the biggest value
    if (value < 2000 && value2 > 2000) {
        initial_avoid(true);
    }
    else if ( value > 2000 && value2 < 2000) {
        initial_avoid(false);
    }

    else if (value2 < value) {  
       cereal_str("Right lidar less$");
       initial_avoid(true);         
    }
    else if (value <= value2) { 
       cereal_str("left lidar less$");
                
       initial_avoid(false);      
    }
    else {
      cereal_str("error$");
    }
    return;
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



void test(void) {
    int x=1;
    if (x==1) {
        cereal_str("initial avoid true$");
    spin_test();
    }
}

