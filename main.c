#include <inttypes.h>
#include <stdbool.h>

#include "utils.h"
#include "rcc.h"
#include "gpio.h"
#include "systick.h"
#include "timer.h"

int main(void) {

	systick_init(HSI_FREQUENCY/1000);

	uint16_t led = PIN('A', 5);
	RCC->AHB1ENR |= BIT(PINBANK(led));
	gpio_set_mode(led, GPIO_MODE_OUTPUT);

	for (;;)
	{
		uint32_t t, period = 500;
		if (timer_expired(&t, period, get_systick()))
		{
			static bool led_on_off = true;
			gpio_write(led, led_on_off);
			led_on_off = !led_on_off;
		}
	}

	return 0;
}
