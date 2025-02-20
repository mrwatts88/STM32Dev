// goal: convert the 0_led_toggle_address code to use structs for register access
#include <stdint.h>

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

// BITS
#define GPIOAEN				(1U << 0)
#define PIN_5				(1U << 5)
#define LED_PIN				(PIN_5)

// REGISTER ACCESS STRUCTS
typedef struct {
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR; /* !< RCC AHB1 peripheral clock register, Address offset: 0x30 */
} RCC_TypeDef;

typedef struct {
	volatile uint32_t MODER; /* !< GPIO port mode register, Address offset: 0x00 */
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR; /* !< GPIO port output data register, Address offset: 0x14 */
} GPIO_TypeDef;

#define RCC		((RCC_TypeDef*)RCC_BASE)
#define GPIOA	((GPIO_TypeDef*)GPIOA_BASE)

int main(void) {
	// enable clock for AHB1 BUS
	RCC->AHB1ENR |= GPIOAEN;

	// set up pin for output mode
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	while (1) {
		// toggle LED high/low
		GPIOA->ODR ^= LED_PIN;

		for (volatile int i = 0; i < 100000; i++)
			;
	}
}

