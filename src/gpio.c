#include "gpio.h"
#include "timers.h"
// initializes gpio 
void gpio_init(void){    
    // enable gpio clock
    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 6;
}

// // after switch matrix is set, can disable the clock to prevent changes 
// void gpio_disable_swm_clock(void){
//     LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<6);
// }


// // configure given pin to be a gpio pin, 
// void gpio_swm_configure_pin(uint32_t pin, bool state){

// }

// read the given pin's state
uint32_t gpio_read_pin(uint32_t pin){
    return (LPC_GPIO_PORT->PIN0 & (1<< pin)) >> pin;
}


// set direction (input or output) of given pin
void gpio_set_direction(uint32_t pin, enum GPIO_STATE dir){
    if (dir == OUTPUT){
        LPC_GPIO_PORT->DIRSET0 |= 1 << pin;
    } else {
        LPC_GPIO_PORT->DIRCLR0 |= 1 << pin;
    }
}

// toggle the direction (input or output) of the given pin
void gpio_toggle_pin_dir(uint32_t pin){
    LPC_GPIO_PORT->DIRNOT0 |= 1 << pin;
}


// set output state of the given pin  
void gpio_set_pin(uint32_t pin, enum GPIO_STATE state){
    if (state == HIGH) {
        LPC_GPIO_PORT->SET0 |= 1 << pin;
    } else {
        LPC_GPIO_PORT->CLR0 |= 1 << pin;
    }
}

// toggle the state of the given pin
void gpio_toggle_pin(uint32_t pin){
    LPC_GPIO_PORT->NOT0 |= 1<<pin;
}

