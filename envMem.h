/*
 * File:   envMem.h
 * Author: willrice
 *
 * Created on February 13, 2020, 15:00
 */

#ifndef ENVMEM_H
#define ENVMEM_H


//I'll probably write out the maths nicely else where


// Structures
struct bubble {
    int radius;
    float angle;
    int r_error;
};

struct balloon {
    int radius;
    struct threeangles angles;
    int r_error;
};

struct moveMem {
    struct bubble current; // Movement which is continously added to until offload
    
    // This whole part will be replaced with pointers
    // I am just stupid
    uint8_t pointyboi; // Pointer for latest position
    struct bubble move0;
    struct bubble move1;
    struct bubble move2;
    struct bubble move3;
    // Will be allocatable to n number in global
};

//// To add to moveMem
//moveMem.current = polar_add_struct(moveMem.current,polar_coordinate);
//
//// To offload from current
//moveMem.pointyboi -> moveMem.move0 = moveMem.current;
//moveMem.current = 0;


#endif //ENVMEM_H