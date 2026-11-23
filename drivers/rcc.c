#include "rcc.h"

// nothing is read or written in here, its only an address
static volatile uint32_t *bus_reg(rcc_periph_t periph) {
    switch (periph & 0xFF00U) {
        case RCC_BUS_AHB1: return &RCC->AHB1ENR;
        case RCC_BUS_APB1: return &RCC->APB1ENR;
        case RCC_BUS_APB2: return &RCC->APB2ENR;
        default: return 0;
    }
}

void rcc_enable(rcc_periph_t periph) {
    volatile uint32_t *reg = bus_reg(periph);
    if (reg) {
        //dereference to change hardware
        *reg |= (1U << (periph & 0xFFU));
    }
}

void rcc_disable(rcc_periph_t periph) {
    volatile uint32_t *reg = bus_reg(periph);
    if (reg) {
        *reg &= ~(1U << (periph & 0xFFU));
    }
}