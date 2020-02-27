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
}
