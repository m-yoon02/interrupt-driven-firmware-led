#pragma once
#include <stdint.h>

void patterns_set(uint8_t id);
uint8_t patterns_get(void);

void patterns_set_speed_ms(uint16_t ms);
uint16_t patterns_get_speed_ms(void);

void patterns_poll(void);
