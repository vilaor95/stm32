#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "stm32f446xx.h"

#include "utils.h"

uint32_t get_systick(void);

#define SYSTICK SysTick

static inline void systick_init(uint32_t ticks)
{
	if ((ticks - 1) > 0xffffff) return;

	SYSTICK->LOAD = ticks - 1;

	SYSTICK->VAL = 0;

	SYSTICK->CTRL = BIT(0) | BIT(1) | BIT(2);

	RCC->APB2ENR |= BIT(14);
}
#define HSI_FREQUENCY (16000000)

#endif
