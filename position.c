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
 * Returns angle as a value between -pi and pi
 */
float ang_scale(float theta)
/*
 * Scales angle between -pi and pi
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


/*
 * Returns shortest from ang1 to ang2
 * positive = aclk, negative = clk
 */
float ang_diff(float ang1, float ang2)
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
 * Finds angle overlap between two lists of angles 
 */
void ang_overlap();


/*
 * Finds angle overlap between two lists of two lists of angles 
 */
void ang2_overlap();


/*
 * Checks if angle inside list of 3 angles 
 */
void ang_within();


/*
 * Returns shortest rotation between two angles
 */
void ang_short(void);


/*
 * Returns if a polar coordinate lies in a circle with centre at polar position
 */
void polar_in_polar();


/*
 * Calculates the min and max error given values for error.
 */
struct twoangles rice_calc(int rMove, float phiMove, int r1, int r2)
/*
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


/*
 * Calculates the min and max error given values for error.
 */
struct twooftwo find_error(int rMove, float phiMove, int r1, int r2, float rErr, float phiErr, int tfErr)
/*
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

/*
 * Finds robot locations based on single transmission
 * Returns highest likely value with max and min
 */
struct twoofthree robo_find(int rMove, float phiMove, int r1, int r2, float rErr, float phiErr, int tfErr)
/*
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