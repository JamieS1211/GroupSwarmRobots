/*
 * File:   cereal.c
 * Author: willrice
 *
 * Created on February 26, 2020, 19:50
 * 
 * ASCII Chart for reference:
 * https://www.arduino.cc/en/Reference/ASCIIchart
 */

#include "globals.h"
#include "cereal.h"

// Variable
// --------
// char string[20]
// sprintf(string, "%f", number)

// Text
// ----
// char string_name[string_length] = "string";
void cereal_str(char string[])
{
    uint8_t string_size = sizeof(string)/sizeof(char);
    
    for (int i = 0; i<string_size; i++) {
        // Send function tb named
    }
}

void cereal_int(int input) {
    char string[20] = {0};
    sprintf(string, "%i", input);
    
    cereal_str(string);
}

void cereal_float(float input) {
    char string[20] = {0};
    sprintf(string, "%f", input);
    
    cereal_str(string);
}

void cereal_uint8_t(uint8_t input) {
    char string[20] = {0};
    sprintf(string, "%u", input);
    
    cereal_str(string);
}

void cereal_size_t(size_t input) {
    char string[20] = {0};
    sprintf(string, "%u", input);
    
    cereal_str(string);
}