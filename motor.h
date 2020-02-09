/*
 * File:   motor.h
 * Author: bendickinson
 *
 * Created on February 07, 2020, 15:40 PM
 */

#ifndef MOTOR_H
#define MOTOR_H

//Pages 355 - 359 - 361 in data sheet

/*
 * motor setup - Page 358
 */
void motor_Setup(void);

void setDutyCycleR(uint16_t dutyCycle);

void setDutyCycleL(uint16_t dutyCycle);

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
void motor_stop(void);

/*
 * motor setup - Page 349
 */
void motor_reverse(uint16_t angle);
#endif //MOTOR_H