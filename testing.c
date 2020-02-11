/*
 * File:   testing.c
 * Author: willrice
 *
 * Created on February 11, 2020, 20:13
 */


#include <xc.h> // Think is library type thing

#include "globals.h"
#include "testing.h"

// testing modules
#include "position.h"

void test_all(){
 /*
 * Tests all functions
 */
    int testa1 = test_ang_scale();
 
}

int test_ang_scale(){
    int y = 1;
    float test1 = ang_scale(10);
    float test1_result = -2.566371;
    if(test1 != test1_result){
        y = 0;
    }
    float test2 = ang_scale(-10);
    float test2_result = 2.566371;
    if(test2 != test2_result){
        y = 0;
    }
    return y;
}