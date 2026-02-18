#pragma once
#include <stdint.h>

void uart_init(uint32_t baud);
void uart_putc(uint8_t c);
void uart_puts(const char *s);
void uart_print_u32(uint32_t v);

uint8_t uart_getc_nonblock(uint8_t *out); // 1 if got byte, 0 otherwise
