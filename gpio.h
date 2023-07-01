#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32f446xx.h"

#define GPIO(bank) ((GPIO_TypeDef*)(GPIOA_BASE + 0x400 * ((unsigned int)bank)))

#include "utils.h"

typedef enum {
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_AF,
	GPIO_MODE_ANALOG,
} GPIO_MODE_t;

static inline void gpio_set_mode(uint16_t pin, GPIO_MODE_t mode)
{
	GPIO_TypeDef* gpio = GPIO(PINBANK(pin));
	int n = PINNO(pin);
	RCC->AHB1ENR |= BIT(PINBANK(pin));

	gpio->MODER &= ~(3U << (n*2));
	gpio->MODER |= ((mode&3U) << (n*2));
}

static inline void gpio_set_af(uint16_t pin, uint8_t af_num)
{
	GPIO_TypeDef* gpio = GPIO(PINBANK(pin));	
	int n = PINNO(pin);
	gpio->AFR[n >> 3] &= ~(15UL << ((n & 7) * 4));
	gpio->AFR[n >> 3] |= ((uint32_t)af_num << ((n & 7) * 4));
}

static inline void gpio_write(int pin, bool val)
{
	GPIO_TypeDef* gpio = GPIO(PINBANK(pin));
	int n = PINNO(pin);

	gpio->BSRR = (1U << n << (val ? 0 : 16));
}

#endif
