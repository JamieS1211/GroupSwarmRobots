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
#include <stdio.h>
#include "mcc_generated_files/uart2.h"
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
    // Loops through an undefined length string input till it reaches:
    // 36 = $ which signals end of tranmission
    // 0 = Null which signals nothing stores
    int i = 0;
    while (string[i]!=36 && string[i]!=0){
        uint8_t txData = string[i];
        // Send function
        UART2_Write(txData);
        i += 1;
    }
    UART2_Write(13);    // Arduino Carriage return
    UART2_Write(10);
}

void cereal_int(int input) {
    // Serial the type
    char typey[] = "int$";
    cereal_str(typey);
    
    // Formatting number
    char string[20] = {0};
    sprintf(string, "%i", input);
    
    // Serial Number
    cereal_str(string);
}

void cereal_float(float input) {
    // Serial the type
    char typey[] = "float$";
    cereal_str(typey);
    
    // Formatting number
    char string[20] = {0};
    sprintf(string, "%f", input);
    
    // Serial Number
    cereal_str(string);
}

void cereal_uint8_t(uint8_t input) {
    // Serial the type
    char typey[] = "uint8_t$";
    cereal_str(typey);
    
    // Formatting number
    char string[20] = {0};
    sprintf(string, "%u", input);
    
    // Serial Number
    cereal_str(string);
}

void cereal_int16_t(int16_t input) {
    // Serial the type
    char typey[] = "int16_t$";
    cereal_str(typey);
    
    // Formatting number
    char string[20] = {0};
    sprintf(string, "%i", input);
    
    // Serial Number
    cereal_str(string);
}

void cereal_size_t(size_t input) {
    // Serial the type
    char typey[] = "size_t$";
    cereal_str(typey);
    
    // Formatting number
    char string[20] = {0};
    sprintf(string, "%u", input);
    
    // Serial number
    cereal_str(string);
}

void cereal_hex(uint8_t input) {
    // Serial the type
    char typey[] = "hex$";
    cereal_str(typey);
    
    // Formatting number
    char string[20] = {0};
    sprintf(string, "%x", input);
    
    // Serial Number
    cereal_str(string);
}