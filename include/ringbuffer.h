#ifndef RINGBUFFER_H
#define RINGBUFFER_H
#include <stdint.h>

#define RB_MAXSIZE 64

typedef struct {
    char volatile buf[RB_MAXSIZE];
    uint8_t volatile head; // 0-63 index
    uint8_t volatile tail; // 0-63 index
} ringbuf_t;

int rb_get(ringbuf_t *rb, char *c);
void rb_put(ringbuf_t *rb, char c);

#endif // RINGBUFFER_H