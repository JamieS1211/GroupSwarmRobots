/*
 * File:   compass.c
 * Author: willrice
 *
 * Created on February 7, 2020, 22:15
 */


#include <xc.h> // Think is library type thing

#include "globals.h"
#include "position.h"
#include "stdlib.h"

//I'll probably write out the maths nicely else where

/*
 * ------------------------
 * --- envMem Functions ---
 * ------------------------
 */
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

/*
 * ------------------------
 * ---- Math Functions ----
 * ------------------------
 */
float ang_scale(float theta)
/*
 * Returns angle as a value between -pi and pi
 */
{
    while(1) {
        if (theta <= -M_PI) {
            theta = theta + 2*M_PI;
        }
        else if (theta > M_PI) {
            theta = theta - 2*M_PI;
        }
        else {
            break;
        }
    }
    return theta;
}

float ang_diff(float ang1, float ang2)
/*
 * Returns shortest from ang1 to ang2
 * positive = aclk, negative = clk
 */
{
    // Ensuring angles in correct range
    ang1 = ang_scale(ang1);
    ang2 = ang_scale(ang2);
    
    // Calculating both directions
    float diff1 = ang_scale(ang2 - ang1);
    float diff2 = ang_scale(ang2 - ang1 + 2*M_PI);
    
    // Finding smallest and returning
    if (abs(diff1) < abs(diff2)) {
        return diff1;
    }
    else {
        return diff2;
    }
}

/*
 * ------------------------
 * --- struct Functions ---
 * ------------------------
 */
struct polarcoord polar_add(int radiusA, float angleA, int radiusB, float angleB)
/* Returns addition of two polar coordinates
 * To perform a subtraction multiply radiusB by -1
 * 
 * Parameters
 * ----------
 * radiusA
 *      int in mm.
 * angleA
 *      Angle in radians.
 * radiusB
 *      int in mm. Multiply by -1 to perform polar subtraction.
 * angleB
 *      Angle in radians.
 * 
 * Returns
 * -------
 * struct polarcoord
 *      int radius;
 *      float angle;
 */
{
    struct polarcoord out;
    
    // https://math.stackexchange.com/questions/1365622/adding-two-polar-vectors
    out.radius = round(sqrt(pow(radiusA,2)+pow(radiusB,2)+(2*radiusA*radiusB*cos(angleB-angleA))));
    out.angle = angleA + atan2(radiusB*sin(angleB-angleA),radiusA+(radiusB*cos(angleB-angleA)));
    
    return out;
}

struct polarcoord polar_add_struct(struct polarcoord polarA, struct polarcoord polarB)
/* Returns addition of two polar structures
 * 
 * Parameters
 * ----------
 * polarA
 *      int radius;
 *      float angle;
 * polarB
 *      int radius;
 *      float angle;
 * 
 * Returns
 * -------
 * struct polarcoord
 *      int radius;
 *      float angle;
 */
{
    struct polarcoord out = polar_add(polarA.radius, polarA.angle, polarB.radius, polarB.angle);
    return out;
}

struct polarcoord polar_sub_struct(struct polarcoord polarA, struct polarcoord polarB)
/* Returns subtraction of two polar structures
 * 
 * Parameters
 * ----------
 * polarA
 *      int radius;
 *      float angle;
 * polarB
 *      int radius;
 *      float angle;
 * 
 * Returns
 * -------
 * struct polarcoord
 *      int radius;
 *      float angle;
 */
{
    struct polarcoord out = polar_add(polarA.radius, polarA.angle, (-1)*polarB.radius, polarB.angle);
    return out;
}


/*
 * ------------------------
 * ---- awful Functions ---
 * ------------------------
 */
struct twoofthree ang_overlap(struct threeangles listA, struct threeangles listB)
/*
 * returns overlap. Don't ask how it works
 */
{
    // Defining calc variables and scaling
    float A_aclk = ang_scale(listA.offset_aclk);
    float A_mean = ang_scale(listA.mean);
    float A_clk = ang_scale(listA.offset_clk);
    
    float B_aclk = ang_scale(listB.offset_aclk);
    float B_mean = ang_scale(listB.mean);
    float B_clk = ang_scale(listB.offset_clk);
    
    // If anticlockwise of A_aclk, move clockwise one full rotation
    // I know writing a function would look nicer but angles hurt my brain
    if (A_aclk < A_mean) {
        A_mean -= 2*M_PI;
    }
    if (A_aclk < A_clk) {
        A_clk -= 2*M_PI;
    }
    if (A_aclk < B_aclk) {
        B_aclk -= 2*M_PI;
    }
    if (A_aclk < B_mean) {
        B_mean -= 2*M_PI;
    }
    if (A_aclk < B_clk) {
        B_clk -= 2*M_PI;
    }
    
    float bounds[2][3] = {0};
    //       A         A    B       B
    //       ?        ?   ?      ?
    if ((A_aclk-A_clk < A_aclk-B_aclk) & (A_aclk-A_clk < A_aclk-B_clk)) {
    }
    //       A    B    A    B
    //       ?   ?###?   ?
    else if ((A_aclk - A_clk >= A_aclk-B_aclk) && (A_aclk-A_clk < A_aclk-B_clk)) {
        bounds[0][0] = B_aclk;
        bounds[0][2] = A_aclk;
    }
    //       A  B   B  A
    //       ? ?##? ?
    else if ((A_aclk-B_clk >= A_aclk-B_aclk) && (A_aclk-B_clk < A_aclk-A_clk)) {
        bounds[0][0] = B_aclk;
        bounds[0][2] = B_clk;
    }
    //       A  B      A    B
    //       ?#?     ?   ?
    else if ((A_aclk-B_clk < A_clk-B_aclk) && (A_aclk-A_clk < A_aclk-B_aclk)) {
        bounds[0][0] = A_aclk;
        bounds[0][2] = B_clk;
    }
    //       A  B   B  A
    //       ?#?  ?#?
    else {
        bounds[0][0] = A_aclk;
        bounds[0][2] = B_clk;
        bounds[1][0] = B_aclk;
        bounds[1][2] = A_clk;
    }
    
    // Looping through solutions to find mid points
    for(int i = 0; i < sizeof(bounds)/sizeof(bounds[0]); i++){
        // Find the mean value
        float denom = (bounds[i][0] + A_mean - B_mean - bounds[i][2]);
        if ( abs(denom) < 0.0001) {
            bounds[i][1] = (bounds[i][0] + bounds[i][2])/2;
        }
        else {
            bounds[i][1] = (bounds[i][0]*A_mean - B_mean*bounds[i][2])/(bounds[i][0] + A_mean - B_mean - bounds[i][2]);
        }
    }
    
    // formatting and returning
    struct twoofthree out;
    // Check if not empty
    if (bounds[0][0]!=0 || bounds[0][2]!=0) {
        out.group1.offset_aclk = bounds[0][0];
        out.group1.mean = bounds[0][1];
        out.group1.offset_clk = bounds[0][2];
        
        // Check if not empty but if first array empty then second array empty
        if (bounds[0][0]!=0 || bounds[1][2]!=0) {
            out.group2.offset_aclk = bounds[1][0];
            out.group2.mean = bounds[1][1];
            out.group2.offset_clk = bounds[1][2];
        }
    }
    return out;
}

struct twoangles rice_calc(int rMove, float phiMove, int r1, int r2)
/* Calculates the min and max error given values for error.
 * 
 * Parameters
 * ----------
 * rMove
 *      Radius of polar coordinate of relative movement.
 * phiMove
 *      Angle in radians of relative movement.
 * r1
 *      Old transmission distance.
 * r2
 *      Most recent transmission distance.
 * 
 * Returns
 * -------
 * theta1, theta2
 *      Possible angles of other robot
 */
{
    // Defining
    int m = rMove;
    int xrel = round(rMove*cos(phiMove));
    int yrel = round(rMove*sin(phiMove));
    float gam = -pow(r1,2)+pow(r2,2)+pow(m,2);
    
    // Ensuring root returns a real number (sometime close to zero due to rounding)
    float inroot = -( pow(r1-r2,2)-pow(m,2) )*( pow(r1+r2,2)-pow(m,2) );
    float root = 0;
    if (inroot > 0) {
        root = sqrt(inroot);
    }
    
    // Calculating values for y/x
    float y1 = +(xrel*(xrel*root + yrel*gam));
    float y2 = -(xrel*(xrel*root - yrel*gam));
    float x1 = -yrel*(xrel*root - yrel*gam) + pow(m,2)*gam;
    float x2 = +yrel*(xrel*root - yrel*gam) + pow(m,2)*gam;
    
    // Need to return
    struct twoangles out;
    out.angA = atan2(y1,x1);
    out.angB = atan2(y2,x2);
    
    return out;
}

struct twooftwo find_error(int rMove, float phiMove, int r1, int r2, float rErr, float phiErr, int tfErr)
/* Calculates the min and max error given values for error.
 * 
 * Parameters
 * ----------
 * rMove
 *      Radius of polar coordinate of relative movement.
 * phiMove
 *      Angle in radians of relative movement.
 * r1
 *      Old transmission distance.
 * r2
 *      Most recent transmission distance.
 * rErr
 *      Percent error (0.02 for 2%).
 * phiErr
 *      Angle error in radians.
 * tfErr
 *      Transmission error in mm.
 * 
 * Returns
 * -------
 * [max_angle, min_angle]
 *      Each composed of a length 2 list from ricecalc
 */
{
    // Max rMove with error
    int max_move = (rMove*(1+rErr))+tfErr;
    int min_move = (rMove*(1-rErr))-tfErr;
    
    // r2-r1 < move < r2+r1 (limits)
    if(max_move < r2-r1) {
        max_move = r2-r1;
    }
    else if(max_move > r2+r1) {
        max_move = r2+r1;
    }
    if(min_move < r2-r1) {
        min_move = r2-r1;
    }
    else if(min_move > r2+r1) {
        min_move = r2+r1;
    }
    
    // Large Error
    struct twoangles error1 = rice_calc(max_move, phiMove, r1, r2);
    struct twoangles error2 = rice_calc(min_move, phiMove, r1, r2);
    
    // Reformatting and returning
    struct twooftwo out;
    out.group1.angA = error1.angA;
    out.group1.angB = error2.angA;
    out.group2.angA = error1.angB;
    out.group2.angB = error2.angB;
    
    return out;
}

struct twoofthree robo_find(int rMove, float phiMove, int r1, int r2, float rErr, float phiErr, int tfErr)
/* Finds robot locations based on single transmission
 * Returns highest likely value with max and min
 * 
 * Parameters
 * ----------
 * rMove
 *      Radius of polar coordinate of relative movement.
 * phiMove
 *      Angle in radians of relative movement.
 * r1
 *      Old transmission distance.
 * r2
 *      Most recent transmission distance.
 * rErr
 *      Percent error (0.02 for 2%).
 * phiErr
 *      Angle error in radians.
 * tfErr
 *      Transmission error in mm.
 * 
 * Returns
 * -------
 * 2x3 values
 *      Returns two lists with the format
 *          Offset1
 *          Mode
 *          Offset2
 */
{
    // Calculate mode and error
    struct twoangles mode = rice_calc(rMove, phiMove, r1, r2);
    struct twooftwo offset = find_error(rMove, phiMove, r1, r2, rErr, phiErr, tfErr);
    
    // Reformatting
    struct threeangles directionA;
    struct threeangles directionB;
    
    directionA.mean = mode.angA;
    directionB.mean = mode.angB;
    
    // min is anticlockwise from mid
    // max is clockwise from mid
    if (abs(ang_diff(mode.angA, offset.group1.angA))<abs(ang_diff(mode.angA, offset.group1.angB))) {
        if (ang_diff(mode.angA, offset.group1.angA)<0) {
            directionA.offset_aclk = offset.group1.angB;
            directionA.offset_clk = offset.group1.angA;
        }
        else {
            directionA.offset_aclk = offset.group1.angA;
            directionA.offset_clk = offset.group1.angB;
        }
    }
    else {
        if (ang_diff(mode.angA, offset.group1.angB)>0) {
            directionA.offset_aclk = offset.group1.angB;
            directionA.offset_clk = offset.group1.angA;
        }
        else {
            directionA.offset_aclk = offset.group1.angA;
            directionA.offset_clk = offset.group1.angB;
        }
    }
    
    if (abs(ang_diff(mode.angB, offset.group2.angA))<abs(ang_diff(mode.angB, offset.group2.angB))) {
        if (ang_diff(mode.angB, offset.group2.angA)<0) {
            directionB.offset_aclk = offset.group2.angB;
            directionB.offset_clk = offset.group2.angA;
        }
        else {
            directionB.offset_aclk = offset.group2.angA;
            directionB.offset_clk = offset.group2.angB;
        }
    }
    else {
        if (ang_diff(mode.angB, offset.group2.angB)>0) {
            directionB.offset_aclk = offset.group2.angB;
            directionB.offset_clk = offset.group2.angA;
        }
        else {
            directionB.offset_aclk = offset.group2.angA;
            directionB.offset_clk = offset.group2.angB;
        }
    }
    
    // Creating output structure
    struct twoofthree out;
    out.group1 = directionA;
    out.group2 = directionB;
    
    return out;
}