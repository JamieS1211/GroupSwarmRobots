/*
 * File:   compass.c
 * Author: willrice
 *
 * Created on February 7, 2020, 21:50
 */


#include <xc.h> // Think is library type thing

#include "globals.h"
#include "compass.h"

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