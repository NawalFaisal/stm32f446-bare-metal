#ifndef RINGBUFFER_H
#define RINGBUFFER_H
#include <stdint.h>

#define RB_MAXSIZE 64

typedef struct{
    char volatile buf[RB_MAXSIZE]; 
    uint8_t volatile head; // 0-63 index
    uint8_t volatile tail;  //0-63 index
}TypeDef_RINGBUF;

#endif //RINGBUFFER_H