#include "cli.h"
#include "uart.h"
#include "patterns.h"
#include "timer.h"
#include <stdint.h>
#include <string.h>

#define LINE_MAX 64

static char line[LINE_MAX];
static uint8_t line_len = 0;

static void print_help(void) {
  uart_puts(
    "Commands:\r\n"
    "  help\r\n"
    "  pattern <0|1|2>\r\n"
    "  speed <ms>     (20..5000)\r\n"
    "  status\r\n"
  );
}

static uint8_t is_space(char c) {
  return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
}

static int parse_int(const char *s) {
  int v = 0;
  int sign = 1;
  if (*s == '-') { sign = -1; s++; }
  while (*s >= '0' && *s <= '9') {
    v = v * 10 + (*s - '0');
    s++;
  }
  return v * sign;
}

static void handle_line(char *s) {
  // Tokenize in-place
  while (is_space(*s)) s++;
  if (*s == '\0') return;

  char *cmd = s;
  while (*s && !is_space(*s)) s++;
  if (*s) *s++ = '\0';

  while (is_space(*s)) s++;
  char *arg = (*s) ? s : NULL;

  if (strcmp(cmd, "help") == 0) {
    print_help();
    return;
  }

  if (strcmp(cmd, "pattern") == 0) {
    if (!arg) { uart_puts("Usage: pattern <0|1|2>\r\n"); return; }
    int id = parse_int(arg);
    if (id < 0 || id > 2) { uart_puts("pattern must be 0..2\r\n"); return; }
    patterns_set((uint8_t)id);
    uart_puts("OK\r\n");
    return;
  }

  if (strcmp(cmd, "speed") == 0) {
    if (!arg) { uart_puts("Usage: speed <ms>\r\n"); return; }
    int ms = parse_int(arg);
    patterns_set_speed_ms((uint16_t)ms);
    uart_puts("OK\r\n");
    return;
  }

  if (strcmp(cmd, "status") == 0) {
    uart_puts("ticks10ms=");
    uart_print_u32(timer_ticks_10ms());
    uart_puts(" pattern=");
    uart_putc((char)('0' + patterns_get()));
    uart_puts(" speed_ms=");
    uart_print_u32(patterns_get_speed_ms());
    uart_puts("\r\n");
    return;
  }

  uart_puts("Unknown command. Type 'help'\r\n");
}

void cli_poll(void) {
  uint8_t b;
  while (uart_getc_nonblock(&b)) {
    char c = (char)b;

    // echo (optional)
    uart_putc((uint8_t)c);

    if (c == '\r' || c == '\n') {
      uart_puts("\r\n");
      line[line_len] = '\0';
      handle_line(line);
      line_len = 0;
      uart_puts("> ");
      continue;
    }

    if (c == 0x08 || c == 0x7F) { // backspace
      if (line_len > 0) line_len--;
      continue;
    }

    if (line_len < (LINE_MAX - 1)) {
      line[line_len++] = c;
    }
  }
}
