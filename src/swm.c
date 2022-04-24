#include "swm.h"


// initializes swm clock
void swm_init(void){
    // enable SWM clock
    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 7;
}

// if all swm configuration is done can call to disable swm clock 
void swm_clock_disable(void){
    LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<7);
}

