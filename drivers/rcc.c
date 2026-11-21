#include "rcc.h"



void enable_rcc_ahb1(rcc_t *rcc, uint8_t bit) { 
    rcc->AHB1ENR |= (1u << bit); 
}

void enable_rcc_apb1(rcc_t *rcc, uint8_t bit) { 
    rcc->APB1ENR |= (1u << bit); 
}

void enable_rcc_apb2(rcc_t *rcc, uint8_t bit) { 
    rcc->APB2ENR |= (1u << bit); 
}