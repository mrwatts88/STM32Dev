#include "stm32f4xx.h"
#include "led.h"

void led_init() {
	// enable GPIOA clock for AHB1 BUS
	RCC->AHB1ENR |= GPIOAEN;

	// set up PA5 for output mode
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);
}
