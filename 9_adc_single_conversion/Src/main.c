#include <stdio.h>
#include "uart.h"
#include "adc.h"

void init(void);

uint32_t sensor_value;

int main(void) {
	init();

	while (1) {

	}
}

void init(void) {
	uart2_init_pa3();
	init_adc_pa1();


	while (1) {
		start_conversion();
		sensor_value = adc_read();
		for(int i = 0; i < 100000; i++);
		printf("Sensor value: %lu\r\n", sensor_value);
	}
}
