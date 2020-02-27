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
#include <xc.h>
#include "globals.h"
#include "interrupts.h"
#include "i2c.h"
#include "testing.h"
#include "Collision.h"
#include "Lidar.h"
#include "ADC.h"

#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/mcc.h"
#include "VL53L0X.h"
#include "cereal.h"

void main(void) {
    SYSTEM_Initialize();
    OSCILLATOR_Initialize();
    PMD_Initialize();
    UART2_Initialize();
    
    //LATBbits.LATB0 = 0; // Ensure manually controlled VL53L0X is off
    //__delay_ms(50);
    //VL53L0X_Change_Address(0x52, 0x00); // Change the address from default to 0
    //__delay_ms(50);
    //LATBbits.LATB0 = 1; // Re-enable manually controlled VL53L0X
    
    // Setup both VL53L0X modules
    //VL53L0X_Setup(0x00);
    VL53L0X_Setup(0x29);
    
    while(1){
        uint16_t value = ADC_Read(0);
        if (value > 1000){
            TRISAbits.TRISA5 = 0;
            LATAbits.LATA5 = 1;
        }
        else{
            TRISAbits.TRISA5 = 0;
            LATAbits.LATA5 = 0;
        }
        uint16_t value2 = ADC_Read(1);
        if (value2 > 1000){
            TRISAbits.TRISA6 = 0;
            LATAbits.LATA6 = 1;
        }
        else{
            TRISAbits.TRISA6 = 0;
            LATAbits.LATA6 = 0;
        }
    }
    
    return;
}