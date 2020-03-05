/*
 * File:   ADC.c
 * Author: poult
 *
 * Created on 20 January 2020, 17:34
 */

#define _XTAL_FREQ 20000000

#include <xc.h>
#include <pic18f27K42.h>
#include "ADC.h"
// Pages 602 - 619 - 639 in data sheet

/*
 * Function sets up all ADC (Analog to Digital converter) settings.
 */
void ADC_Setup(void) {
    // Setup ADC
    // FVRCON [Fixed Reference Voltage Set-up] - page 599
    FVRCONbits.CDAFVR = 0b10; // Set to 2.048V
    FVRCONbits.ADFVR = 0b10; // Set to 2.048V
    FVRCONbits.EN = 1; // Turn on fixed reference voltage
    FVRCONbits.CDAFVR = 0b10; // Set to 2.048V
    FVRCONbits.ADFVR = 0b10; // Set to 2.048V
    while (FVRCONbits.RDY == 0) {
        __delay_ms(20);
    }
    
    // ADCON0 [ADC Control Register 0] - page 619
    ADCON0bits.CS = 1; // ADCRC Clock - Dedicated 600KHz clock for ADC module
    ADCON0bits.FM = 1; // Right justify results
      
    // TRISx [Tri-state control register] - page 265
    
    
    // UPDATE FOR NEW PINS TOO!!!!---------------------------------
    TRISAbits.TRISA0 = 1; // Set RA0 to Input
    TRISAbits.TRISA1 = 1; // Set RA1 to Input
    TRISAbits.TRISA2 = 1; // Set RA2 to Input
    TRISCbits.TRISC0 = 1; // Set RC0 to Input
    TRISAbits.TRISA3 = 0; // Set RA3 to Output
    TRISAbits.TRISA4 = 0; // Set RA4 to Output
    
    // ANSELA [Analog select port registers] - page 267
    ANSELAbits.ANSELA0 = 1; // Set RA0 as analog channel
    ANSELAbits.ANSELA1 = 1; // Set RA1 as analog channel
    ANSELAbits.ANSELA2 = 1; // Set RA2 as analog channel
    ANSELCbits.ANSELC0 = 1; // Set RC0 as analog channel
            
}

/*
 * Sets up the item to be sampled by the ADC
 * Passed x to define item
 */
void ADC_DestinationSetup(uint8_t x) {
    if (x == 0) {
        // Power LDR
        LATAbits.LATA4 = 1;
        // ADPCH [ADC Channel selection register] - page 625
        ADPCH = 0x00; // RA0 is selected
    } else if (x == 1) {
        // Power LDR
        LATAbits.LATA4 = 1;
        // ADPCH [ADC Channel selection register] - page 625
        ADPCH = 000001; // RA1 is selected
    } else if (x == 2) {
        //Isolate Solar Panel
        LATAbits.LATA3 = 1;
        // ADPCH [ADC Channel selection register] - page 625
        ADPCH = 000002; // RA2 is selected
    } else if (x ==3){
        //Isolate Solar Panel
        LATAbits.LATA3 = 1;
        // ADPCH [ADC Channel selection register] - page 625
        ADPCHbits.ADPCH = 0b10000; // ----------------------FIX PIN ALLOCATION!!!!!!!!!--------------------
    
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
int ADC_Read(uint8_t x) {
    /*
     * x = 0 - LDR1 (RA0)
     * x = 1 - LDR2 (RA1) 
     * x = 2 - Solar Panel (RA2)
     * x = 3 - Battery (------------------------Determine)
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
    
    if (PORTAbits.RA3 == 1){
        LATAbits.LATA3 = 0;   // Toggle solar isolation pin
    }
    if (PORTAbits.RA4 ==1){
        LATAbits.LATA4 = 0;
    }
    return (ADRESH << 8) + ADRESL;
}

