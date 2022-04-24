#include "adc.h"

// add blocker to prevent changes to CTRL register until calibration is done
static bool calibration_in_progress = 0;

// self calibrate adc
void adc_self_calibrate(void){
    uint32_t saved_ctrl = LPC_ADC->CTRL;
    // to calibrate, sets clock div to 500 KHz, enables calmode
    LPC_ADC->CTRL |= ((MICROCONTROLLER_CLOCK / 500000) - 1) | (1 << 30); 
    // calibration is not done until CALMODE is cleared
    calibration_in_progress = true;
}

// setup based on chapter 21 of the LPC82x manual
void adc_init(void){
    // enable the adc peripheral
    LPC_SYSCON->PDRUNCFG &= ~(1 << 4);

    // enable ADC clock
    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 24;

    //todo: handle the adc irqs
    adc_self_calibrate();
    
    // if in low voltasge mode, need to change the trim register
    if(SUPPLY_VOLTAGE < 27){
        LPC_ADC->TRM |= 1 << 5;
    }
}

// power adc down
void adc_power_down(void){
    LPC_SYSCON->PDRUNCFG ^= 1 << 4;
}

// set adc to low power mode (powered off when not in use) 
enum ADC_ERRORS adc_set_low_power_mode(int mode){
    if (calibration_in_progress) {
        calibration_in_progress = (LPC_ADC->CTRL & 1 << 30) >> 30;
        return CALIBRATION_IN_PROGRESS;
    }
    if (mode){
        LPC_ADC->CTRL |= 1 << 10;
    } else {
        LPC_ADC->CTRL &= ~(1<<10);
    }
    return ADC_SUCCESS;
}

// set the adc sample rate
enum ADC_ERRORS set_adc_sample_rate(uint32_t clock){
    if (calibration_in_progress) {
        calibration_in_progress = (LPC_ADC->CTRL & 1 << 30) >> 30;
        return CALIBRATION_IN_PROGRESS;
    }
    // check if the requested sample rate is above limits (either hardware or power defined) 
    if (clock > ADC_MAX_RATE || (clock > 1000000 && SUPPLY_VOLTAGE < 27)){
        return SAMPLE_RATE_TOO_HIGH;
    } 
    LPC_ADC->CTRL |= ((MICROCONTROLLER_CLOCK / clock) - 1) | (1 << 30); 
    return ADC_SUCCESS;
}



// enables or disables adc channels based on value of state 
enum ADC_ERRORS adc_enable_disable(uint32_t adc_channel, bool state){
    if (adc_channel <= ADC_MAX_CHANNEL){
        uint32_t channel_bit = 1 << (adc_channel+13);
        if(state){
            LPC_SWM->PINENABLE0 |= channel_bit;
        } else {
            LPC_SWM->PINENABLE0 &= ~channel_bit;
        } 
        return SUCCESS;
    }
    return ADC_CHANNEL_DOES_NOT_EXIST;
}

// // set adc interrupt function to a given value
// // jpl coding standard says this implementation is bad practice so maybe redo it?
// enum ADC_ERRORS adc_set_interrupt_function(uint32_t seq_channel, void (*function)(void)){
//     if(seq_channel == 0){

//     }
// }



