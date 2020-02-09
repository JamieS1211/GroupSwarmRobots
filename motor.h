/*
 * File:   motor.h
 * Author: bendickinson
 *
 * Created on February 07, 2020, 15:40 PM
 */

#ifndef MOTOR_H
#define MOTOR_H


//Pages 342 - 351 - 355 in data sheet

/*
 * motor setup - Page 348
 * corresponding TRIS bit cleared
 */
void motor_Setup(void);

/*
 * motor basic movement function - Page 349
 */
void move_dist(angle, distance);

/*
 * motor movement to interrupt - Page 349
 */
void move(angle);

/*
 * motor spin in place - Page 349
 */
void motor_spin(angle);

/*
 * motor setup - Page 349
 */
void motor_Setup(void);

/*
 * motor stop - Page 349
 */
void motor_stop(void);

/*
 * motor setup - Page 349
 */
void motor_Setup(void);

/*
 * motor setup - Page 349
 */
void motor_slow(angle, distance);

/*
 * motor setup - Page 349
 */
void motor_reverse(angle);


#endif //MOTOR_H