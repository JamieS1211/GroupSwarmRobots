/*
 * File:   envMem.h
 * Author: willrice
 *
 * Created on February 13, 2020, 15:00
 */

#ifndef ENVMEM_H
#define ENVMEM_H

#include "position.h"


//I'll probably write out the maths nicely else where


// Universal Structures
struct polarcoord {
    int radius;
    float angle;
};

struct twoangles {
    float angA;
    float angB;
};

struct threeangles {
    float offset_aclk;
    float mean;
    float offset_clk;
};

struct twooftwo {
    struct twoangles group1;
    struct twoangles group2;
};

struct twoofthree {
    struct threeangles group1;
    struct threeangles group2;
};

struct bubble {
    int radius;
    float angle;
    int r_error;
};

struct balloon {
    int radius;
    struct threeangles angles;
};

// EnvMem functions
int update_place(int place, int array_length);

struct bubble update_bubble(struct bubble old, struct polarcoord newmove);

struct balloon update_balloon(struct balloon old, struct polarcoord newmove);

void update_envMem();

#endif //ENVMEM_H