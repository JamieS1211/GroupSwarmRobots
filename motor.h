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

void setDutyCycle(int dutyCycle);

/*
 * motor basic movement function w/ option to reduce speed
 */
void move_dist(float angle, int distance, bool slow);

/*
 * motor movement to interrupt timer T6
 */
void motor_move(float angle);

/*
 * motor spin in place for a desired shift in angle
 */
void motor_spin(float angle);

/*
 * motor spin in place for a desired angle (?)
 */
void motor_bearing(float angle);

/*
 * motor stop
 */
void motor_stop(void);

/*
 * motor reverses (5cm) then spins to desired angle
 */
void motor_reverse(float angle);

/*
 * Escape from P2P charging
 */
void motor_escape(void);

/*
 * saving distance moved in vector direction as polar coordinates
 */
void motor_save(float angle, int distance);

/*
 * calculating time t
 */
int calcanglet(float angle);

/*
 * calculating time needed to reach desired distance
 */
int calcdistt(int distance);

/*
 * TESTER - infinite clockwise spin
 */
void spin_test(void);

/*
 * TESTER - move forward 20s
 */
void move_test(void);

#endif //MOTOR_H