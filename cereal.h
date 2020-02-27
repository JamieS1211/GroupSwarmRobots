/*
 * File:   cereal.h
 * Author: willrice
 *
 * Created on February 26, 2020, 19:50
 * 
 * ASCII Chart for reference:
 * https://www.arduino.cc/en/Reference/ASCIIchart
 */

#ifndef CEREAL_H
#define CEREAL_H

/* Unable to pass multiple variable types into functions so if there isn't a
 * suitable function, see below on how to send the data.
 * 
 * Variable
 * --------
 * char string[20] = {0};               Create string array and make null.
 * sprintf(string, "%f", variable);     Change %f depending on type:
 *      %c  -   char
 *      %i  -   int (signed)
 *      %f  -   float
 *      ...
 *      %u  -   uint8_t
 *      %u  -   size_t unsigned
 *      %x  -   size_t hex
 *      ...
 *      %hi -   signed short int
 *      %hu -   unsigned short int
 *      %u  -   unsigned in
 *      %li -   signed long int
 *      %lu -   unsigned long int
 * 
 * Text
 * ----
 * char string_name[string_length] = "string";
 */

/* Example
 * -------
 * int x = 58;
 * 
 * // First Serial print an ID. Try to keep short to save mem
 * // Check is a valid ASCII character 
 * // https://www.arduino.cc/en/Reference/ASCIIchart
 * // You must send an $ to end the character list
 * // If you don't it will print all memory till it finds 0
 * 
 * char string[3] = "x=$";
 * cereal_str(string);
 * 
 * // Next send the variable x which is an int
 * 
 * cereal_int(x);
 * 
 * // On the arduino Serial Port this will return
 *      x=
 *      int
 *      58
 */

// The main function for sending (called by all others)
void cereal_str(char string[]);

// Specific Functions
void cereal_int(int input);
void cereal_float(float input);
void cereal_uint8_t(uint8_t input);
void cereal_int16_t(int16_t input);
void cereal_size_t(size_t input);

#endif  //CEREAL_H