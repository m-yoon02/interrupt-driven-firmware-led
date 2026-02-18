#include "ringbuf.h"

void ringbuf_init(ringbuf_t *rb) {
  rb->head = 0;
  rb->tail = 0;
}

uint8_t ringbuf_push(ringbuf_t *rb, uint8_t b) {
  uint8_t next = (uint8_t)(rb->head + 1) % RINGBUF_SIZE;
  if (next == rb->tail) return 0; // full
  rb->buf[rb->head] = b;
  rb->head = next;
  return 1;
}

uint8_t ringbuf_pop(ringbuf_t *rb, uint8_t *out) {
  if (rb->tail == rb->head) return 0; // empty
  *out = rb->buf[rb->tail];
  rb->tail = (uint8_t)(rb->tail + 1) % RINGBUF_SIZE;
  return 1;
}
