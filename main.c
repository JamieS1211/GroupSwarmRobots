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
 * 12 - RC1                         - [NONE] ?      THE BEN ZONE
 * 13 - RC2                         - [NONE] ?      ------------
 * 14 - RC3                         - [SCK1 SPI] ?  ------------
 * 15 - RC4                         - [SDI1 SPI] ?  ------------
 * 16 - RC5                         - [NONE] ?      ------------
 * 17 - RC6                         - [NONE] ?      ------------
 * 18 - RC7                         - [NONE]
 * 19 - VSS                         - [+ 0V]
 * 20 - VDD                         - [+ 5V]
 * 21 - RB0                         - [GPI0]
 * 22 - RB1                         - [SDO1]
 * 23 - RB2                         - [SDI1 - SPI]
 * 24 - RB3                         - [SCK1 - SPI]
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

void main(void) {
    SYSTEM_Initialize();
    OSCILLATOR_Initialize();
    PMD_Initialize();
    comp_reset();
    cereal_str("Initialize Complete$");
    
    LATBbits.LATB0 = 0; // Ensure manually controlled VL53L0X is off
    __delay_ms(50);
    VL53L0X_Change_Address(0x29, 0x28); // Change the address from default to 0
    __delay_ms(50);
    LATBbits.LATB0 = 1; // Re-enable manually controlled VL53L0X
    __delay_ms(50);
    
    // Setup both VL53L0X modules
    VL53L0X_Setup(0x28);
    //VL53L0X_Setup(0x29);
    
    
    // While loop testing ADC then Lidar then compass
    while(1){
        
//        // ADC testing
//        uint16_t value = ADC_Read(0);
//        if (value > 1000){
//            TRISAbits.TRISA5 = 0;
//            LATAbits.LATA5 = 1;
//        }
//        else{
//            TRISAbits.TRISA5 = 0;
//            LATAbits.LATA5 = 0;
//        }
//        uint16_t value2 = ADC_Read(1);
//        if (value2 > 1000){
//            TRISAbits.TRISA6 = 0;
//            LATAbits.LATA6 = 1;
//        }
//        else{
//            TRISAbits.TRISA6 = 0;
//            LATAbits.LATA6 = 0;
//        }
//        
        // Lidar Testing
        
        //uint16_t VL53L0X_2_dist = VL53L0X_ReadRange(0x29);
        uint16_t VL53L0X_1_dist = VL53L0X_ReadRange(0x28);
        
        //cereal_uint16_t(VL53L0X_2_dist);
        cereal_uint16_t(VL53L0X_1_dist);
        //uint16_t bread = VL53L0X_ReadRange(0x00);
        //cereal_uint16_t(bread);
//        uint16_t pizza = ADC_Read(0);
//        pizza = round(pizza/1.092);

        __delay_ms(1000);
        
    } // End of testing loop
    
    return;
}