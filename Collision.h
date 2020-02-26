/* 
 * File:   Collision.h
 * Author: Chloe
 *
 * Created on 25 February 2020
 */

#ifndef COLLISION_H
#define COLLISION_H

#include "globals.h"

/* Change Address of one Lidar */
void Lidar_Change_Address();

/*Check if movement can be completed*/
void collide_check(uint16_t distance);

#endif //COLLISION