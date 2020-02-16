/*
 * File:   position.h
 * Author: willrice
 *
 * Created on February 7, 2020, 22:00
 */

#ifndef POSITION_H
#define POSITION_H


//I'll probably write out the maths nicely else where


// Structures
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

/*
 * Returns angle as a value between -pi and pi
 */
float ang_scale(float theta);


/*
 * Returns shortest from ang1 to ang2
 * positive = aclk, negative = clk
 */
float ang_diff(float ang1, float ang2);


/*
 * Returns addition of two polar coordinates
 * To perform a subtraction multiply radiusB by -1
 */
struct polarcoord polar_add(int radiusA, float angleA, int radiusB, float angleB);


/*
 * Returns addition of two polar structures
 */
struct polarcoord polar_add_struct(struct polarcoord polarA, struct polarcoord polarB);


/*
 * Returns subtraction of two polar structures
 */
struct polarcoord polar_add_struct(struct polarcoord polarA, struct polarcoord polarB);


/*
 * Finds angle overlap between two lists of angles 
 */
struct twoofthree ang_overlap();


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
struct twoangles rice_calc(int rMove, float phiMove, int r1, int r2);


/*
 * Calculates the min and max error given values for error.
 */
struct twooftwo find_error(int rMove, float phiMove, int r1, int r2, float rErr, float phiErr, int tfErr);

/*
 * Finds robot locations based on single transmission
 * Returns highest likely value with aclk and clk
 */
struct twoofthree robo_find(int rMove, float phiMove, int r1, int r2, float rErr, float phiErr, int tfErr);

#endif //COMPASS_H