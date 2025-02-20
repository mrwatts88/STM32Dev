#include "stm32f4xx.h"

#define GPIOAEN				(1U << 0)
#define PIN_5				(1U << 5)
#define PIN_13				(1U << 13)
#define BTN_PIN				(PIN_13)
#define LED_PIN				(PIN_5)

int main(void) {
	// enable clock for AHB1 BUS
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	// set up pin 5 for output mode
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	// set up pin 13 for input mode
	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);

	while (1) {
		// if button is pressed pin 13 will be high
		if (GPIOC->IDR & BTN_PIN) {
			// turn LED on
			GPIOA->BSRR = LED_PIN;
		} else {
			// turn LED off
			GPIOA->BSRR = LED_PIN << 16;
		}
	}
}
