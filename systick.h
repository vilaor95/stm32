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
#define HSI_FREQUENCY (16 * 1000000) //16 MHz

#define PLL_M (8)
#define PLL_N (180)
#define PLL_P (2)

#define PLL_HSI_INPUT (16)

#define PLL_FREQ (PLL_HSI_INPUT / PLL_M * PLL_N / PLL_P)
#define CPU_FREQ (PLL_FREQ * 1000000)

#define APB1_PRE (5) //Clock between 4
#define APB2_PRE (4) //Clock between 2

#define APB1_FREQ (CPU_FREQ / 4)
#define APB2_FREQ (CPU_FREQ / 2)

static inline void clock_init(void)
{
	//Flash latency to Wait State 5 (6 CPU cycles) for 180MHz clock
	//Also, enable instruction prefetch and cache
	FLASH->ACR |= (5UL | BIT(8) | BIT(9)); 

	//Configure PLL
	RCC->PLLCFGR &= ~(BIT(18)-1); //Clear PLL multipliers (P and N) and input divisor (M)
	RCC->PLLCFGR |= (((PLL_P-2) & 3) << 16);
	RCC->PLLCFGR |= (PLL_N << 6 | PLL_M);

	//Enable PLL
	RCC->CR |= BIT(24);	
	while ((RCC->CR & BIT(25)) == 0) (void)0; //Wait until PLL is ready/locked

	//Set APB1 and APB2 prescaler
	RCC->CFGR |= (APB1_PRE << 10);
	RCC->CFGR |= (APB2_PRE << 13);

	//Set PLL as clock source
	RCC->CFGR |= 2;

	while ((RCC->CFGR & BIT(12)) == 0) (void)0; //Wait until done 
}

#endif
