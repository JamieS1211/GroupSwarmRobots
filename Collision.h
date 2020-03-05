/* 
 * File:   Collision.h
 * Author: Chloe
 *
 * Created on 25 February 2020
 */

#ifndef COLLISION_H
#define COLLISION_H

#include <xc.h>
#include <stdint.h>
#include <pic18f27K42.h>
#include <math.h>

#include "globals.h"


/*Check if movement can be completed*/
uint8_t collide_check(uint16_t distance);
void collision();

#endif //COLLISION_H