#include "timer.h"

bool timer_expired(uint32_t *expiration, uint32_t period, uint32_t now)
{
	if (now + period < *expiration) *expiration = 0;
	if (*expiration == 0) *expiration = now + period;
	if (*expiration > now) return false;
	*expiration = ((now - *expiration) > period) ? now + period : *expiration + period;
	return true;
}
