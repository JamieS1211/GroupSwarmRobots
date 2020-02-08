/*
 * File:   position.h
 * Author: willrice
 *
 * Created on February 7, 2020, 22:00
 */

#ifndef POSITION_H
#define POSITION_H


//I'll probably write out the maths nicely else where


/*
 * Finds robot locations based on single transmission
 */
void robo_find(int rMove);


/*
 * Finds angle overlap between two lists of angles 
 */
void ang_overlap(void, void);


/*
 * Finds angle overlap between two lists of two lists of angles 
 */
void ang2_overlap(void, void);


/*
 * Checks if angle inside list of angles 
 */
void ang_within(void, void);


/*
 * Returns angle as a value between -pi and pi
 */
void ang_scale(void);


/*
 * Returns angle as a value between -pi and pi
 */
void ang_scale(void);


/*
 * Returns clockwise and anticlockwise difference between angles
 */
void ang_diff(void, void);

/*
 * Returns shortest rotation between two angles
 */
void ang_short(void);

#endif //COMPASS_H