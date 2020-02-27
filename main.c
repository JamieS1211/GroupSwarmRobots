/*
 * File:   main.c
 * Author: jamieshepherd
 *
 * Created on January 18, 2020, 6:02 PM
 */

/*
 * PIC 18F27k42
 * 
 * Data sheet
 * PIC18(L)F26/27/45/46/47/55/56/57K42
 */

#pragma warning disable 520
#pragma warning disable 2053
#pragma warning disable 1498

#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/mcc.h"
#include "VL53L0X.h"

void main(void) {
    SYSTEM_Initialize();
    OSCILLATOR_Initialize();
    PMD_Initialize();
    
    //LATBbits.LATB0 = 0; // Ensure manually controlled VL53L0X is off
    //__delay_ms(50);
    //VL53L0X_Change_Address(0x52, 0x00); // Change the address from default to 0
    //__delay_ms(50);
    //LATBbits.LATB0 = 1; // Re-enable manually controlled VL53L0X
    
    // Setup both VL53L0X modules
    //VL53L0X_Setup(0x00);
    VL53L0X_Setup(0x29);
    
    while(1) {
        __delay_ms(500);
        VL53L0X_ReadRange(0x29);
    }
    
    return;
}
