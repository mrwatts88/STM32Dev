#include "stm32f4xx.h"

#define GPIOAEN				(1U << 0)
#define PIN_5				(1U << 5)
#define LED_PIN				(PIN_5)

int main(void) {
	// enable clock for AHB1 BUS
	RCC->AHB1ENR |= GPIOAEN;

	// set up pin for output mode
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	while (1) {
		// toggle LED high/low
		GPIOA->ODR ^= LED_PIN;

		for (volatile int i = 0; i < 100000; i++)
			;
	}
}

