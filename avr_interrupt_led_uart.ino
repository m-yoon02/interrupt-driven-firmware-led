#include <avr/interrupt.h>

extern "C" {
  #include "gpio.h"
  #include "timer.h"
  #include "uart.h"
  #include "patterns.h"
  #include "cli.h"
}

void setup() {
  gpio_init();
  timer1_init_10ms();
  uart_init(115200);

  sei(); // enable global interrupts

  uart_puts("\r\nAVR firmware ready. Type 'help' + Enter.\r\n");
}

void loop() {
  cli_poll();
  patterns_poll();
}
