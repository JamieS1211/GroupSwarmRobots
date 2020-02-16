/*
 * File:   testing.h
 * Author: willrice
 *
 * Created on February 11, 2020, 20:13
 */

#ifndef TESTING_H
#define TESTING_H

/*
 * Tests all functions
 */
void test_all();

// Position testing
int test_ang_scale();
int test_ang_diff();
int test_polar_add();
int test_ang_overlap();
// ...
int test_rice_calc();
int test_find_error();
int test_robo_find();

#endif //COMPASS_H