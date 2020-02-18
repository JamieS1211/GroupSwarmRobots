/*
 * File:   envMem.c
 * Author: willrice
 *
 * Created on February 13, 2020, 15:00
 */


#include <xc.h> // Think is library type thing

#include "globals.h"
#include "stdlib.h"

//I'll probably write out the maths nicely else where

int update_place(int place, int array_length) {
    place = place + 1;
    if (place >= array_length) {
        place = 0;
    }
    return place;
}

struct bubble update_bubble(struct bubble old, struct polarcoord newmove) {
    
}

struct balloon update_balloon(struct balloon old, struct polarcoord newmove) {
    
}

void update_envMem() {
    
}
