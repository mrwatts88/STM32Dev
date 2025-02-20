// goal: light up led
/* From the nucleo 64 user manual (https://www.st.com/resource/en/user_manual/um2324-stm32-nucleo64-boards-mb1360-stmicroelectronics.pdf):
 * USER (LD4): this green LED is a user LED connected to ARDUINO® signal D13
corresponding to STM32 I/O PA5. To light the LED, a high-logic state ‘1’ has to be
written in the corresponding GPIO. A transistor is used to drive the LED when the I/O
voltage is 1.8 V. LD4 consumption does not impact the VDD STM32 power
measurement, since LD4 is isolated from it.
 */

// Port: A
// Pin:  5

// Need to find out the address for GPIO port A
// From the stm32f446mc datasheet (https://www.st.com/resource/en/datasheet/stm32f446mc.pdf):
// 0x4002 0000 - 0x4002 03FF GPIOA (look in the memory map)
// note that the GPIO blocks are part of the AHB1 bus, which is part of the peripherals block
// block diagram shows all the blocks and the buses they are connected to (e.g. GPIOA is on the AHB1 bus)
// AHB is advanced high performance bus, APB is advanced peripheral bus


#define PERIPH_BASE 		(0x40000000UL)

// BUS OFFSETS
#define AHB1PERIPH_OFFSET 	(0x00020000UL)

// BUSES
#define AHB1PERIPH_BASE 	(PERIPH_BASE + AHB1PERIPH_OFFSET)

// BLOCK OFFSETS
#define RCC_OFFSET			(0x3800UL)
#define GPIOA_OFFSET		(0UL)

// BLOCKS
#define RCC_BASE			(AHB1PERIPH_BASE + RCC_OFFSET)
#define GPIOA_BASE			(AHB1PERIPH_BASE + GPIOA_OFFSET)


// REGISTER OFFSETS
#define AHB1EN_R_OFFSET 	(0x30UL)
#define MODE_R_OFFSET		(0UL)
#define OD_R_OFFSET			(0X14UL)

// REGISTERS
#define RCC_AHB1EN_R		(*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET))
#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))
#define GPIOA_OD_R			(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

// BITS
#define GPIOAEN				(1U << 0)
#define PIN_5				(1U << 5)
#define LED_PIN				(PIN_5)

int main(void) {
	// enable clock for AHB1 BUS
	RCC_AHB1EN_R |= GPIOAEN;

	// set up pin for output mode
	GPIOA_MODE_R |= (1U << 10);
	GPIOA_MODE_R &= ~(1U << 11);

	while(1) {
		// toggle LED high/low
		GPIOA_OD_R ^= LED_PIN;

		for (volatile int i = 0;i < 100000; i++);
	}
}

