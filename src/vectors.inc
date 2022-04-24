extern void (* const g_pfnVectors[])(void);
__attribute__((section(".isr_vector")))
void (* const g_pfnVectors[])(void)  = {
    &_vStackTop,                          // Stack pointer (stack grows "down", therefore start at end of RAM)
    reset_handler,                          // reset handler
    NMI_Handler,                            // The NMI handler
    HardFault_Handler,                      // The hard fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    SVC_Handler,                            // SVCall handler
    0,                                      // Reserved
    0,                                      // Reserved
    PendSV_Handler,                         // The PendSV handler
    SysTick_Handler,                        // The SysTick handler

    // Chip Level - LPC82x
    SPI0_IRQHandler,                         // SPI0 controller
    SPI1_IRQHandler,                         // SPI1 controller
    0,                                       // Reserved
    UART0_IRQHandler,                        // UART0
    UART1_IRQHandler,                        // UART1
    UART2_IRQHandler,                        // UART2
    0,                                       // Reserved
    I2C1_IRQHandler,                         // I2C1 controller
    I2C0_IRQHandler,                         // I2C0 controller
    SCT_IRQHandler,                          // Smart Counter Timer
    MRT_IRQHandler,                          // Multi-Rate Timer
    CMP_IRQHandler,                          // Comparator
    WDT_IRQHandler,                          // Watchdog
    BOD_IRQHandler,                          // Brown Out Detect
    FLASH_IRQHandler,                        // Flash Interrupt
    WKT_IRQHandler,                          // Wakeup timer
    ADC_SEQA_IRQHandler,                     // ADC sequence A completion
    ADC_SEQB_IRQHandler,                     // ADC sequence B completion
    ADC_THCMP_IRQHandler,                    // ADC threshold compare
    ADC_OVR_IRQHandler,                      // ADC overrun
    DMA_IRQHandler,                          // DMA
    I2C2_IRQHandler,                         // I2C2 controller
    I2C3_IRQHandler,                         // I2C3 controller
    0,                                       // Reserved
    PIN_INT0_IRQHandler,                     // PIO INT0
    PIN_INT1_IRQHandler,                     // PIO INT1
    PIN_INT2_IRQHandler,                     // PIO INT2
    PIN_INT3_IRQHandler,                     // PIO INT3
    PIN_INT4_IRQHandler,                     // PIO INT4
    PIN_INT5_IRQHandler,                     // PIO INT5
    PIN_INT6_IRQHandler,                     // PIO INT6
    PIN_INT7_IRQHandler,                     // PIO INT7
};