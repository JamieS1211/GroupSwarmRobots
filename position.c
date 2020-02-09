/*
 * File:   compass.c
 * Author: willrice
 *
 * Created on February 7, 2020, 22:15
 */


#include <xc.h> // Think is library type thing

#include "globals.h"
#include "position.h"
#include "math.h"
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
void rice_calc(int rMove, float phiMove, int r1, int r2)
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
    float yx1 = +((xrel*(xrel*root + yrel*gam))/(-yrel*(xrel*root - yrel*gam) + pow(m,2)*gam) );
    float yx2 = -((xrel*(xrel*root - yrel*gam))/(+yrel*(xrel*root - yrel*gam) + pow(m,2)*gam) );
    
    // Calculating angles
    float theta1 = atan(yx1);
    float theta2 = atan(yx2); 
    
    // Need to return
}


/*
 * Calculates the min and max error given values for error.
 */
void find_error(int rMove, float phiMove, int r1, int r2, float rErr, float phiErr, int tfErr)
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
    rice_calc(max_move, phiMove, r1, r2);
    rice_calc(min_move, phiMove, r1, r2);
    
    // Returning
    // return [max_angle, min_angle]
}

/*
 * Finds robot locations based on single transmission
 * Returns highest likely value with max and min
 */
void robo_find(int rMove, float phiMove, int r1, int r2, float rErr, float phiErr, int tfErr)
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
    // Must call error calc first
    // errorcalc(rMove, phiMove, r1, r2, rErr, phiErr, tfErr);
    // rice_calc(rMove, phiMove, r1, r2);
    
    // Reformatting
    // Shouldn't need to reformat depending on directory setup
    // Should just need to call the two functions
}
