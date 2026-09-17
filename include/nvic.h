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

/* ISER[0] = 00000000 00000000 00000000 00000000  0-31
   ISER[1] enables irq between 32-63
   ISER[2] enables irq 64-95
   ISER[3] enables irq 96-127
   ISER[4] enables irq 128-159
   ISER[5] enables irq 160-191
   ISER[6] enables irq 192-224
   ISER[7] enables irq 225 - 256   
   8 x 32 = 256
    each bite repersnets one irq so iser[10] can enable interupts that are between the numbers of 0-31
    so to get 40 just do irq / 32 = 1 and irq % 32  
    

*/
