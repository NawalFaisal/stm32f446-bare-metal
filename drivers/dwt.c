#include "dwt.h"

void dwt_init(void) {
    DEMCR |= (1U << 24);     
    DWT->CYCCNT = 0;
    DWT->CTRL  |= (1U << 0); 
}

uint32_t dwt_cycles(void) {
    return DWT->CYCCNT;
}