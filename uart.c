#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "ringbuf.h"

static ringbuf_t rx_rb;

static void uart_set_baud_u2x(uint32_t baud) {
  // Use double speed (U2X0=1): UBRR = F_CPU/(8*baud) - 1
  UCSR0A |= (1 << U2X0);

  uint16_t ubrr = (uint16_t)((F_CPU / (8UL * baud)) - 1UL);
  UBRR0H = (uint8_t)(ubrr >> 8);
  UBRR0L = (uint8_t)(ubrr & 0xFF);
}

void uart_init(uint32_t baud) {
  ringbuf_init(&rx_rb);

  uart_set_baud_u2x(baud);

  // 8N1 frame
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  // Enable RX, TX and RX complete interrupt
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
}

ISR(USART_RX_vect) {
  uint8_t b = UDR0; // reading clears RX flag
  ringbuf_push(&rx_rb, b);
}

uint8_t uart_getc_nonblock(uint8_t *out) {
  return ringbuf_pop(&rx_rb, out);
}

void uart_putc(uint8_t c) {
  while (!(UCSR0A & (1 << UDRE0))) { /* wait */ }
  UDR0 = c;
}

void uart_puts(const char *s) {
  while (*s) uart_putc((uint8_t)*s++);
}

void uart_print_u32(uint32_t v) {
  char buf[11];
  int i = 10;
  buf[i] = '\0';
  if (v == 0) {
    uart_putc('0');
    return;
  }
  while (v > 0 && i > 0) {
    buf[--i] = (char)('0' + (v % 10));
    v /= 10;
  }
  uart_puts(&buf[i]);
}
