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
 * motor movement to interrupt timer T6
 */
void motor_move(uint16_t angle);

/*
 * motor spin in place for a desired shift in angle
 */
void motor_spin(uint16_t angle);

/*
 * motor spin in place for a desired angle (?)
 */
void motor_bearing(uint16_t angle);

/*
 * motor stop
 */
void motor_stop(void);

/*
 * motor reverses (1s) then spins to desired angle
 */
void motor_reverse(uint16_t angle);

/*
 * saving distance moved in direction
 */
void motor_save(uint16_t angle, uint16_t distance);

/*
 * calculating time needed to spin to desired angle
 */
long double calcanglet(uint16_t angle);

/*
 * calculating time needed to reach desired distance
 */
long double calcdistt(uint16_t distance);

/*
 * TESTER - infinite clockwise spin
 */
void spin_testCW(void);

/*
 * TESTER - move forward for 20s
 */
void move_test(void);
#endif //MOTOR_H