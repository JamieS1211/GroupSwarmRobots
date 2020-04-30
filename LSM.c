/*
 * File:   LSM.c
 * Author: poult
 *
 * Created on 20 January 2020, 17:34
 */

#define M_PI acos(-1.0)

#include "mcc_generated_files/mcc.h"
#include <xc.h>
#include <pic18f27K42.h>
#include "globals.h"
#include "ADC.h"
#include "compass.h"
#include "motor.h"
#include "cereal.h"

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
    uint8_t iteration2 =0;
    uint8_t lightLevel = 0;
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
            cereal_str("Long distance closure$");
            cereal_str("Finding best direction$");
            for (i = 1; i < 11; i++) {
                motor_spin(M_PI / 6);
                if (ADC_Read(0) < current) {
                    bestPos = i;
                    current = ADC_Read(0);
                }

            }
            cereal_str("Turning to best direction$");
            motor_spin((M_PI / 6)*(bestPos+1)); // --------- Check not overturning --------------
            cereal_str("Moving until perpendicular$");
            while (abs(ADC_Read(0) - ADC_Read(1)) > 0.1*ADC_Read(0) && ADC_Read(2) < 800) {
                move_coll(0, 20, 0);
                // ---------------------------------Iteration Limit -----------------------------------------
            }
            cereal_str("Perpendicular$");
        }

        //Short range closing using Solar
        if (ADC_Read(2) > 800) {
            // Check if already ideal
            return true;
        }

        cereal_str("Optimising position$");
        lightLevel = ADC_Read(2);
        while (iteration2 < 20){
            while (iteration < 12) {
                move_dist(M_PI/6, 10, 0); 

                if (ADC_Read(2) > 800) {
                    return true;
                }
                else if (ADC_Read(2)>lightLevel + 5){
                    lightLevel = ADC_Read(2);
                    break;
                }
                else{
                    move_dist(M_PI, 10, 0);
                    motor_spin(M_PI);
                }
                iteration += 1;
            }
            if (iteration == 12){
                cereal_str("Unable to Optimise$");
                break;
            }
            iteration =0;
            iteration2+=1;
            cereal_str("Source not viable$");
        }
        // When max iterations reached move away:
        iteration = 0;
        iteration2 = 0;
        cereal_str("Optimisation Failed$");
        cereal_str("Finding new source$");
        move_dist(M_PI, 300, 0);
        
        while (ADC_Read(1)< ADC_Read(0) && iteration < 50) {
            move_dist(0, 450, 0);
            iteration+=1;
        }
        iteration =0;
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
