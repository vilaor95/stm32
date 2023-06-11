#ifndef __UTILS_H__
#define __UTILS_H__

#define ON 1
#define OFF 0

#define BIT(x) (1UL << (x))
#define PIN(bank, num) ((((bank) - 'A') << 8) | (num))
#define PINNO(pin) (pin & 0xff)
#define PINBANK(pin) (pin >> 8)

#endif
