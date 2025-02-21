#include "systick.h"
#include "stm32f4xx.h"

void systick_delay_ms(uint32_t ms) {
	SysTick->LOAD = 16000;
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

	for (int i = 0; i < ms; i++) {
		while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
			;
	}

	SysTick->CTRL = ~SysTick_CTRL_ENABLE_Msk;
}
