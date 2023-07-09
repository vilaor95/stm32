#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include "stm32f446xx.h"

#define WD_PROTECTION_VAL	(0x5555)
#define WD_START_VAL		(0xCCCC)
#define WD_REFRESH_VAL		(0xAAAA)

#define WD_COUNTER_RELOAD_VAL	(0xFFF)
#define WD_PRE_VAL		(0x1)	

static inline void wd_init()
{
	//Disable write protection for PR and RLR regs
	IWDG->KR = WD_PROTECTION_VAL;
	
	IWDG->PR = WD_PRE_VAL;
	IWDG->RLR = WD_COUNTER_RELOAD_VAL;

	IWDG->KR = 0; //Enable write protection again

	while (((IWDG->SR & BIT(0)) == 0) ||
		((IWDG->SR & BIT(1)) == 0))
			(void)0; //Wait 
}

static inline void wd_start()
{
	IWDG->KR = WD_START_VAL;
}

static inline void wd_refresh()
{
	IWDG->KR = WD_REFRESH_VAL;
}

#endif
