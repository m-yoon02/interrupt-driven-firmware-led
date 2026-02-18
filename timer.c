#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t g_ticks_10ms = 0;

void timer1_init_10ms(void) {
  // Timer1 CTC, compare match A every 10ms
  // F_CPU = 16MHz, prescaler=64 => 250kHz timer clock
  // 10ms => 2500 counts => OCR1A = 2499

  TCCR1A = 0;
  TCCR1B = 0;

  TCCR1B |= (1 << WGM12);              // CTC mode
  TCCR1B |= (1 << CS11) | (1 << CS10); // prescaler 64

  OCR1A = 2499;

  TIMSK1 |= (1 << OCIE1A);             // enable compare match A interrupt
}

ISR(TIMER1_COMPA_vect) {
  g_ticks_10ms++;
}

uint32_t timer_ticks_10ms(void) {
  uint32_t t;
  uint8_t sreg = SREG;
  cli();
  t = g_ticks_10ms;
  SREG = sreg;
  return t;
}
