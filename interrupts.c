/*
 * File:   interrupts.c
 * Author: jamieshepherd
 *
 * Created on January 18, 2020, 6:09 PM
 */


#include <xc.h>

// Pages 115 - 135 - 169 in data sheet

/*
 * Function sets up all interrupt settings.
 */
void interrupts_Setup(void) {
    
    //INTCON0 [Interrupt Control Register 0] - page 135
    INTCON0bits.GIE = 1; // GIE - Global interrupt Enable bits
    
    //PIE3 [Peripheral interrupt enable register 3] - page 150
    PIE3bits.TMR0IE = 1;
    
}



/*
 * Function should be called on an interrupt.
 * Contains code for each type of interrupt and clears interrupt after handling.
 */
void __interrupt() interrupts_Event(void) {
    
    if (PIE9bits.TMR6IE && PIR9bits.TMR6IF) {
        // Stop movement forwards
        motor_stop();
        // Read compass
        
        // Read LiDAR
        
        // Make decision
        
        // Turn
        motor_spin();
        
        // Move forwards
        motor_move();
        
        // TMR6 Interrupt - must be software cleared
        PIR9bits.TMR6IF = 0; // Reset timer (?)
    }
}
