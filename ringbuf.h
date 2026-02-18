#pragma once
#include <stdint.h>

#define RINGBUF_SIZE 64

typedef struct {
  volatile uint8_t buf[RINGBUF_SIZE];
  volatile uint8_t head;
  volatile uint8_t tail;
} ringbuf_t;

void ringbuf_init(ringbuf_t *rb);
uint8_t ringbuf_push(ringbuf_t *rb, uint8_t b); // returns 1 if ok, 0 if full
uint8_t ringbuf_pop(ringbuf_t *rb, uint8_t *out); // returns 1 if ok, 0 if empty
