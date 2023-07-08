#ifndef __USART_H__
#define __USART_H__

#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

#include "stm32f446xx.h"

#include "gpio.h"
#include "systick.h"

static inline void usart_init(USART_TypeDef* usart, unsigned long baud)
{
	uint16_t tx = 0, rx = 0;
	uint32_t freq;

	if (usart == USART1) freq = APB2_FREQ, RCC->APB2ENR |= BIT(4);
	if (usart == USART2) freq = APB1_FREQ, RCC->APB1ENR |= BIT(17);
	if (usart == USART3) freq = APB1_FREQ, RCC->APB1ENR |= BIT(18);

	if (usart == USART1) tx = PIN('A', 9), rx = PIN('A', 10);
	if (usart == USART2) tx = PIN('A', 2), rx = PIN('A', 3);
	if (usart == USART3) tx = PIN('C', 10), rx = PIN('C', 11);

	gpio_set_mode(tx, GPIO_MODE_AF);
	gpio_set_af(tx, 7);
	gpio_set_mode(rx, GPIO_MODE_AF);
	gpio_set_af(rx, 7);

	usart->CR1 = 0; // Disable USART
	usart->BRR = freq / baud;
	usart->CR1 |= BIT(13) | BIT (3) | BIT(2);
}

static inline bool usart_is_ready(USART_TypeDef *usart)
{
	return usart->SR & BIT(5);
}

static inline uint8_t usart_read_byte(USART_TypeDef* usart)
{
	return (uint8_t)(usart->DR & 0xFF);
}

static inline void usart_write_byte(USART_TypeDef* usart, uint8_t data)
{
	usart->DR = data;
	while ((usart->SR & BIT(7)) == 0) (void)0; 
}

static inline void usart_write_buf(USART_TypeDef *usart, char* buf, size_t len)
{
	while(len-- > 0) usart_write_byte(usart, *(uint8_t*) buf++); 
}

#endif
