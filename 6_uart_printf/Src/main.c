#include "stm32f4xx.h"
#include <stdio.h>

#define SYS_FREQ			(16000000)
#define APB1_CLK			SYS_FREQ
#define UART_BAUDRATE		115200

void uart2_tx_init(void);
static uint16_t compute_uart_BD(uint32_t, uint32_t);
void uart2_write(int);

int main(void) {
	uart2_tx_init();
	while (1) {
		printf("Hello world\n\r");
	}
}


int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}

void uart2_write(int ch) {
	// make sure transmit data register is empty
	while (!(USART2->SR & USART_SR_TXE));

	// write to transmit data register
	USART2->DR = (ch & 0xFF);
}

void uart2_tx_init(void) {
	// configure PA2
	// 1. enable clock access to gpio A
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	// 2. set pa2 mode to AF mode
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);
	// 3. set pa2 alternate function type to AF07 (UART_TX)
	GPIOA->AFR[0] |= (7U << 8);

	// configure USART module
	// 1. enable clock access to USART2 (APB1ENR)
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	// 2. configure USART baudrate
	USART2->BRR = compute_uart_BD(APB1_CLK, UART_BAUDRATE);
	// 3. enable transmitter
	USART2->CR1 = USART_CR1_TE;
	// 4. enable USART module
	USART2->CR1 |= USART_CR1_UE;
}

static uint16_t compute_uart_BD(uint32_t PeriphClk, uint32_t BaudRate) {
	return (PeriphClk + BaudRate/2U)/BaudRate;
}



