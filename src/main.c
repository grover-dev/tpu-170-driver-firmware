#include "lpc822.h"
#include "gpio.h"
#include "adc.h"
#include "uart.h"
#include "timers.h"


void init(void){
    gpio_init();
    adc_init();
    uart_init();
    sct_timer_init();

    gpio_set_direction(16, OUTPUT);
    gpio_set_direction(27, OUTPUT);
    gpio_set_direction(12, OUTPUT);
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