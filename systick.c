#include <inttypes.h>

#include "systick.h"

#include "utils.h"

static volatile uint32_t s_ticks;

void SysTick_Handler(void)
{
	s_ticks++;
}

uint32_t get_systick()
{
	return s_ticks;
}
