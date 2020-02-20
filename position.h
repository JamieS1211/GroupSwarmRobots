/*
 * File:   position.h
 * Author: willrice
 *
 * Created on February 7, 2020, 22:00
 */

#ifndef POSITION_H
#define POSITION_H

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
    int r_error;
};

// EnvMem functions (used by others)
int update_place(int place, int array_length);

//envMem functions (used by self)
struct bubble update_bubble(struct bubble old, struct polarcoord newmove);
struct balloon update_balloon(struct balloon old, struct polarcoord newmove);
void update_envMem();

// Math functions used by others
float ang_scale(float theta);
float ang_diff(float ang1, float ang2);

// Structure functions
struct polarcoord polar_add(int radiusA, float angleA, int radiusB, float angleB);
struct polarcoord polar_add_struct(struct polarcoord polarA, struct polarcoord polarB);
struct polarcoord polar_sub_struct(struct polarcoord polarA, struct polarcoord polarB);


// Awful functions of pain doom and destruction
struct twoofthree   ang_overlap();
struct twoangles    rice_calc (int rMove, float phiMove, int r1, int r2);
struct twooftwo     find_error(int rMove, float phiMove, int r1, int r2, float rErr, float phiErr, int tfErr);
struct twoofthree   robo_find (int rMove, float phiMove, int r1, int r2, float rErr, float phiErr, int tfErr);

#endif //COMPASS_H