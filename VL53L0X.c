/* 
 * File:   VL53L0X.c
 * Author: Chloe 
 *
 * Created on 07 February 2020
 */
#include <xc.h>
#include "stdint.h"
#define _XTAL_FREQ 20000000

#include "globals.h"
#include "VL53L0X.h"
#include "mcc_generated_files/examples/i2c2_master_example.h"
#include "cereal.h"


#define SYSRANGE_START 0x00
#define SYSTEM_SEQUENCE_CONFIG 0x01
#define SYSTEM_RANGE_CONFIG 0x09
#define SYSTEM_INTERRUPT_CONFIG_GPIO 0x0A
#define SYSTEM_INTERRUPT_CLEAR 0x0B
#define SYSTEM_THRESH_LOW 0x0E
#define INTERRUPT_STATUS 0x13
#define RANGE_RESULT_HI 0x1E
#define RANGE_RESULT_LO 0x1F
#define CROSSTALK_COMPENSATION_PEAK_RATE_MCPS 0x20
#define RE_RANGE_CONFIG_MIN_SNR 0x27
#define ALGO_PHASECAL_LIM 0x30
#define GLOBAL_CONFIG_VCSEL_WIDTH 0x32
#define FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT 0x44
#define MSRC_CONFIG_TIMEOUT_MACROP 0x46
#define FINAL_RANGE_CONFIG_VALID_PHASE_LOW 0x47
#define FINAL_RANGE_CONFIG_VALID_PHASE_HIGH 0x48
#define DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD 0x4E
#define DYNAMIC_SPAD_REF_EN_START_OFFSET 0x4F
#define PRE_RANGE_CONFIG_VCSEL_PERIOD 0x50
#define PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI 0x51
#define PRE_RANGE_CONFIG_TIMEOUT_MACROP_LO 0x52
#define PRE_RANGE_CONFIG_VALID_PHASE_LOW 0x56
#define PRE_RANGE_CONFIG_VALID_PHASE_HIGH 0x57
#define MSRC_CONFIG_CONTROL 0x60
#define PRE_RANGE_CONFIG_SIGMA_THRESH_HI 0x61
#define PRE_RANGE_CONFIG_SIGMA_THRESH_LO 0x62
#define PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT 0x64
#define FINAL_RANGE_CONFIG_MIN_SNR 0x67
#define FINAL_RANGE_CONFIG_VCSEL_PERIOD 0x70
#define FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI 0x71
#define FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO 0x72
#define POWER_MANAGEMENT_GO1_POWER_FORCE 0x80
#define SYSTEM_HISTOGRAM_BIN 0x81
#define GPIO_HV_MUX_ACTIVE_HIGH 0x84
#define VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV 0x89
#define SYSTEM_RANGE_CONFIG_4 0x94
#define RESULT_PEAK_SIGNAL_RATE_REF_0 0xB0
#define RESULT_PEAK_SIGNAL_RATE_REF_1 0xB1
#define RESULT_PEAK_SIGNAL_RATE_REF_2 0xB2
#define RESULT_PEAK_SIGNAL_RATE_REF_3 0xB3
#define RESULT_PEAK_SIGNAL_RATE_REF_4 0xB4
#define RESULT_PEAK_SIGNAL_RATE_REF_5 0xB5
#define GLOBAL_CONFIG_REF_EN_START_SELECT 0xB6


/*
 * Send data to VL53L0X using I2C
 */
void VL53L0X_SendData(uint8_t slave_address, uint8_t device_register, uint8_t value) {
    uint8_t data[2] = {device_register, value};
    I2C2_WriteNBytes(slave_address, data, 2);
}


/*
 * Receive data from VL53L0X using I2C
 */
uint8_t VL53L0X_Read_Register(uint8_t slave_address, uint8_t register_value) {
    uint8_t value;    
    I2C2_ReadDataBlock(slave_address, register_value, &value, 1);
    return value;
}

/*
 * Change the I2C address of the VL53L0X 
 */
void VL53L0X_Change_Address(uint8_t oldAddress, uint8_t newAddress) {
    
    TRISCbits.TRISC7 =0;
    LATCbits.LATC7 = 0; // Ensure manually controlled VL53L0X is off
    __delay_ms(50);

    VL53L0X_SendData(oldAddress, 0x8A, newAddress);
        __delay_ms(50);
    LATCbits.LATC7 = 1; // Re-enable manually controlled VL53L0X
    __delay_ms(50);
}


/*
 * Setup VL53L0X to desired settings using I2C
 */
void VL53L0X_Setup(uint8_t slave_address) {
    //TODO Find documentation that gives details and configure as desired (Possibly Peter knows?)
    VL53L0X_Initialisation(slave_address);
    
    //SET TO CONTINEOUS AND HIGH ACCURACY
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, 0x00);
	VL53L0X_SendData(slave_address, 0x45, 0x0C);   //UNKNOWN
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_VALID_PHASE_HIGH, 0x50);
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_VALID_PHASE_LOW , 0x08);
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_VCSEL_PERIOD, 0x08);
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_TIMEOUT_MACROP_LO, 0x75);   //UNKNOWN
	VL53L0X_SendData(slave_address, MSRC_CONFIG_TIMEOUT_MACROP, 0x1D);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI, 0x02);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO, 0x8B);
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x01);
	VL53L0X_SendData(slave_address, SYSTEM_INTERRUPT_CLEAR, 0x01);
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x00);
	VL53L0X_SendData(slave_address, SYSTEM_SEQUENCE_CONFIG, 0xE8);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_VALID_PHASE_HIGH, 0x48);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_VALID_PHASE_LOW, 0x08);
	VL53L0X_SendData(slave_address, GLOBAL_CONFIG_VCSEL_WIDTH, 0x03);
	VL53L0X_SendData(slave_address, 0x30, 0x07);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x30, 0x20);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_VCSEL_PERIOD, 0x06);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI, 0x01);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO, 0xD7);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI, 0x01);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO, 0xD7);
	VL53L0X_SendData(slave_address, SYSTEM_SEQUENCE_CONFIG, 0x02);
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x01);
	VL53L0X_SendData(slave_address, SYSTEM_INTERRUPT_CLEAR, 0x01);
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x00);
	VL53L0X_SendData(slave_address, SYSTEM_SEQUENCE_CONFIG, 0xE8);
}


/*
 * Setup VL53L0X with initial values
 */
void VL53L0X_Initialisation(uint8_t slave_address) { 
    
    VL53L0X_SendData(slave_address, VHV_CONFIG_PAD_SCL_SDA__EXTSUP_HV, 0x01);
    VL53L0X_SendData(slave_address, 0x88, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x00);
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x01);
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);
	VL53L0X_SendData(slave_address, MSRC_CONFIG_CONTROL, 0x12);
    VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, 0x00);
    VL53L0X_SendData(slave_address, 0x45, 0x20);   // UNKNOWN
	VL53L0X_SendData(slave_address, SYSTEM_SEQUENCE_CONFIG, 0xFF);
	VL53L0X_SendData(slave_address, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x00);
	VL53L0X_SendData(slave_address, 0xFF, 0x06);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x83, 0x05);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x07);   //UNKNOWN
	VL53L0X_SendData(slave_address, SYSTEM_HISTOGRAM_BIN, 0x01);
	VL53L0X_SendData(slave_address, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
	VL53L0X_SendData(slave_address, SYSTEM_RANGE_CONFIG_4, 0x6B);
	VL53L0X_SendData(slave_address, 0x83, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x83, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, SYSTEM_HISTOGRAM_BIN, 0x00);
	VL53L0X_SendData(slave_address, 0xFF, 0x06);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x83, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x01);
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, DYNAMIC_SPAD_REF_EN_START_OFFSET, 0x00);
	VL53L0X_SendData(slave_address, DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD, 0x2C);
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, GLOBAL_CONFIG_REF_EN_START_SELECT, 0xB4);
	VL53L0X_SendData(slave_address, RESULT_PEAK_SIGNAL_RATE_REF_0, 0x00);
	VL53L0X_SendData(slave_address, RESULT_PEAK_SIGNAL_RATE_REF_1, 0xF0);
	VL53L0X_SendData(slave_address, RESULT_PEAK_SIGNAL_RATE_REF_2, 0xFF);
	VL53L0X_SendData(slave_address, RESULT_PEAK_SIGNAL_RATE_REF_3, 0x1E);
	VL53L0X_SendData(slave_address, RESULT_PEAK_SIGNAL_RATE_REF_4, 0x00);
	VL53L0X_SendData(slave_address, RESULT_PEAK_SIGNAL_RATE_REF_5, 0x00);
    
    
    VL53L0X_Tuning(slave_address);
    
    
    VL53L0X_SendData(slave_address, SYSTEM_INTERRUPT_CONFIG_GPIO, 0x04);
	VL53L0X_SendData(slave_address, GPIO_HV_MUX_ACTIVE_HIGH, 0x01);
	VL53L0X_SendData(slave_address, SYSTEM_INTERRUPT_CLEAR, 0x01);
	VL53L0X_SendData(slave_address, SYSTEM_SEQUENCE_CONFIG, 0xE8);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI, 0x02);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO, 0x94);
	VL53L0X_SendData(slave_address, SYSTEM_SEQUENCE_CONFIG, 0x01);
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x41);
    
    while ((VL53L0X_Read_Register(slave_address, INTERRUPT_STATUS) & 0x07) == 0);
    
	VL53L0X_SendData(slave_address, SYSTEM_INTERRUPT_CLEAR, 0x01);
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x00);
	VL53L0X_SendData(slave_address, SYSTEM_SEQUENCE_CONFIG, 0x02);
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x01);
    
    while ((VL53L0X_Read_Register(slave_address, INTERRUPT_STATUS) & 0x07) == 0);
    
	VL53L0X_SendData(slave_address, SYSTEM_INTERRUPT_CLEAR, 0x01);
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x00);
	VL53L0X_SendData(slave_address, SYSTEM_SEQUENCE_CONFIG, 0xE8); 
    
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI, 0x05);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO, 0x9A);
}


/*
 * Setup VL53L0X to recommended tuning values
 */
void VL53L0X_Tuning(uint8_t slave_address) {
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x00);
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, SYSTEM_RANGE_CONFIG, 0x00); 
	VL53L0X_SendData(slave_address, 0x10, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x11, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x24, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x25, 0xFF);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x75, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, DYNAMIC_SPAD_NUM_REQUESTED_REF_SPAD, 0x2C);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_VALID_PHASE_HIGH, 0x00);
	VL53L0X_SendData(slave_address, ALGO_PHASECAL_LIM, 0x20);
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, ALGO_PHASECAL_LIM, 0x09);
	VL53L0X_SendData(slave_address, 0x54, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x31, 0x04);   //UNKNOWN
	VL53L0X_SendData(slave_address, GLOBAL_CONFIG_VCSEL_WIDTH, 0x03); 
	VL53L0X_SendData(slave_address, 0x40, 0x83);   //UNKNOWN
	VL53L0X_SendData(slave_address, MSRC_CONFIG_TIMEOUT_MACROP, 0x25);
	VL53L0X_SendData(slave_address, MSRC_CONFIG_CONTROL, 0x00);
	VL53L0X_SendData(slave_address, RE_RANGE_CONFIG_MIN_SNR, 0x00);
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_VCSEL_PERIOD, 0x06);
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_TIMEOUT_MACROP_HI, 0x00);
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_TIMEOUT_MACROP_LO, 0x96);
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_VALID_PHASE_LOW, 0x08);
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_VALID_PHASE_HIGH, 0x30);
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_SIGMA_THRESH_HI, 0x00);
	VL53L0X_SendData(slave_address, PRE_RANGE_CONFIG_SIGMA_THRESH_LO , 0x00);
	VL53L0X_SendData(slave_address, PRE_RANGE_MIN_COUNT_RATE_RTN_LIMIT, 0x00);
	VL53L0X_SendData(slave_address, 0x65, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x66, 0xA0);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x22, 0x32);   //UNKNOWN
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_VALID_PHASE_LOW, 0x14);
	VL53L0X_SendData(slave_address, 0x49, 0xFF);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x4A, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x7A, 0x0A);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x7B, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x78, 0x21);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x23, 0x34);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x42, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, 0xFF);
	VL53L0X_SendData(slave_address, 0x45, 0x26);   //UNKNOWN
	VL53L0X_SendData(slave_address, MSRC_CONFIG_TIMEOUT_MACROP, 0x05);
	VL53L0X_SendData(slave_address, 0x40, 0x40);   //UNKNOWN
	VL53L0X_SendData(slave_address, SYSTEM_THRESH_LOW, 0x06);
	VL53L0X_SendData(slave_address, CROSSTALK_COMPENSATION_PEAK_RATE_MCPS, 0x1A);
	VL53L0X_SendData(slave_address, 0x43, 0x40);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x34, 0x03);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x35, 0x44);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x31, 0x04);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x4B, 0x09);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x4C, 0x05);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x4D, 0x04);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_MIN_COUNT_RATE_RTN_LIMIT, 0x00);
	VL53L0X_SendData(slave_address, 0x45, 0x20);   //UNKNOWN
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_VALID_PHASE_LOW, 0x08);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_VALID_PHASE_HIGH, 0x28);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_MIN_SNR, 0x00);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_VCSEL_PERIOD, 0x04);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_HI, 0x01);
	VL53L0X_SendData(slave_address, FINAL_RANGE_CONFIG_TIMEOUT_MACROP_LO, 0xFE);
	VL53L0X_SendData(slave_address, 0x76, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x77, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x0D, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
	VL53L0X_SendData(slave_address, SYSTEM_SEQUENCE_CONFIG, 0xF8);
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, 0x8E, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x01);
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);
}


/*
 * Read range from VL53L0X 
 */
uint16_t VL53L0X_ReadRange(uint8_t slave_address) {
	VL53L0X_SendData(slave_address, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x01);
	VL53L0X_SendData(slave_address, 0xFF, 0x01);   //UNKNOWN
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x00);
	VL53L0X_SendData(slave_address, 0x91, 0x3C);   //UNKNOWN
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x01);
	VL53L0X_SendData(slave_address, 0xFF, 0x00);   //UNKNOWN
	VL53L0X_SendData(slave_address, POWER_MANAGEMENT_GO1_POWER_FORCE, 0x00);
	VL53L0X_SendData(slave_address, SYSRANGE_START, 0x01);
    
    while ((VL53L0X_Read_Register(slave_address, INTERRUPT_STATUS) & 0x07) == 0x00);
    __delay_ms(2);
    
    uint8_t valueHI = VL53L0X_Read_Register(slave_address, RANGE_RESULT_HI);
    uint8_t valueLO = VL53L0X_Read_Register(slave_address, RANGE_RESULT_LO);
    
	VL53L0X_SendData(slave_address, SYSTEM_INTERRUPT_CLEAR, 0x01);
    
    return (valueHI << 8) + valueLO;
}
