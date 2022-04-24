#include "lpc822.h"
#include "gpio.h"
#include "adc.h"
#include "uart.h"
#include "timers.h"
#include "pins.h"


void init(void){
    gpio_init();
    adc_init();
    uart_init();
    sct_timer_init();

    gpio_set_direction(A_FET_PIN, OUTPUT);
    gpio_set_direction(B_FET_PIN, OUTPUT);
    gpio_set_direction(C_FET_PIN, OUTPUT);
    gpio_set_direction(D_FET_PIN, OUTPUT);


    // configure AB, CD current sense amplifier shutdown pins  
    // and then set them high to enable the devices
    gpio_set_direction(AB_OPAMP_SHUTDOWN_PIN, OUTPUT);
    gpio_set_direction(CD_OPAMP_SHUTDOWN_PIN, OUTPUT);
    gpio_set_pin(AB_OPAMP_SHUTDOWN_PIN, OUTPUT);    
    gpio_set_pin(CD_OPAMP_SHUTDOWN_PIN, OUTPUT);    

    
    gpio_set_direction(HALL_UX_PIN, INPUT);
    gpio_set_direction(HALL_WY_PIN, INPUT);

    //todo: test if this works 
    uart_add_periheral(0, RS232_TX_PIN, RS232_RX_PIN, DISABLE_PIN,DISABLE_PIN, DISABLE_PIN);

    adc_enable_disable(A_SENSE_FILT_ADC, true);
    adc_enable_disable(B_SENSE_FILT_ADC, true);
    adc_enable_disable(C_SENSE_FILT_ADC, true);
    adc_enable_disable(D_SENSE_FILT_ADC, true);
    
    adc_enable_disable(TEMP_SENSE_ADC, true);
    adc_enable_disable(PRESSURE_SENSE_ADC, true);

    adc_set_sample_rate(1000000);

}


int main(void){
    init();


    int x = 0;
    while(1){
        gpio_toggle_pin(16);
        gpio_toggle_pin(27);
        gpio_toggle_pin(12);
        for(int i = 0; i < 100000; i++){
            x++;
        }
        x = 0;
    };

}