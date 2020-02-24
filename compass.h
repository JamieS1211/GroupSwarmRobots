/*
 * File:   compass.h
 * Author: willrice
 *
 * Created on February 7, 2020, 16:05
 * 
 * Modified based on:
 * https://github.com/dthain/QMC5883L
 * Declination angle is removed. Compass points to magnetic North
 * Not true North
 */

#ifndef COMPASS_H
#define COMPASS_H

// Functions
void comp_reset();          // reset()
void comp_reconfig_standby();       // reconfig()
void comp_reconfig_cont();

float comp_head();            //readHeading()
int comp_readRaw( int16_t *x, int16_t *y, int16_t *z, int16_t *t ); //readRar()

#endif  //COMPASS_H