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

/*
 * Pin map with how used
 * 
 * 1  - VPP/MCLR/RE3                - [PROGRAMMER VPP]
 * 2  - RA0                         - [LDR ADC]
 * 3  - RA1                         - [LDR 2 ADC]
 * 4  - RA2                         - [Solar ADC]
 * 5  - RA3                         - [Solar Isolation toggle]
 * 6  - RA4                         - [ADC Toggle]
 * 7  - RA5                         - [NONE]
 * 8  - VSS                         - [+ 0V]
 * 9  - RA7                         - [XSHUT 1]
 * 10 - RA6                         - [XSHUT 2]
 * 11 - RC0                         - [NONE]
 * 12 - RC1                         - [NONE]      
 * 13 - RC2                         - [NONE]      
 * 14 - RC3                         - [NONE]         
 * 15 - RC4                         - [Enable Motors]
 * 16 - RC5                         - [NONE]      
 * 17 - RC6                         - [NONE]      
 * 18 - RC7                         - [NONE]
 * 19 - VSS                         - [+ 0V]
 * 20 - VDD                         - [+ 5V]
 * 21 - RB0                         - [R Motor Backwards]
 * 22 - RB1                         - [R Motor Forwards]
 * 23 - RB2                         - [L Motor Backwards]
 * 24 - RB3                         - [L Motor Forwards]
 * 25 - RB4                         - [SDA2 - I2C]
 * 26 - RB5                         - [SCL2 - I2C]
 * 27 - RB6/ICSPCLK                 - [TX2] THERE IS NO TX1
 * 28 - RB7/ICSPDAT                 - [RX2]
 */

#pragma warning disable 520
#pragma warning disable 2053
#pragma warning disable 1498
#include <xc.h>
#include "globals.h"
#include "Collision.h"
#include "ADC.h"

#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/mcc.h"
#include "VL53L0X.h"
#include "cereal.h"
#include "compass.h"
#include "motor.h"

void main(void) {
    SYSTEM_Initialize();
    
    while(1){
        spin_test();
        __delay_ms(2000);
        move_test();
        __delay_ms(2000);
    } // End of testing loop
    
    return;
}