#ifndef QUEUE_H
#define QUEUE_H
#include <stdint.h>

// single producer single consumer queue. 
typedef struct {
    uint8_t *buf;            
    uint32_t item_size;      
    uint32_t mask;           
    volatile uint32_t head;  // producer writes, consumer only reads
    volatile uint32_t tail;  // consumer writes, producer only reads
} queue_t;

// one slot is always left empty so full and empty can be told apart without a
// count, so usable depth is capacity - 1
int q_init(queue_t *q, void *buf, uint32_t item_size, uint32_t capacity);

int q_put(queue_t *q, const void *item); // 0 if full, nothing overwritten
int q_get(queue_t *q, void *out);        // 0 if empty

uint32_t q_count(queue_t *q);

#endif // QUEUE_H