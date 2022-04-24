#pragma once

#include "LPC8xx.h"
#include "lpc_types.h"

// clock cycles for 1 microsecond 
#define us 25 

// define microcontroller clock frequency in Hz
#define MHz 1000000
#define MICROCONTROLLER_CLOCK (25*MHz)

// define supply voltage (in units of 0.1 V (33->3.3V))
#define SUPPLY_VOLTAGE 33