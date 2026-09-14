#ifndef NVIC_H
#define NVIC_H
#include <stdint.h>

typedef struct {
    volatile uint32_t ISER[8];      /* 0x000  set enable*/ 
    uint32_t RESERVED0[24];
    volatile uint32_t ICER[8];      /* 0x080 clean enable*/
    uint32_t RESERVED1[24];
    volatile uint32_t ISPR[8];      /* 0x100 set pending*/
    uint32_t RESERVED2[24];
    volatile uint32_t ICPR[8];      /* 0x180 clear pending*/
    uint32_t RESERVED3[24];
    volatile uint32_t IABR[8];      /* 0x200 activity bit*/
    uint32_t RESERVED4[56];
    volatile uint32_t IPR[60];      /* 0x300 prority bit*/
} TypeDef_NVIC;

#define NVIC ((TypeDef_NVIC *)0xE000E100)
#endif //NVIC_H