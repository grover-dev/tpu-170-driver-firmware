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
enum ADC_ERRORS adc_set_low_power_mode(int mode)
{
    if (calibration_in_progress){
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
enum ADC_ERRORS adc_set_sample_rate(uint32_t clock)
{
    if (calibration_in_progress) {
        calibration_in_progress = (LPC_ADC->CTRL & 1 << 30) >> 30;
        return CALIBRATION_IN_PROGRESS;
    }
    // check if the requested sample rate is above limits (either hardware or power defined) 
    if (clock > ADC_MAX_RATE || (clock > 1000000 && SUPPLY_VOLTAGE < 27)){
        return SAMPLE_RATE_TOO_HIGH;
    } 
    LPC_ADC->CTRL |= ((MICROCONTROLLER_CLOCK / (25 *clock)) - 1) | (1 << 30); 
    return ADC_SUCCESS;
}



// enables or disables adc channels based on value of state 
enum ADC_ERRORS adc_enable_disable(uint32_t adc_channel, bool state)
{
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

// sets given sequence channels to given channel bit map 
// sequence = 0 for SEQA, sequence = 1 for SEQB
void adc_set_sequence_channels(uint32_t sequence, uint32_t channel_bit_map)
{
    if (sequence == 0){
        LPC_ADC->SEQA_CTRL = (LPC_ADC->SEQA_CTRL & 0xfffff000) | channel_bit_map;
    } else {
        LPC_ADC->SEQB_CTRL = (LPC_ADC->SEQA_CTRL & 0xfffff000) | channel_bit_map;
    }
}

// adds given channel bit map to given sequence  
// sequence = 0 for SEQA, sequence = 1 for SEQB
void adc_add_sequence_channels(uint32_t sequence, uint32_t channel_bit_map)
{
    if (sequence == 0){
        LPC_ADC->SEQA_CTRL |= channel_bit_map;
    } else {
        LPC_ADC->SEQB_CTRL |= channel_bit_map;
    }
}

// configure the given adc sequence 
// sequence = 0 for SEQA, sequence = 1 for SEQB
void adc_configure_sequence(uint32_t sequence, uint32_t trigger, bool trigpol, bool syncbypass,
                            bool singlestep, uint32_t priority, uint32_t mode, bool seq_enable)
{
    if (sequence == 0){
        LPC_ADC->SEQA_CTRL = (sequence & 0xfff) | (trigger & 0x07) << 12 | (trigpol & 0x01) << 18 |
                             (syncbypass & 0x01) << 19 | (singlestep & 0x01) << 28 | 
                             (priority & 0x01) << 29 | (mode & 0x01) << 30 | (seq_enable & 0x01) << 31; 
    } else {
        LPC_ADC->SEQB_CTRL = (sequence & 0xfff) | (trigger & 0x07) << 12 | (trigpol & 0x01) << 18 |
                             (syncbypass & 0x01) << 19 | (singlestep & 0x01) << 28 | 
                             (priority & 0x01) << 29 | (mode & 0x01) << 30 | (seq_enable & 0x01) << 31; 
    }
}

// disable or enable the given adc sequence 
// sequence = 0 for SEQA, sequence = 1 for SEQB
void adc_enable_disable_sequence(uint32_t sequence, bool state){
    volatile unsigned long * seq_addr;
    if (sequence == 0){
        seq_addr = &(LPC_ADC->SEQA_CTRL);
    } else{
        seq_addr = &(LPC_ADC->SEQB_CTRL);
    }
    if (state){
        *seq_addr |= (state & 0x01) << 31; 
    } else {
        *seq_addr &= ~((state & 0x01) << 31); 
    }
    
}

// trigger an adc sample for the given adc channel
 // sequence = 0 for SEQA, sequence = 1 for SEQB
 // type = 0 for single sample, type = 1 for burst (continuous) 
void adc_trigger_sample(uint32_t sequence, bool type){
    volatile unsigned long * seq_addr;
    if (sequence == 0){
        seq_addr = &(LPC_ADC->SEQA_CTRL);
    } else{
        seq_addr = &(LPC_ADC->SEQB_CTRL);
    }
    if (!type){
        // if single sample requested, disable burst first (if burst is enabled)
        if((*seq_addr & 0x01) << 27){
            *seq_addr &= ~(1 << 27);
            *seq_addr |= 1 << 26;
        } else {
            *seq_addr |= 1 << 26;
        }
    } else {
        *seq_addr |= 1 << 27;
    }
}


// // set adc interrupt function to a given value
// // jpl coding standard says this implementation is bad practice so maybe redo it?
// enum ADC_ERRORS adc_set_interrupt_function(uint32_t seq_channel, void (*function)(void)){
//     if(seq_channel == 0){

//     }
// }



