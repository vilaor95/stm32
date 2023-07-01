#ifndef __USART_H__
#define __USART_H__

#include <inttypes.h>

#include "gpio.h"
#include "rcc.h"
#include "systick.h"

typedef struct usart {
	volatile uint32_t SR, DR, BRR, CR1, CR2, CR3, GTPR; 
} usart_t;

#define USART1 ((usart_t*)0x40010400)
#define USART2 ((usart_t*)0x40004400)
#define USART3 ((usart_t*)0x40004800)
#define UART4  ((usart_t*)0x40004C00)
#define UART5  ((usart_t*)0x40005000)
#define USART6 ((usart_t*)0x40011400)

static inline void usart_init(usart_t* usart, unsigned long baud)
{
	uint16_t tx = 0, rx = 0;

	if (usart == USART1) RCC->APB1ENR |= BIT(4);
	if (usart == USART2) RCC->APB1ENR |= BIT(17);
	if (usart == USART3) RCC->APB1ENR |= BIT(18);

	if (usart == USART1) tx = PIN('A', 9), rx = PIN('A', 10);
	if (usart == USART2) tx = PIN('A', 2), rx = PIN('A', 3);
	if (usart == USART3) tx = PIN('C', 10), rx = PIN('C', 11);

	gpio_set_mode(tx, GPIO_MODE_AF);
	gpio_set_af(tx, 7);
	gpio_set_mode(rx, GPIO_MODE_AF);
	gpio_set_af(rx, 7);

	usart->CR1 = 0; // Disable USART
	usart->BRR = HSI_FREQUENCY / baud;
	usart->CR1 |= BIT(13) | BIT (3) | BIT(2);
}

static inline bool usart_is_ready(usart_t *usart)
{
	return usart->SR & BIT(5);
}

static inline uint8_t usart_read_byte(usart_t* usart)
{
	return (uint8_t)(usart->DR & 0xFF);
}

static inline void usart_write_byte(usart_t* usart, char data)
{
	usart->DR = data;
	while ((usart->SR & BIT(7)) == 0) (void)0; 
}

static inline void usart_write_buf(usart_t *usart, char* buf, size_t len)
{
	while(len-- > 0) usart_write_byte(usart, *buf++); 
}

#endif
