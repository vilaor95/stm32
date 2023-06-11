#ifndef __TIMER_H__
#define __TIMER_H__

#include <inttypes.h>
#include <stdbool.h>

bool timer_expired(uint32_t* expiration, uint32_t period, uint32_t now);

#endif
