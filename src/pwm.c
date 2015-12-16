#include "pwm.h"

volatile uint32_t* pwm_channel_map[15] = {
	&TIM1_CCR1,
	&TIM1_CCR2,
	&TIM1_CCR3,
	&TIM2_CCR1,
	&TIM2_CCR2,
	&TIM2_CCR3,
	&TIM3_CCR1,
	&TIM3_CCR2,
	&TIM3_CCR3,
	&TIM15_CCR1,
	&TIM15_CCR2,
	&TIM16_CCR1,
	&TIM1_CCR4,
	&TIM2_CCR4,
	&TIM3_CCR4
};


void pwm_init() {
	pwm_rcc_init();
	pwm_gpio_init();
	pwm_set_all_raw(0);
	pwm_timers_init();
}

void pwm_timers_init() {

//Configuring timer TIM1
	TIM1_CR1 = TIM_CR1_CKD_CK_INT | TIM_CR1_CMS_EDGE;
	TIM1_ARR = PWM_TOP;
	TIM1_PSC = 0;
	TIM1_EGR = TIM_EGR_UG;
	//Setup output compare
		TIM1_CCR1 = 0;
		TIM1_CCR2 = 0;
		TIM1_CCR3 = 0;
		TIM1_CCR4 = 0;

		TIM1_BDTR |= TIM_BDTR_MOE; //test

		//TIM1_CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E; //test
		TIM1_CCER |= TIM_CCER_CC1NE | TIM_CCER_CC1P | TIM_CCER_CC2NE | TIM_CCER_CC2P | TIM_CCER_CC3NE | TIM_CCER_CC3P | TIM_CCER_CC4E;
		TIM1_CCMR1 |= TIM_CCMR1_OC1M_PWM1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_PWM1 | TIM_CCMR1_OC2PE;
		TIM1_CCMR2 |= TIM_CCMR2_OC3M_PWM1 | TIM_CCMR2_OC3PE | TIM_CCMR2_OC4M_PWM1 | TIM_CCMR2_OC4PE;

	TIM1_CR1 |= TIM_CR1_ARPE;
	TIM1_CR1 |= TIM_CR1_CEN;

//Configuring timer TIM2
	TIM2_CR1 = TIM_CR1_CKD_CK_INT | TIM_CR1_CMS_EDGE;
	TIM2_ARR = PWM_TOP;
	TIM2_PSC = 0;
	TIM2_EGR = TIM_EGR_UG;
	//Setup output compare
		TIM2_CCR1 = 0;
		TIM2_CCR2 = 0;
		TIM2_CCR3 = 0;
		TIM2_CCR4 = 0;
		TIM2_CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
		TIM2_CCMR1 |= TIM_CCMR1_OC1M_PWM1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_PWM1 | TIM_CCMR1_OC2PE;
		TIM2_CCMR2 |= TIM_CCMR2_OC3M_PWM1 | TIM_CCMR2_OC3PE | TIM_CCMR2_OC4M_PWM1 | TIM_CCMR2_OC4PE;

	TIM2_CR1 |= TIM_CR1_ARPE;
	TIM2_CR1 |= TIM_CR1_CEN;

//Configuring timer TIM3
	TIM3_CR1 = TIM_CR1_CKD_CK_INT | TIM_CR1_CMS_EDGE;
	TIM3_ARR = PWM_TOP;
	TIM3_PSC = 0;
	TIM3_EGR = TIM_EGR_UG;
	//Setup output compare
		TIM3_CCR1 = 0;
		TIM3_CCR2 = 0;
		TIM3_CCR3 = 0;
		TIM3_CCR4 = 0;
		TIM3_CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E | TIM_CCER_CC4E;
		TIM3_CCMR1 |= TIM_CCMR1_OC1M_PWM1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_PWM1 | TIM_CCMR1_OC2PE;
		TIM3_CCMR2 |= TIM_CCMR2_OC3M_PWM1 | TIM_CCMR2_OC3PE | TIM_CCMR2_OC4M_PWM1 | TIM_CCMR2_OC4PE;

	TIM3_CR1 |= TIM_CR1_ARPE;
	TIM3_CR1 |= TIM_CR1_CEN;

//Configuring timer TIM15
	TIM15_CR1 = TIM_CR1_CKD_CK_INT | TIM_CR1_CMS_EDGE;
	TIM15_ARR = PWM_TOP;
	TIM15_PSC = 0;
	TIM15_EGR = TIM_EGR_UG;
	//Setup output compare
		TIM15_CCR1 = 0;
		TIM15_CCR2 = 0;
		TIM15_CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E;
		TIM15_CCMR1 |= TIM_CCMR1_OC1M_PWM1 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2M_PWM1 | TIM_CCMR1_OC2PE;

	TIM15_BDTR |= TIM_BDTR_MOE; //test


	TIM15_CR1 |= TIM_CR1_ARPE;
	TIM15_CR1 |= TIM_CR1_CEN;

//Configuring timer TIM16
	TIM16_CR1 = TIM_CR1_CKD_CK_INT | TIM_CR1_CMS_EDGE;
	TIM16_ARR = PWM_TOP;
	TIM16_PSC = 0;
	TIM16_EGR = TIM_EGR_UG;
	//Setup output compare
		TIM16_CCR1 = 0;
		TIM16_CCER |= TIM_CCER_CC1E;
		TIM16_CCMR1 |= TIM_CCMR1_OC1M_PWM1 | TIM_CCMR1_OC1PE;


	TIM16_BDTR |= TIM_BDTR_MOE; //test


	TIM16_CR1 |= TIM_CR1_ARPE;
	TIM16_CR1 |= TIM_CR1_CEN;	
}


void pwm_gpio_init() {


//Configuring port GPIOA
	//Init pins
	gpio_clear(GPIOA, GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO6 | GPIO7 | GPIO11);
	//Configure mode
	gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO6 | GPIO7 | GPIO11);

//Configuring port GPIOB
	//Init pins
	gpio_clear(GPIOB, GPIO0 | GPIO1 | GPIO8 | GPIO10 | GPIO11 | GPIO13 | GPIO14 | GPIO15);
	//Configure mode
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO0 | GPIO1 | GPIO8 | GPIO10 | GPIO11 | GPIO13 | GPIO14 | GPIO15);


}


void pwm_rcc_init() {
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);

	rcc_periph_clock_enable(RCC_TIM1);
	rcc_periph_clock_enable(RCC_TIM2);
	rcc_periph_clock_enable(RCC_TIM3);
	rcc_periph_clock_enable(RCC_TIM15);
	rcc_periph_clock_enable(RCC_TIM16);


}

int pwm_output_filter(int v) {
	if (v < 0) v=0;
	if (v > PWM_TOP) v = PWM_TOP;
	return GAMMA_LUT[v];

}

void pwm_set_all_raw(int value) {
	for (int ch=0; ch<15; ch++) {
		pwm_set_channel_raw(ch, value);
	}
}

void pwm_set_all(int value) {
	pwm_set_all_raw(pwm_output_filter(value));
}

void pwm_set_channel_raw(int channel, int value) {
	*pwm_channel_map[channel] = value;
}

void pwm_set_channel(int channel, int value) {
	*pwm_channel_map[channel] = pwm_output_filter(value);
}