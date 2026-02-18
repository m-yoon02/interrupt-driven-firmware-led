#include "patterns.h"
#include "timer.h"
#include "gpio.h"

static volatile uint8_t  g_pattern_id = 0;
static volatile uint16_t g_period_ms  = 250; // default speed
static uint32_t g_next_deadline = 0;

static uint8_t scanner_phase = 0;
static uint8_t binary_counter = 0;

void patterns_set(uint8_t id) {
  g_pattern_id = id % 3;
  scanner_phase = 0;
  binary_counter = 0;
}

uint8_t patterns_get(void) {
  return g_pattern_id;
}

void patterns_set_speed_ms(uint16_t ms) {
  if (ms < 20) ms = 20;
  if (ms > 5000) ms = 5000;
  g_period_ms = ms;
}

uint16_t patterns_get_speed_ms(void) {
  return g_period_ms;
}

static void pattern_update(uint8_t id) {
  switch (id) {
    case 0: // BLINK
      led_toggle();
      break;

    case 1: // "SCANNER" on 1 LED -> do a distinctive double-pulse
      // Every update advances phase: on, off, on, long off
      scanner_phase = (scanner_phase + 1) % 4;
      if (scanner_phase == 0 || scanner_phase == 2) led_set(1);
      else led_set(0);
      break;

    case 2: // "BINARY" on 1 LED -> shows LSB toggling (fast/visible at low speed)
      binary_counter++;
      led_set(binary_counter & 0x01);
      break;
  }
}

void patterns_poll(void) {
  uint32_t now_ticks = timer_ticks_10ms();

  // Convert ms to 10ms ticks (rounded up)
  uint16_t ticks_period = (uint16_t)((g_period_ms + 9) / 10);
  if (ticks_period == 0) ticks_period = 1;

  if (g_next_deadline == 0) {
    g_next_deadline = now_ticks + ticks_period;
  }

  if ((int32_t)(now_ticks - g_next_deadline) >= 0) {
    pattern_update(g_pattern_id);
    g_next_deadline += ticks_period;
  }
}
