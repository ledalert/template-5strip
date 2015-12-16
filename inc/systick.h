#ifndef SYSTICK_H
#include <libopencm3/cm3/systick.h>


void systick_sleep_ms(int time);
void init_systick();

#define SYSTICK_H
#endif
