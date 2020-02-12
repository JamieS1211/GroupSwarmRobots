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
#include <stdbool.h>
#include <math.h>
#include "ADC.h"

// Deal with all light source management scripts
bool PowerFinding(void){
    //When battery is low check if good source in memory and nearby
    // if Solar voltage < threshold{
        // Read in environment memory
    
        // Check for location
        //If distance & Uncertainty < thresholds {
            //Call distance closing function}
        //else {
            // int count = 0;
            // While solarV < threshold & Iterations < max -  Repeat all up to max iterations or until solar threshold voltage is reached
    
            //Read ADC for all three sensors
            // int x0 = 0
            // int x1 = LDR Front
            //while x1 > x0
            // turn then x0= x1, then x1 = scan
            //Turn one step back after to undo difference 
            // While x1 > x0
            // Turn other way, x0 = x1, then x1 = scan
            //Turn back one step after to undo difference
            //Drive straight, check solar cell in intervals. Once it starts to drop again and two LDR are near balanced stop.
            // count = count + 1; Iterate count
    
    
    // else {
    //  sit and charge
    //}

    // If no source found check sensors - search until reasonable signal detected


    //Move in straight lines - Rapid LDR decline and similarity when perpendicular

    // Repeat until threshold solar voltage is reached 

    
    if (ADC_Read(2) < 600){ // ------------Check how this works as binary passed---------
        //if (knownSourceDistance < Threshold & sourceUncertainty < Threshold2){
            //move(requiredTurn(sourceAngle), sourceDistance)
        //}
        //else {
            
        //}
    }
    int iteration = 0;
    while (ADC_Read(2) < 800) {
        while (ADC_Read(2) < 600) {
            // Long range closing use LDR's
            int previous = ADC_Read(0);
            rotate(M_PI/6);
            while (ADC_Read(0)< previous){
                rotate(M_PI/6);
                previous = ADC_Read(0);
            }
            rotate(-M_PI/6);
            while (ADC_Read(0)< previous){
                rotate(-M_PI/6);
                previous = ADC_Read(0);
            }
            rotate(-M_PI/6);

            while (ADC_Read(0)<ADC_Read(1)){
                move(0, 5);
            }
        }
        //Short range closing using Solar
        if (ADC_Read(2) > 800){
            // Check if already ideal
            return true;
        }
        
        // --------   Check for improvement not for ultimate value
        
        while (iteration < 12){
            move(M_PI/6, 1);
            if (ADC_Read(2) > 800){
                return true;
            }
            move(M_PI,1);
            move(M_PI,0);
            iteration +=1;
        }
        
        // When max iterations reached move away:
        
        
    }
    return true;
}


//


float requiredTurn(float angle){
   float current = comp_head();
   
   if (M_PI>(angle - current) > 0){
       return angle - current;     
   }
   else if ((angle - current) >0){
       return -(2*M_PI - (angle - current));
   }
   else if ( M_PI>(current - angle) >0){
       return -(current - angle);
   }
   else if ((current - angle) > 0){
       return (2*M_PI - (current - angle));
   }
   else{
       return 0;
   }
}


// Crude functionality, will get close to LS. 
// And when to give up close finding to search somewhere else (How to do this) 
// Consider using differencing as well as single value? 
