/* 
 * File:   Collision.h
 * Author: Chloe
 *
 * Created on 24 February 2020
 */

#ifndef COLLISION_H
#define COLLISION_H

#include "globals.h"

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
#include "motor.h"


void Lidar_Change_Address();

uint8_t collide_check(uint16_t distance);


#endif //COLLISION_H