/*
 * File:   motor.c
 * Author: bendickinson
 *
 * Created on February 07, 2020, 15:40 PM
 */

#include <xc.h>
#include "math.h"
#include "mcc_generated_files/examples/i2c2_master_example.h"
#include "compass.h"
#include "mcc_generated_files/mcc.h"
#include "position.h"

#include "globals.h"

//Pages 355 - 359 - 361 in data sheet

/*
 * Duty Cycle, i.e. motor speed set-up - Page 358
 * TO CHECK - PMW5 OR PMW6????? OR USE MCC
 */
void setDutyCycle(int dutyCycle) {
    PWM5DCH = dutyCycle >> 2;
    PWM5DCL = (dutyCycle & 0b11) << 6;
    PWM6DCH = dutyCycle >> 2;
    PWM6DCL = (dutyCycle & 0b11) << 6;
}

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
    
    setDutyCycle(512); // 50% duty cycle = 512/1024
    
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
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB4 = 0; 
}

/*
 * calculating time needed to reach desired distance
 * distance in cm, time in s
 */
int calcdistt(int distance){
    int movetime = 10; // TO TEST - time taken to move 200 cm
    int disttime = movetime/(200/distance);
    return disttime;
}

/*
 * calculating time needed to reach desired angle
 * angle in rad, time in s
 */
int calcanglet(float angle) {
    int fstime = 8; // TO TEST - time taken to complete full rotation
    double pi = M_PI; // pi
    int spintime = fstime / (2*pi/angle); // t/(2pi/angle)
    return spintime;
}

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
 * saving distance moved in vector direction as polar coordinates
 */
void motor_save(float angle, int distance){
    struct polarcoord temp = {0}; // Created new polar coord space in mem
    temp.angle = angle;
    temp.radius = distance;
        
    currMove = polar_add_struct(currMove, temp); // Update current movement
}

/*
 * motor spin in place for a desired shift in angle
 */
void motor_spin(float angle) {
    if (angle > 0) { // Anti-clockwise
        rightForwards = 1;
        leftBackwards = 1;
    }
    else { // Clockwise
        rightBackwards = 1;
        leftForwards = 1;
    }
    __delay_ms(100);
    int ctime = calcanglet(angle)*1000;
    __delay_ms(ctime);        
    motor_stop();
    motor_save(angle, 0);
}

/*
 * motor basic movement function w/ option to reduce speed
 */
void move_dist(float angle, int distance, bool slow){      
    if (slow == true) {
        setDutyCycle(128); // Eighth duty cycle (128/1024)
    }
    else {
        setDutyCycle(512);
    }
    motor_spin(angle);
    __delay_ms(250);
    
    rightForwards = 1;
    leftForwards = 1;
    int ctime = calcdistt(distance);
    for (int t = 0; t <= ctime; t++){
        __delay_ms(1000);        
    }
    motor_stop();
    motor_save(angle, distance);
}

/*
 * motor collision movement function w/ option to reduce speed
 */
//void move_coll(float angle, int distance, bool slow){
//    if (slow == true) {
//        setDutyCycle(128); // Quarter duty cycle (128/1024)
//    }
//    
////    int coll_check = collide_check(distance);
////    if (coll_check == 0){ // Check if obstacle
////        // insert oliver movement code here
////    }
//    else { // no obstacle
//        motor_spin(angle);
//        __delay_ms(1);
//        rightForwards = 1;
//        leftForwards = 1;
//        int ctime = calcdistt(distance);
//        for (int t = 0; t < ctime; t++){
//            __delay_ms(1000);        
//    }
//
//    motor_stop();
//    motor_save(angle, distance);    
//}



/*
 * motor movement to interrupt timer, i.e. step-move
 */
void motor_move(float angle) {
    motor_spin(angle);
    rightForwards = 1;
    leftForwards = 1;
    __delay_ms(250);
    motor_stop();
    motor_save(angle, 0);
 }

/*
 * motor spin in place for a desired angle in rad (?)
 */
void motor_bearing(float angle) {
    float curr_head = comp_head();
    float spin_amount = ang_diff(angle, curr_head);
    motor_spin(spin_amount);
    motor_save(angle, 0);
}

/*
 * motor reverses then spins to desired angle
 */
void motor_reverse(float angle, int distance) {
    rightBackwards = 1;
    leftBackwards = 1;
    
    int revtime = calcdistt(distance);
    for (int t = 0; t < revtime; t++){
        __delay_ms(1000);        
    }
    motor_stop();
    __delay_ms(250);
    motor_spin(angle);
    __delay_ms(1);
    motor_stop();
    motor_save(angle, distance);
}

/*
 * Escape from P2P charging
 */
void motor_escape(void){
    rightBackwards = 1;
    leftBackwards = 1;
//    
//    int esctime = calcdistt(5); // move 5cm back
//    for (int t = 0; t < esctime; t++){
//        __delay_ms(1000);        
//    }
//    motor_stop();
//    __delay_ms(500);
//    motor_spin(M_PI); // Spin 180°
//    __delay_ms(1);
//    motor_stop();
//    motor_save(M_PI, -5);
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
