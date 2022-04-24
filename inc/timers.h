#pragma once

#include "lpc822.h"

struct event{

};

// enum SCT_CONFIG{};

void sct_timer_init(void);
void sct_input_pin_assign(uint32_t pin, uint32_t channel);
void sct_output_pin_assign(uint32_t pin, uint32_t channel);

