#include "adc.h"
#include "systick.h"

void adc_sample(volatile uint16_t* sample, int channels, int use_interrupt) {


	dma_channel_reset(DMA1, DMA_CHANNEL1);

	dma_set_peripheral_address(DMA1, DMA_CHANNEL1, (uint32_t)&ADC1_DR);
	dma_set_memory_address(DMA1, DMA_CHANNEL1,(uint32_t)sample);
	dma_set_number_of_data(DMA1, DMA_CHANNEL1, channels);
	dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);
	dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL1);
	dma_enable_circular_mode(DMA1, DMA_CHANNEL1);
	dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_16BIT);
	dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_16BIT);
	dma_set_priority(DMA1, DMA_CHANNEL1, DMA_CCR_PL_VERY_HIGH);

	if (use_interrupt) {
		dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);
	}

	dma_enable_channel(DMA1, DMA_CHANNEL1);

	adc_start_conversion_regular(ADC1);

}

void adc_rcc_init() {
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_DMA1);
	rcc_periph_clock_enable(RCC_ADC1);

}

void adc_gpio_init() {
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO4 | GPIO5);

}

void adc_init() {

	adc_rcc_init();
	adc_gpio_init();

	const int channels = 2;

	adc_off(ADC1);

	adc_enable_scan_mode(ADC1);	
	adc_set_single_conversion_mode(ADC1);

	adc_set_right_aligned(ADC1);
	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_239DOT5CYC);
	adc_enable_external_trigger_regular(ADC1, ADC_CR2_EXTSEL_SWSTART);
	adc_enable_dma(ADC1);
	
	adc_power_on(ADC1);


	systick_sleep_ms(2);	//Sleeping 1 ms may be less than one ms if systick is about to happen, 
	// we actually just need to wait 3µS according to http://libopencm3.github.io/docs/latest/stm32f1/html/group__adc__file.html#ga51f01f6dedbcfc4231e0fc1d8943d956

	adc_reset_calibration(ADC1);
	adc_calibration(ADC1);

	uint8_t channel_array[2];
	channel_array[0] = 4;
	channel_array[1] = 5;
	
	adc_set_regular_sequence(ADC1, channels, channel_array);

}