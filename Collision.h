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


uint16_t read_range(uint8_t address);

/*Check if movement can be completed*/
uint8_t collide_check(uint16_t move);

void collision_avoid(void);

/* Avoid the obstacle*/
void initial_avoid(bool direction);

/*Going around the obstacle and back to path*/
void second_avoid( bool direction);

void test(void);


        
#endif //COLLISION_H