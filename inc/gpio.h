#pragma once

#include "lpc822.h"


enum GPIO_STATE{INPUT, OUTPUT, HIGH, LOW};

void gpio_init(void);    
uint32_t gpio_read_pin(uint32_t pin);
void gpio_set_direction(uint32_t pin, enum GPIO_STATE dir);
void gpio_toggle_pin_dir(uint32_t pin);
void gpio_set_pin(uint32_t pin, enum GPIO_STATE state);
void gpio_toggle_pin(uint32_t pin);