#ifndef SYSTEM_H
#define SYSTEM_H

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000UL
#define LCD_REFRESH_DELAY_MS 250U

void system_init(void);

#endif