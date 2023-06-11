#include <inttypes.h>
#include <stdbool.h>

void delay(uint32_t ms);

#include "utils.h"
#include "rcc.h"
#include "gpio.h"
#include "systick.h"

int main(void) {

	systick_init(HSI_FREQUENCY/1000);

	uint16_t led = PIN('A', 5);
	RCC->AHB1ENR |= BIT(PINBANK(led));
	gpio_set_mode(led, GPIO_MODE_OUTPUT);

	for (;;)
	{
		gpio_write(led, ON);
		delay(1000);
		gpio_write(led, OFF);
		delay(1000);
	}

	return 0;
}

void delay(uint32_t ms)
{
	uint32_t until = get_systick() + ms;
	while (get_systick() < until) (void) 0;
}

bool timer_expired(uint32_t *expiration, uint32_t period, uint32_t now)
{
	if (now + period < *expiration) *expiration = 0;
	if (*expiration == 0) *expiration = now + period;
	if (*expiration > now) return false;
	*expiration = ((now - *expiration) > period) ? now + period : *expiration + period;
	return true;
}
