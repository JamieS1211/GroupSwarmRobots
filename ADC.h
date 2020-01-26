/*
 * File:   ADC.h
 * Author: poult
 *
 * Created on January 20, 2020, 5:35 PM
 */

#ifndef ADC_H
#define ADC_H


/*
 * Function sets up all ADC (Analog to Digital converter) settings.
 */
void ADC_Setup(void);


/*
 * Sets up the item to be sampled by the ADC
 * Passed x to define item
 */
void ADC_DestinationSetup(int x);


/*
 * Contains code to sample ADC - measuring light levels 
 * Passed x to specify item to sample
 */
int ADC_Read(int x);

#endif //ADC_H