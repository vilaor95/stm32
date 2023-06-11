#ifndef __GPIO_H__
#define __GPIO_H__

typedef struct gpio {
	volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFR[2];
} gpio_t;
#define GPIO_BASE_ADDR (0x40020000)
#define GPIO(bank) ((struct gpio*)(GPIO_BASE_ADDR + (0x400*bank)))

typedef enum {
	GPIO_MODE_INPUT		= 0x0,
	GPIO_MODE_OUTPUT	= 0x01,
	GPIO_MODE_AF		= 0x10,
	GPIO_MODE_ANALOG	= 0x11,
} GPIO_MODE_t;

static inline void gpio_set_mode(uint16_t pin, GPIO_MODE_t mode)
{
	gpio_t* gpio = GPIO(PINBANK(pin));
	int n = PINNO(pin);

	gpio->MODER &= ~(3U << (n*2));
	gpio->MODER |= ((mode&3U) << (n*2));
}

static inline void gpio_write(int pin, bool val)
{
	gpio_t* gpio = GPIO(PINBANK(pin));
	int n = PINNO(pin);

	gpio->BSRR = (1U << n << (val ? 0 : 16));
}

#endif
