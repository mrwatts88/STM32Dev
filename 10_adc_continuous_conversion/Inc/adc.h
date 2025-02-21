/*
 * adc.h
 *
 *  Created on: Feb 21, 2025
 *      Author: mattwatts
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void init_adc_pa1(void);
void start_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
