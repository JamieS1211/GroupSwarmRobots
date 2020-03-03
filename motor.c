/*
 * File:   motor.c
 * Author: bendickinson
 *
 * Created on February 07, 2020, 15:40 PM
 */

#include <xc.h>
#include "math.h"
#include "mcc_generated_files/examples/i2c2_master_example.h"

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
    
    setDutyCycleR(512); // 50% duty cycle = 512/1024
    setDutyCycleL(512);
    
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
    
    // Timer 6 set-up for ~2s
    T6CLKbits.CS = 0b001; // Fosc/4 page 336
    T6CONbits.ON = 1; // page 339
    T6CONbits.CKPS = 0b111; // pre-scalar (1:128) page 239
    T6CONbits.OUTPS = 0b1111; // post-scalar (1:16) page  239
    PIE9bits.TMR6IE = 1; // page 155
    T6PR = 243; // arbitrary 243/245 page 338
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
 * motor basic movement function w/ option to reduce speed
 */
void move_dist(float angle, int distance, bool slow){      
    if (slow == true) {
            setDutyCycleR(128); // Quarter duty cycle (128/1024)
            setDutyCycleL(128);
    }
    motor_spin(angle);
    rightForwards = 1;
    leftForwards = 1;
    int ctime = calcdistt(distance);
    __delay_ms(ctime);
    motor_stop();
    motor_save(angle, distance);
}

/*
 * motor movement to interrupt timer T6
 */
void motor_move(float angle) {
    motor_spin(angle);
    rightForwards = 1;
    leftForwards = 1;
    __delay_ms(1);
    motor_stop();
    motor_save(angle, 0);
 }

/*
 * motor spin in place for a desired shift in angle
 */
void motor_spin(float angle) {

    
    if (angle > 0) { // Anti-clockwise
        rightForwards = 1;
        leftBackwards = 1;
        __delay_ms(1);
        motor_stop();
    }
    if (angle < 0) { // Clockwise
        rightBackwards = 1;
        leftForwards = 1;
        __delay_ms(1);
        motor_stop();
    }
    motor_save(angle, 0);
}

/*
 * motor spin in place for a desired angle (?)
 */
void motor_bearing(uint16_t angle) {
    
}

/*
 * motor stop
 */
void motor_stop(void) {
    leftForwards = 0;
    leftBackwards = 0;
    rightForwards = 0;
    rightBackwards = 0;
    motor_save(angle, distance);
}

/*
 * motor reverses (5cm) then spins to desired angle
 */
void motor_reverse(uint16_t angle) {
    int t6count = ; // T6 counter
    int distance = 5;
    while t6count <= calcdistt(distance){
        rightBackwards = 1;
        leftBackwards = 1;
    }
    motor_spin(angle);
    motor_save(angle, distance);
}

/*
 * Escape from P2P charging
 */
void motor_escape(void){
    
}

/*
 * saving distance moved in vector direction as polar coordinates
 */
void motor_save(float angle, int distance);

/*
 * calculating time t
 */
long double calcanglet(float angle) {
    int fstime = 10; // TO TEST - time taken to complete full rotation
    double pi = M_PI; // pi
    long double spintime = fstime / (2*pi/angle); // t/(2pi/angle)
    return spintime;
}

/*
 * calculating time needed to reach desired distance
 */
long double calcdistt(int distance){
    int movetime = 10; // TO TEST - time taken to move 10 cm
    long double disttime = movetime/(10/distance);
    return disttime;
}

/*
 * TESTER - infinite clockwise spin
 */
void spin_test(void){
    rightBackwards = 1;
    leftForwards = 1;
    rightForwards = 0;
    leftBackwards = 0;
}

/*
 * TESTER - move forward 20s
 */
void move_test(void){
    rightForwards = 1;
    leftForwards = 1;
    rightBackwards = 0;
    leftBackwards = 0;
}
