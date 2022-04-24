#pragma once


// motor driver channel driver pins
#define A_FET_PIN 19
#define B_FET_PIN 20
#define C_FET_PIN 21
#define D_FET_PIN 22

// motor driver current sense pins
#define A_SENSE_FILT_PIN 18
#define B_SENSE_FILT_PIN 17
#define C_SENSE_FILT_PIN 23
#define D_SENSE_FILT_PIN 14

#define A_SENSE_FILT_ADC 8
#define B_SENSE_FILT_ADC 9
#define C_SENSE_FILT_ADC 3
#define D_SENSE_FILT_ADC 2


// motor driver current amplifier shutdown pins 
#define AB_OPAMP_SHUTDOWN_PIN 26
#define CD_OPAMP_SHUTDOWN_PIN 25

// rs232 communication pins
#define RS232_EN_N_PIN 13
#define RS232_INVALID_N_PIN 24
#define RS232_FORCEON_PIN 10
#define RS232_FORCEOFF_PIN 11
#define RS232_TX_PIN 27
#define RS232_RX_PIN 16

// rtd temperature sense pin
#define TEMP_SENSE_PIN 7
#define TEMP_SENSE_ADC 0 

// analog pressure sensing pin
#define PRESSURE_SENSE_PIN 6
#define PRESSURE_SENSE_ADC 1

// hall effect pulse pins
#define HALL_UX_PIN 15
#define HALL_WY_PIN 1

// crystal pins
#define XTAL_IN_PIN 8
#define XTAL_OUT_PIN 8

#define DISABLE_PIN 255