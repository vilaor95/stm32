#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#include "utils.h"
#include "rcc.h"
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
		uint32_t t1, p1 = 500;
		if (timer_expired(&t1, p1, get_systick()))
		{
			static bool led_on_off = true;
			gpio_write(led, led_on_off);
			led_on_off = !led_on_off;
		}

		uint32_t t2, p2 = 2000;
		if (timer_expired(&t2, p2, get_systick()))
		{
			usart_write_buf(USART2, (uint8_t*)"Hi\n\r", 3);
		}

	
	}

	return 0;
}
