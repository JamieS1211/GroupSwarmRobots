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
    int testa2 = test_ang_diff();
    // ...
    int testa3 = test_rice_calc();
    int testa4 = test_find_error();
    int testa5 = test_robo_find();
 
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

int test_ang_diff(){
    int y = 1;
    float test1 = ang_diff(1, 2);
    float test1_result = 1.0;
    
    if(test1 != test1_result){
        y = 0;
    }
    return y;
}

//...

int test_rice_calc() {
    int y = 1;
    struct twoangles test1 = rice_calc(500, 1, 2000, 1700);
    struct twoangles test1_result;
    test1_result.angA = 3.1244705;
    test1_result.angB = -1.1001899;
    
    if((test1.angA != test1_result.angA) && (test1.angB != test1_result.angB)) {
        y = 0;
    }
    
    return y;
}

int test_find_error() {
    int y = 1;
    struct twooftwo test1 = find_error(500, 1, 2000, 1700, 0.2, 0, 100);
//    struct twooftwo test1_result;
//    test1_result.group1.angA = -0.18259862;
//    test1_result.group1.angB = 0.25993082;
//    test1_result.group2.angA = -0.83425146;
//    test1_result.group2.angB = 0.99510324;
    
    return y;
}

int test_robo_find() {
    int y = 1;
    struct twoofthree test1 = robo_find(500, 1, 2000, 1700, 0.2, 0, 100);
    test1 = test1;
//    -2.8816618338040927
//    3.124470460808594
//    2.958994035065673
//
//    -0.834251461336172
//    -1.1001900280453456
//    -2.146489334641508
    
    return y;
}