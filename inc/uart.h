#pragma once

#include "lpc822.h"

#define UART_UNUSED_PIN 0xff

void uart_init(void);
void uart_add_periheral(uint32_t channel, uint32_t tx_pin, uint32_t rx_pin, uint32_t rts_pin, uint32_t cts_pin, uint32_t sclk_pin);