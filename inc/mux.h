#ifndef MUX_H
#include "adc.h"
#include <libopencm3/cm3/nvic.h>


void mux_init();
void mux_gpio_init();
void mux_rcc_init();
void mux_init_irq();
void mux_sample(volatile uint16_t* target);
void mux_wait_for_samples();

#define MUX_H
#endif