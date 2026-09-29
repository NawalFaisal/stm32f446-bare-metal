#include "ringbuffer.h"


void rb_put(TypeDef_RINGBUF *rb, char c){
    int next = (rb->head + 1) % RB_MAXSIZE;
    if(next != rb->tail){
        rb->buf[rb->head] = c;
        rb->head = next;
    }
}

int rb_get(TypeDef_RINGBUF *rb, char *c){
    if(rb->tail == rb->head) return 0;  //return 0 bcuz its empty
    *c = rb->buf[rb->tail]; //go to wherever c points, write the byte there.
    rb->tail = (rb->tail + 1) % RB_MAXSIZE;
    return 1;
}