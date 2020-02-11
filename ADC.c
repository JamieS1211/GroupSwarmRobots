/*
 * File:   ADC.c
 * Author: poult
 *
 * Created on 20 January 2020, 17:34
 */

#define _XTAL_FREQ 20000000

#include <xc.h>
#include <pic18f27K42.h>

// Pages 602 - 619 - 639 in data sheet

/*
 * Function sets up all ADC (Analog to Digital converter) settings.
 */
void ADC_Setup(void) {
    // Setup ADC for LDR
    
    // ADCON0 [ADC Control Register 0] - page 619
    ADCON0bits.CS = 1; // ADCRC Clock - Dedicated 600KHz clock for ADC module
    ADCON0bits.FM = 1; // Right justify results
      
    // TRISx [Tri-state control register] - page 265
    TRISAbits.TRISA0 = 1; // Set RA0 to Input
    
    // ANSELA [Analog select port registers] - page 267
    ANSELAbits.ANSELA0 = 1; // Set RA0 as analog channel
            
}

/*
 * Sets up the item to be sampled by the ADC
 * Passed x to define item
 */
void ADC_DestinationSetup(int x) {
    if (x == 0) {
        // ADPCH [ADC Channel selection register] - page 625
        ADPCH = 0x00; // RA0 is selected
    } else if (x == 1) {
        // ADPCH [ADC Channel selection register] - page 625
        ADPCH = 000001; // RA1 is selected
    } else if (x == 2) {
        // ADPCH [ADC Channel selection register] - page 625
        ADPCH = 000002; // RA2 is selected
        // ---------- Set RA3 High ---------
    } else {
        // ------- Throw Error Here -------
    }
    
    // ADCON0 [ADC Control Register 0] - page 619
    ADCON0bits.ON = 1; // ON - ADC Enable
   __delay_ms(20);
}

/*
 * Contains code to sample ADC - measuring light levels 
 * Passed x to specify item to sample
 */
int ADC_Read(int x) {
    /*
     * x = 0 - LDR1 (RA0)
     * x = 1 - LDR2 (RA1) 
     * x = 2 - Solar Panel (RA2)
     */
    
    //Check if ADC_Setup has run
    // ADCRC Clock, ADCON0 [ADC Control Register 0] - page 619
    if (ADCON0bits.CS == 1){
        ADC_DestinationSetup(x); // Setup Destination for sampling, pass x
    }
    else {
        ADC_Setup(); // Perform initial ADC setup
        ADC_DestinationSetup(x); // Setup Destination for sampling, pass x
    }
        
    // ADCON0 [ADC Control Register 0] - page 619
    ADCON0bits.GO = 1; // ADC Enable bit
    
    while (ADCON0bits.GO); // Wait until ADC conversion completes
    ADCON0bits.ON = 0; // Turn back off ADC
//    if (RA3 = High){
//        RA3 = Low; // ---------- Fix; Toggle solar isolation pin --------
//    }
    return (ADRESH << 4) + ADRESL;
}

