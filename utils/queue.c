#include "queue.h"

static void copy(uint8_t *dst, const uint8_t *src, uint32_t n) {
    while (n--) { *dst++ = *src++; }
}

int q_init(queue_t *q, void *buf, uint32_t item_size, uint32_t capacity) {
    if (capacity == 0 || (capacity & (capacity - 1)) != 0) {
        return 0; 
    }
    q->buf       = (uint8_t *)buf;
    q->item_size = item_size;
    q->mask      = capacity - 1;
    q->head      = 0;
    q->tail      = 0;
    return 1;
}

int q_put(queue_t *q, const void *item) {
    uint32_t next = (q->head + 1) & q->mask;
    if (next == q->tail) return 0; // full, drop it and say so

    copy(&q->buf[q->head * q->item_size], (const uint8_t *)item, q->item_size);

    __asm volatile ("" ::: "memory");
    q->head = next;
    return 1;
}

int q_get(queue_t *q, void *out) {
    if (q->tail == q->head) return 0; // empty

    copy((uint8_t *)out, &q->buf[q->tail * q->item_size], q->item_size);

    __asm volatile ("" ::: "memory"); 
    q->tail = (q->tail + 1) & q->mask;
    return 1;
}

uint32_t q_count(queue_t *q) {
    return (q->head - q->tail) & q->mask;
}