#include <stdint.h>

typedef struct {
    volatile uint32_t SR;    // offset 0x00
    volatile uint32_t DR;    // offset 0x04
    volatile uint32_t BRR;   // offset 0x08
    volatile uint32_t CR1;   // offset 0x0C
} TypeDef_USART;