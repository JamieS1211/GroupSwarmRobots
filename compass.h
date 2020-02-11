/*
 * File:   compass.h
 * Author: willrice
 *
 * Created on February 7, 2020, 16:05
 * 
 * Modified based on:
 * https://www.ccsinfo.com/forum/viewtopic.php?t=51156
 * Declination angle is removed. Compass points to magnetic North
 * Not true North
 */

#ifndef COMPASS_H
#define COMPASS_H


//Entire HMC5883L Compass Manual

// Defining addresses
#define HMC5883L_READ_ADDR       0x3D
#define HMC5883L_WRITE_ADDR      0x3C
                           
#define Config_Reg_A             0x00
#define Config_Reg_B             0x01
#define Mode_Reg                 0x02
#define X_MSB_Reg                0x03
#define X_LSB_Reg                0x04
#define Z_MSB_Reg                0x05
#define Z_LSB_Reg                0x06
#define Y_MSB_Reg                0x07
#define Y_LSB_Reg                0x08
#define Status_Reg               0x09
#define ID_Reg_A                 0x0A             
#define ID_Reg_B                 0x0B
#define ID_Reg_C                 0x0C
       
#define declination_angle     1.04   // For Exeter, UK, 2020  

                                   
//#use I2C(MASTER, SDA = pin_B7, SCL = pin_B6)   
                                             
// Defining used variables
signed long X_axis = 0;
signed long Y_axis = 0;                                 
signed long Z_axis = 0;
float m_scale = 1.0;
       
// Defining functions
unsigned long make_word(unsigned char HB, unsigned char LB);
void HMC5883L_init(); 
unsigned char HMC5883L_read(unsigned char reg);
void HMC5883L_write(unsigned char reg_address, unsigned char value);
void HMC5883L_read_data();
void HMC5883L_scale_axes();
void HMC5883L_set_scale(float gauss);
float HMC5883L_heading();

#endif //COMPASS_H