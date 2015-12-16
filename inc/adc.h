#ifndef ADC_H
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void adc_init();
void adc_rcc_init();
void adc_gpio_init();
void adc_sample(volatile uint16_t* sample, int channels, int use_interrupt);


#define ADC_H
#endif