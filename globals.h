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

//Definitions for motor management
#define leftForwards LATCbits.LATC0
#define leftBackwards LATCbits.LATC7
#define rightForwards LATCbits.LATC5
#define rightBackwards LATCbits.LATC6

#endif //GLOBALS_H