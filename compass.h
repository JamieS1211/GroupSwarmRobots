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
void comp_init();           // init()
void comp_reset();          // reset()
int  comp_ready();          // ready()
void comp_reconfig();       // reconfig()

float comp_head();            //readHeading()
int comp_readRaw( int16_t *x, int16_t *y, int16_t *z, int16_t *t ); //readRar()

void comp_resetCalibration();           //resetCalibration()

void comp_setSamplingRate( int rate );  //setSamplingRate()
void comp_setRange( int range );        //setRange
void comp_setOversampling( int ovl );   //setOversampling
  
// Variables
int16_t xhigh, xlow;
int16_t yhigh, ylow;
uint8_t addr;
uint8_t mode;
uint8_t rate;
uint8_t range;
uint8_t oversampling;

#endif  //COMPASS_H