#include "timers.h"

void SCT_IRQHandler(void){

}

// initialize sct_timer
void sct_timer_init(void){
    // enable sct timer clock
    LPC_SYSCON->SYSAHBCLKCTRL |= 1<<8;
    // reset sct timer peripheral
    LPC_SYSCON->PRESETCTRL |= 1<<8;
}

static struct sct_setup {
    bool unify;
    uint32_t clock_mode;
} sct_state;

void sct_configure(bool unify, uint32_t clock_mode, uint32_t clock_select, bool no_reload_l, 
                    bool no_reload_h, uint32_t insync, bool autolimit_l, bool autolimit_h){
    sct_state.unify = unify;
    sct_state.clock_mode = clock_mode;
    
    LPC_SCT->CONFIG = ((unify) ? 1:0) | (0x03 & clock_mode) << 1 | (0x07 & clock_select) << 3 |
                        ((no_reload_l) ? 1:0) << 7 | ((no_reload_h) ? 1:0) << 8 | (0x07 & insync) << 9 |
                        ((autolimit_l) ? 1:0) << 17 | ((autolimit_h) ? 1:0) << 18; 
    
}


// assign a timer channel input to the given pin
void sct_input_pin_assign(uint32_t pin, uint32_t channel){
    if (channel == 0){
        LPC_SWM->PINASSIGN6 = (LPC_SWM->PINASSIGN6 & 0x00ffffff) | pin<<24;
    } else if (channel == 1){
        LPC_SWM->PINASSIGN7 = (LPC_SWM->PINASSIGN7 & 0xffffff00) | pin;
    } else if (channel == 2){
        LPC_SWM->PINASSIGN8 = (LPC_SWM->PINASSIGN7 & 0xffff00ff) | pin<<8;
    } else if (channel == 3){
        LPC_SWM->PINASSIGN8 = (LPC_SWM->PINASSIGN7 & 0xff00ffff) | pin<<16;
    } 
}
// assign a timer channel output to the given pin
void sct_output_pin_assign(uint32_t pin, uint32_t channel){
    if (channel == 0){
        LPC_SWM->PINASSIGN7 = (LPC_SWM->PINASSIGN7 & 0x00ffffff) | pin<<24;
    } else if (channel == 1){
        LPC_SWM->PINASSIGN8 = (LPC_SWM->PINASSIGN8 & 0xffffff00) | pin;
    } else if (channel == 2){
        LPC_SWM->PINASSIGN8 = (LPC_SWM->PINASSIGN8 & 0xffff00ff) | pin<<8;
    } else if (channel == 3){
        LPC_SWM->PINASSIGN8 = (LPC_SWM->PINASSIGN8 & 0xff00ffff) | pin<<16;
    } else if (channel == 4){
        LPC_SWM->PINASSIGN8 = (LPC_SWM->PINASSIGN8 & 0x00ffffff) | pin<<24;
    } else if (channel == 5){
        LPC_SWM->PINASSIGN9 = (LPC_SWM->PINASSIGN9 & 0xffffff00) | pin;
    }
}

