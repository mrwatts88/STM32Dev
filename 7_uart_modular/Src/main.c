#include <stdio.h>
#include "uart.h"

void init(void);

int main(void) {
	init();

	while (1) {
		printf("Hello world\n\r");
	}
}

void init(void) {
	uart2_tx_init();
}

