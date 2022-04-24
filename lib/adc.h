#pragma once

#include "lpc822.h"

#define ADC_MAX_RATE 1200000
#define ADC_MAX_CHANNEL 11

enum ADC_ERRORS{ADC_SUCCESS, CALIBRATION_IN_PROGRESS, SAMPLE_RATE_TOO_HIGH, ADC_CHANNEL_DOES_NOT_EXIST};


void adc_init(void);
void adc_self_calibrate(void);
void adc_power_down(void);

enum ADC_ERRORS adc_set_low_power_mode(int mode);
enum ADC_ERRORS set_adc_sample_rate(uint32_t clock);
enum ADC_ERRORS adc_enable_disable(uint32_t adc_channel, bool state);
