#include <libopencmsis/core_cm3.h>
#include <libopencm3/stm32/rcc.h>
#include "systick.h"
#include "lut.h"
#include "pwm.h"
#include "uart.h"
#include "mux.h"

struct strip_value {
	int r_acc;
	int g_acc;
	int b_acc;
} strips[5] = {0};


int main() {

	rcc_clock_setup_in_hsi_out_24mhz();
	rcc_periph_clock_enable(RCC_AFIO);
	gpio_primary_remap(AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_OFF, AFIO_MAPR_TIM2_REMAP_PARTIAL_REMAP2);

	pwm_init();
	init_systick();


	int fade = 0;

	const int FADE_MAX = 10000;	//Ten second fade in

 	while(1) {

		if (fade < FADE_MAX) {
			fade++;
		}
 		for (int i=0; i<5; i++) {

 			strips[i].r_acc = (strips[i].r_acc + 1000+i*30) % (4096*1000);
 			strips[i].g_acc = (strips[i].g_acc + 1600+i*20) % (4096*1000);
 			strips[i].b_acc = (strips[i].b_acc + 600+i*40) % (4096*1000);

			pwm_set_channel(i*3+0, fade*SINE_LUT[strips[i].r_acc/1000]/FADE_MAX);
			pwm_set_channel(i*3+1, fade*SINE_LUT[strips[i].g_acc/1000]/FADE_MAX);
			pwm_set_channel(i*3+2, fade*SINE_LUT[strips[i].b_acc/1000]/FADE_MAX);

 		}

 		systick_sleep_ms(1);
 	}


	return 0;
}

