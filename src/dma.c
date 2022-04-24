#include "dma.h"

void DMA_IRQHandler(void){
    
}



void dma_init(void){
    LPC_SYSCON->SYSAHBCLKCTRL |= 1<<29;
}