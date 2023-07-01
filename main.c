#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include "stm32f446xx.h"

#include "utils.h"
#include "gpio.h"
#include "systick.h"
#include "timer.h"
#include "usart.h"

int main(void) {

	systick_init(HSI_FREQUENCY/1000);

	uint16_t led = PIN('A', 5);
	gpio_set_mode(led, GPIO_MODE_OUTPUT);

	usart_init(USART2, 115200);

	for (;;)
	{
		static bool led_on_off = true;

		uint32_t t1, p1 = 500;
		if (timer_expired(&t1, p1, get_systick()))
		{
			gpio_write(led, led_on_off);
			led_on_off = !led_on_off;
		}

		uint32_t t2, p2 = 1500;
		if (timer_expired(&t2, p2, get_systick()))
		{

			printf("LED status %d tick %lu\r\n", led_on_off, get_systick());
		}
	}

	return 0;
}
