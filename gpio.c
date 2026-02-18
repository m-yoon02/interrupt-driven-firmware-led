#include "gpio.h"
#include <avr/io.h>

void gpio_init(void) {
  // Onboard LED is PB5 (Arduino D13)
  DDRB |= (1 << DDB5);     // PB5 output
  PORTB &= ~(1 << PORTB5); // start off
}

void led_set(uint8_t on) {
  if (on) PORTB |=  (1 << PORTB5);
  else    PORTB &= ~(1 << PORTB5);
}

void led_toggle(void) {
  // Fast toggle on AVR: write 1 to PIN register bit
  PINB = (1 << PINB5);
}
