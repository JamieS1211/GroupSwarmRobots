/*
 * File:   LSM.c
 * Author: poult
 *
 * Created on 20 January 2020, 17:34
 */

#define _XTAL_FREQ 20000000
#define M_PI acos(-1.0)

#include <xc.h>
#include <pic18f27K42.h>
#include "globals.h"
#include "ADC.h"
#include "compass.h"
#include "motor.h"

// Deal with all light source management scripts

bool PowerFinding(void) {

    //if (ADC_Read(2) < 600){ // ------------Check how this works as binary passed---------
    //if (knownSourceDistance < Threshold & sourceUncertainty < Threshold2){
    //    move(requiredTurn(sourceAngle), sourceDistance)
    //}
    //else {

    //}
    //}

    uint8_t iteration = 0;
    while (ADC_Read(2) < 800) {
        while (ADC_Read(2) < 600) {
            // Long range closing use LDR's
            //            int previous = ADC_Read(0);
            //            //motor_spin(M_PI/6);
            //            while (ADC_Read(0)< previous){
            //                //motor_spin(M_PI/6);
            //                previous = ADC_Read(0);
            //            }
            //            //motor_spin(-M_PI/6);
            //            while (ADC_Read(0)< previous){
            //                //motor_spin(-M_PI/6);
            //                previous = ADC_Read(0);
            //            }
            //            //motor_spin(-M_PI/6);
            //            while (ADC_Read(0)<ADC_Read(1)){
            //                //motor_spin(0, 5);
            //            }
            uint8_t i;
            uint16_t current = ADC_Read(0);
            uint8_t bestPos = 0;
            for (i = 1; i < 11; i++) {
                motor_spin(M_PI / 6);
                if (ADC_Read(0) > current) {
                    bestPos = i;
                    current = ADC_Read(0);
                }

            }
            motor_spin((M_PI / 6)*(bestPos+1)); // --------- Check not overturning --------------
            while ((ADC_Read(0) - ADC_Read(1)) > 0.1*ADC_Read(0) && ADC_Read(2) < 800) {
                move_dist(0, 1, 0);
            }
            
        }

        //Short range closing using Solar
        if (ADC_Read(2) > 800) {
            // Check if already ideal
            return true;
        }

        // --------   Check for improvement not for ultimate value

        while (iteration < 12) {
            //move_dist(M_PI/6, 1, 0); 
            if (ADC_Read(2) > 800) {
                return true;
            }
            //move_dist(M_PI,1, 0);
            //move_dist(M_PI,0, 0);
            iteration += 1;
        }

        // When max iterations reached move away:
    }

    return true;
}

float requiredTurn(float angle) {
    float current = comp_head();

    if (M_PI > (angle - current) > 0) {
        return angle - current;
    } else if ((angle - current) > 0) {
        return -(2 * M_PI - (angle - current));
    } else if (M_PI > (current - angle) > 0) {
        return -(current - angle);
    } else if ((current - angle) > 0) {
        return (2 * M_PI - (current - angle));
    } else {
        return 0;
    }
}


// Crude functionality, will get close to LS. 
// And when to give up close finding to search somewhere else (How to do this) 
// Consider using differencing as well as single value? 
// Full spin to find ideal point to prevent Rear light intensity increase issue
