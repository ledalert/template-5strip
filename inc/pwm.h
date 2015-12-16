#ifndef PWM_H
#include "lut.h"
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>


#define PWM_PERIOD 4096
#define PWM_TOP (PWM_PERIOD - 1)

void pwm_init();
void pwm_rcc_init();
void pwm_timers_init();
void pwm_gpio_init();
void pwm_set_all_raw();
int pwm_output_filter(int value);
void pwm_set_output();

void pwm_set_all_raw(int value);
void pwm_set_all(int value);
void pwm_set_channel_raw(int channel, int value);
void pwm_set_channel(int channel, int value);




#define PWM_H
#endif