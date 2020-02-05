/*
 * File:   LSM.c
 * Author: poult
 *
 * Created on 20 January 2020, 17:34
 */

#define _XTAL_FREQ 20000000

#include <xc.h>
#include <pic18f27K42.h>
#include <stdbool.h>

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

}


//
