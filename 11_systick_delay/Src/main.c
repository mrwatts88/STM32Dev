#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "systick.h"

void init(void);

int main(void) {
	init();

	while (1) {
		systick_delay_ms(1000);
		printf("Waited 1 second. \n\r");
	}
}

void init(void) {
	uart2_init_pa3();
}
