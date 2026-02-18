#pragma once
#include <stdint.h>

void gpio_init(void);
void led_set(uint8_t on);
void led_toggle(void);
