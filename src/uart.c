#include "uart.h"

void uart_init(void){
    // enables flash register interface
    LPC_SYSCON->SYSAHBCLKCTRL |= 1 <<3;
    // reseting all uart peripherals
    LPC_SYSCON->PRESETCTRL &= ~(7<<3);

    // initialize uart clock divider with 1 to start the clock 
    LPC_SYSCON->UARTCLKDIV = 1;
    // div should always be set to 0xff
    LPC_SYSCON->UARTFRGDIV = 0xff;
    LPC_SYSCON->UARTFRGMULT = 0;
}

// assigns uart peripheral on given channel to given pins
// if any function is not needed (ex: rts, cts, sclk) pass UART_UNUSED_PIN
void uart_add_periheral(uint32_t channel, uint32_t tx_pin, uint32_t rx_pin, uint32_t rts_pin, uint32_t cts_pin, uint32_t sclk_pin){
   if (channel == 0){
        LPC_SWM->PINASSIGN0 = tx_pin | rx_pin << 8 | rts_pin << 16 | cts_pin << 24;
        LPC_SWM->PINASSIGN1 = (LPC_SWM->PINASSIGN1 & 0xffffff00) | sclk_pin;  
   } else if (channel == 1){
        LPC_SWM->PINASSIGN1 = (LPC_SWM->PINASSIGN1 & 0xff) | tx_pin << 8 | rx_pin << 16 | rts_pin << 24;
        LPC_SWM->PINASSIGN2 = (LPC_SWM->PINASSIGN2 & 0xffff0000) | cts_pin | sclk_pin << 8;
   } else if (channel == 2){
       LPC_SWM->PINASSIGN2 = (LPC_SWM->PINASSIGN2 & 0xffff) | tx_pin << 16 | rx_pin << 24;
       LPC_SWM->PINASSIGN3 = (LPC_SWM->PINASSIGN3 & 0xff000000) | rts_pin | cts_pin << 8 | sclk_pin << 16;
   }
}



void uart_set_baud(uint32_t channel, uint32_t baud_rate){
    uint32_t clock = (MICROCONTROLLER_CLOCK / (16 * baud_rate)) & 0xffff;
    if (channel == 0){
        LPC_USART0->BRG = clock; 
    } else if (channel == 1){
        LPC_USART1->BRG = clock;
    } else if (channel == 2){
        LPC_USART2->BRG = clock;
    }
}

void uart_dma_setup(uint32_t channel){
    
}