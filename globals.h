/*
 * File:   globals.h
 * Author: jamieshepherd
 *
 * Created on January 18, 2020, 6:09 PM
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#include "position.h"

/* ~~~~~~~~~~~~~~~~~~
 * Environment Memory
 * ~~~~~~~~~~~~~~~~~~*/
// Global Error variables
float moveError = 0.2;      // 20%
float compError = M_PI/18;  // 10 degrees
int tranError = 100;        // 100mm

// Move Memory
// Move memory variables
uint8_t moveMem_p = 0;

// Current Movement and Saved
struct polarcoord currMove;
struct polarcoord prevMove[10] = {0};

// Length of Move Array
uint8_t prevMove_size = sizeof(prevMove)/sizeof(struct polarcoord);


// Light Memory
// Light memory variables
uint8_t lit_Mem_p = 0;

// Light memory array
struct bubble lit_Mem[4] = {0};

// Length of Move Array
uint8_t lit_Mem_size = sizeof(lit_Mem)/sizeof(struct bubble);


// Object Memory
// Object memory length
uint8_t obj_Mem_p = 0;

// Light memory array
struct bubble obj_Mem[4] = {0};

// Length of Move Array
uint8_t obj_Mem_size = sizeof(obj_Mem)/sizeof(struct bubble);


//Definitions for motor management
#define leftForwards LATBbits.LATB3
#define leftBackwards LATBbits.LATB2
#define rightForwards LATBbits.LATB1
#define rightBackwards LATBbits.LATB0

#endif //GLOBALS_H