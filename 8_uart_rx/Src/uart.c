#include "stm32f4xx.h"
#include "uart.h"

void uart2_write(int ch);

int __io_putchar(int ch) {
	uart2_write(ch);
	return ch;
}

void uart2_write(int ch) {
	// make sure transmit data register is empty
	while (!(USART2->SR & USART_SR_TXE))
		;

	// write to transmit data register
	USART2->DR = (ch & 0xFF);
}

char uart2_read(void) {
	// make sure transmit data register is empty
	while (!(USART2->SR & USART_SR_RXNE))
		;

	// read from transmit data register
	return USART2->DR;
}

uint16_t compute_uart_BD(uint32_t PeriphClk, uint32_t BaudRate) {
	return (PeriphClk + BaudRate / 2U) / BaudRate;
}

void uart2_init(void) {
	// configure RX/TX pins
	// 1. enable clock access to gpio A
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	// 2. set pa2 mode to AF mode
	GPIOA->MODER &= ~(1U << 4);
	GPIOA->MODER |= (1U << 5);
	// 3. set pa2 alternate function type to AF07 (UART_TX)
	GPIOA->AFR[0] |= (7U << 8);
	// 4. set pa3 mode to AF mode
	GPIOA->MODER &= ~(1U << 6);
	GPIOA->MODER |= (1U << 7);
	// 5. set pa3 AF to AF07 (UART_RX)
	GPIOA->AFR[0] |= (7U << 12);

	// configure USART module
	// 1. enable clock access to USART2 (APB1ENR)
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	// 2. configure USART baudrate
	USART2->BRR = compute_uart_BD(APB1_CLK, UART_BAUDRATE);
	// 3. enable transmitter and receiver
	USART2->CR1 = (USART_CR1_TE | USART_CR1_RE);
	// 5. enable USART module
	USART2->CR1 |= USART_CR1_UE;
}
