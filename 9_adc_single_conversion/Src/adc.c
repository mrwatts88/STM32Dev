#include "adc.h"
#include "stm32f4xx.h"

void init_adc_pa1(void) {
	// datasheet: https://www.st.com/resource/en/datasheet/stm32f446mc.pdf

	// from the datasheet, Figure 3. STM32F446xC/E block diagram, ADC1 is on bus APB2
	// enable clock for APB2
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	// 1st conversion in regular sequence = channel 1
	ADC1->SQR3 &= ~ADC_SQR3_SQ1_Msk;
	ADC1->SQR3 |= ADC_SQR3_SQ1_0;

	// Regular channel sequence length = 1
	ADC1->SQR1 &= ~ADC_SQR1_L_Msk;

	// enable ADC module
	ADC1->CR2 |= ADC_CR2_ADON;

	// enable GPIOA clock for AHB1 BUS
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// from the datasheet Table 10. STM32F446xx pin and ball descriptions
	// channel 1 (ADC123_IN1) is on pin PA1.
	// set up PA1 for analog mode
	GPIOA->MODER &= ~GPIO_MODER_MODER1_Msk;
	GPIOA->MODER |= (GPIO_MODER_MODER1_0 | GPIO_MODER_MODER1_1);
}

void start_conversion(void) {
	// Start Conversion of regular channels
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void) {
	// wait for conversion to be complete
	while (!(ADC1->SR & ADC_CSR_EOC1))
		;

	// read converted value
	return ADC1->DR;
}
