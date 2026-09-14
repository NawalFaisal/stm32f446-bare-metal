#ifndef RCC_H
#define RCC_H
#include <stdint.h>

typedef struct {
    volatile uint32_t RESERVED1[12];  // offset 0x00 to 0x2C
    volatile uint32_t AHB1ENR;        // offset 0x30
    volatile uint32_t RESERVED2[3];   // offset 0x34 to 0x3C
    volatile uint32_t APB1ENR;        // offset 0x40
    volatile uint32_t APB2ENR;        //offset 0x44
} TypeDef_RCC;

#define RCC   ((TypeDef_RCC *)0x40023800)

#endif //RCC_H