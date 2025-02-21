#include <stdio.h>
#include "uart.h"
#include "led.h"

#define PIN_5				(1U << 5)
#define LED_PIN				(PIN_5)

void init(void);

char key;

int main(void) {
	init();

	while (1) {
		key = uart2_read();

		if (key == 'N') {
			GPIOA->ODR |= LED_PIN;
		} else if (key == 'F') {
			GPIOA->ODR &= ~LED_PIN;
		}
	}
}

void init(void) {
	uart2_init();
	led_init();
}



