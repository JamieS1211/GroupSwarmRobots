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

#include <xc.h>
#include "globals.h"
#include "interrupts.h"

// Production -> set configuration bits
// CONFIG1L
#pragma config FEXTOSC = ECH    // External Oscillator Selection (EC (external clock) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC  // Reset Oscillator Selection (EXTOSC operating per FEXTOSC bits (device manufacturing default))

// CONFIG1H
#pragma config CLKOUTEN = OFF   // Clock out Enable bit (CLKOUT function is disabled)
#pragma config PR1WAY = ON      // PRLOCKED One-Way Set Enable bit (PRLOCK bit can be cleared and set only once)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

// CONFIG2L
#pragma config MCLRE = EXTMCLR  // MCLR Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
#pragma config PWRTS = PWRT_OFF // Power-up timer selection bits (PWRT is disabled)
#pragma config MVECEN = OFF      // Multi-vector enable bit (Multi-vector enabled, Vector table used for interrupts)
#pragma config IVT1WAY = ON     // IVTLOCK bit One-way set enable bit (IVTLOCK bit can be cleared and set only once)
#pragma config LPBOREN = OFF    // Low Power BOR Enable bit (ULPBOR disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG2H
#pragma config BORV = VBOR_2P45 // Brown-out Reset Voltage Selection bits (Brown-out Reset Voltage (VBOR) set to 2.45V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config DEBUG = OFF      // Debugger Enable bit (Background debugger disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period selection bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = ON        // WDT operating mode (WDT enabled regardless of sleep)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4L
#pragma config BBSIZE = BBSIZE_512// Boot Block Size selection bits (Boot Block size is 512 words)
#pragma config BBEN = OFF       // Boot Block enable bit (Boot block disabled)
#pragma config SAFEN = OFF      // Storage Area Flash enable bit (SAF disabled)
#pragma config WRTAPP = OFF     // Application Block write protection bit (Application Block not write protected)

// CONFIG4H
#pragma config WRTB = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-30000Bh) not write-protected)
#pragma config WRTC = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config WRTSAF = OFF     // SAF Write protection bit (SAF not Write Protected)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)

// CONFIG5L
#pragma config CP = OFF         // PFM and Data EEPROM Code Protection bit (PFM and Data EEPROM code protection disabled)


/*
 * Pin map with how used
 * 
 * 1  - VPP/MCLR/RE3                - [PROGRAMMER VPP]
 * 2  - RA0                         - [LDR ADC]
 * 3  - RA1                         - [LDR 2 ADC]
 * 4  - RA2                         - [Solar ADC]
 * 5  - RA3                         - [Solar Isolation toggle]
 * 6  - RA4                         - [NONE]
 * 7  - RA5                         - [SS1 SPI]
 * 8  - VSS                         - [+ 5V]
 * 9  - RA7                         - [NONE]
 * 10 - RA6                         - [NONE]
 * 11 - RC0                         - [NONE]
 * 12 - RC1                         - [NONE]
 * 13 - RC2                         - [NONE]
 * 14 - RC3                         - [SCK1 SPI]
 * 15 - RC4                         - [SDI1 SPI]
 * 16 - RC5                         - [NONE]
 * 17 - RC6                         - [NONE]
 * 18 - RC7                         - [NONE]
 * 19 - VSS                         - [+ 0V]
 * 20 - VDD                         - [+ 5V]
 * 21 - RB0                         - [NONE]
 * 22 - RB1                         - [SCL2 I2C]
 * 23 - RB2                         - [SDA2 I2C]
 * 24 - RB3                         - [NONE]
 * 25 - RB4                         - [NONE]
 * 26 - RB5                         - [NONE]
 * 27 - RB6/ICSPCLK                 - [NONE]
 * 28 - RB7/ICSPDAT                 - [NONE]
 */

void main(void) {
    interrupts_Setup(); // Last setup function
    
    while(1);
    
    return;
}
