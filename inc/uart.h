#ifndef UART_H
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/dma.h>

void uart_send_data(volatile void* data, int length);
void uart_rcc_init();
void uart_gpio_init();
void uart_init();

#define UART_H
#endif