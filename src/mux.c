#include "mux.h"

#include "pwm.h"	//For debug purpose

static volatile int samples_complete;
static volatile uint16_t* target_buffer;
static volatile int target_buffer_pos;


void mux_rcc_init() {
	rcc_periph_clock_enable(RCC_GPIOA);
}

void mux_gpio_init() {
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO12 | GPIO13 | GPIO14);

}

void mux_init() {
	adc_init();
	mux_rcc_init();
	mux_gpio_init();
	mux_init_irq();
}

void mux_init_irq() {
	nvic_set_priority(NVIC_DMA1_CHANNEL1_IRQ, 0);
	nvic_enable_irq(NVIC_DMA1_CHANNEL1_IRQ);	
}


void mux_wait_for_samples() {
	while (!samples_complete);
}

static void _mux_do_sample() {


	uint32_t adr_reset = (GPIO12 | GPIO13 | GPIO14) << 16;
	uint32_t adr_set = target_buffer_pos << 12;

	// Test
//	uint32_t adr_set = 0 << 12;
//	gpio_clear(GPIOA, GPIO12 | GPIO13 | GPIO14);

	GPIOA_BSRR = adr_reset | adr_set;		//Set adress of mux


	adc_sample(target_buffer + target_buffer_pos * 2, 2, 1);

}


void mux_sample(volatile uint16_t* target) {


	samples_complete=0;

	//Debug LED red
	// pwm_set_channel_raw(9, 0);
	// pwm_set_channel_raw(10, 4095);
	// pwm_set_channel_raw(11, 0);

	target_buffer = target;
	target_buffer_pos = 0;
	_mux_do_sample();
}



void dma1_channel1_isr(void) {
	DMA1_IFCR |= DMA_IFCR_CTCIF1;

	if (target_buffer_pos++ < 8) {
		_mux_do_sample();
	} else {
		//Debug LED green
		// pwm_set_channel_raw(9, 0);
		// pwm_set_channel_raw(10, 0);
		// pwm_set_channel_raw(11, 0);
		samples_complete=1;

	}

}
