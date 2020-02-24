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
            int previous = ADC_Read(0);
            motor_spin(M_PI/6);
            while (ADC_Read(0)< previous){
                motor_spin(M_PI/6);
                previous = ADC_Read(0);
            }
            motor_spin(-M_PI/6);
            while (ADC_Read(0)< previous){
                motor_spin(-M_PI/6);
                previous = ADC_Read(0);
            }
            motor_spin(-M_PI/6);

            while (ADC_Read(0)<ADC_Read(1)){
                motor_spin(0, 5);
            }
        }
        //Short range closing using Solar
        if (ADC_Read(2) > 800){
            // Check if already ideal
            return true;
        }
        
        // --------   Check for improvement not for ultimate value
        
        while (iteration < 12){
            move_dist(M_PI/6, 1, 0); 
            if (ADC_Read(2) > 800){
                return true;
            }
            move_dist(M_PI,1, 0);
            move_dist(M_PI,0, 0);
            iteration +=1;
        }
        
        // When max iterations reached move away:
        
        
    }
    return true;
}




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
