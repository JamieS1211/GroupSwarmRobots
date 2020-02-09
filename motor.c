/*
 * File:   motor.c
 * Author: bendickinson
 *
 * Created on February 07, 2020, 15:40 PM
 */

#include <xc.h>

#include "globals.h"

//Pages 355 - 359 - 361 in data sheet

/*
 * motor setup - Page 358
 */
void motor_Setup(void) {
    TRISCbits.TRISC1 = 1;
    TRISCbits.TRISC2 = 1;
        
    // Duty period
    T2PR = 249; // page 348
    T4PR = 249;
    
    PWM5CONbits.EN = 1; // page 359
    PWM6CONbits.EN = 1; 
    
    setDutyCycleR;
    setDutyCycleL;
    
    PIR4bits.TMR2IF = 0; // page 141
    PIR7bits.TMR4IF = 0; // page 144
        
    T2CLKbits.T2CS = 0b001; // page 336
    T4CLKbits.T4CS = 0b001;
     
    T2CONbits.ON = 1; // page 339
    T4CONbits.ON = 1;
    
    CCPTMRS1bits.P5TSEL = 0b10; // page 360
    CCPTMRS1bits.P6TSEL = 0b01;
    
    RC1PPS = 0x0D; // page 278
    RC2PPS = 0x0E;
    
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    
    // Enable drive pins
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;    
}

void setDutyCycleR(uint16_t dutyCycle) {
    PWM5DCH = dutyCycle >> 2;
    PWM5DCL = (dutyCycle & 0b11) << 6;
}

void setDutyCycleL(uint16_t dutyCycle) {
    PWM6DCH = dutyCycle >> 2;
    PWM6DCL = (dutyCycle & 0b11) << 6;
}

/*
 * motor basic movement function
 */
void move_dist(uint16_t angle, uint8_t distance, bool slow);

/*
 * motor movement to interrupt
 */
void move(uint16_t angle);

/*
 * motor spin in place
 */
void motor_spin(uint16_t angle);

/*
 * motor stop
 */
void motor_stop(void) {
    leftForwards = 0;
    leftBackwards = 0;
    rightForwards = 0;
    rightBackwards = 0;
}

/*
 * motor setup - Page 349
 */
void motor_reverse(uint16_t angle);