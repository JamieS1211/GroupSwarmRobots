/*
 * File:   interrupts.h
 * Author: jamieshepherd
 *
 * Created on January 18, 2020, 6:09 PM
 */


#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// Pages 115 - 135 - 169 in data sheet

/*
 * Function sets up all interrupt settings.
 */
void interrupts_Setup(void);



/*
 * Function should be called on an interrupt.
 * Contains code for each type of interrupt and clears interrupt after handling.
 */
void __interrupt() interrupts_Event(void);

#endif //INTERRUPTS_H