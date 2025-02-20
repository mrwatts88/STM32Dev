#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"

#define SYS_FREQ			(16000000)
#define APB1_CLK			SYS_FREQ
#define UART_BAUDRATE		115200

void uart2_tx_init(void);

#endif /* UART_H_ */
