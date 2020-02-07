/*
 * File:   compass.h
 * Author: willrice
 *
 * Created on February 7, 2020, 16:05
 */

#ifndef COMPASS_H
#define COMPASS_H


//Entire HMC5883L Compass Manual

/*
 * Compass Setup - Page 12 - 14
 * Individual data sheet
 * Setting up single measure mode
 */
void comp_Setup(void);



/*
 * Compass Testing+Calibration - Page 19
 * Removing natural offset by applying 1.1 Gauss field
 * Sets gain to correct value
 */
void comp_Test(void, void, void);



/*
 * Compass Testing+Calibration - Page 15, 18
 * Register Document
 * Returns Compass heading
 */
void comp_Head(void, void, void);

/*
 * Compass Testing+Calibration - Page 15, 18
 * Register Document
 * Returns Compass heading in Gauss
 */
void comp_Raw(void, void, void);

#endif //COMPASS_H