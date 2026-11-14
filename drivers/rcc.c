#include "rcc.h"
#include <stdint.h>

// This file will create drivers to turn on different buses.
void init_RCC_AHB1LPENR(TypeDef_RCC *port, uint8_t pin) {
    port->AHB1ENR &= ~(3 << pin); // clear
    port->AHB1ENR |= (1 << pin);  // turn on
}

void init_RCC_APB1ENR(TypeDef_RCC *port, uint8_t pin) {
    port->APB1ENR &= ~(3 << pin);
    port->APB1ENR |= (1 << pin);
}

void init_RCC_APB2ENR(TypeDef_RCC *port, uint8_t pin) {
    port->APB2ENR &= ~(3 << pin);
    port->APB2ENR |= (1 << pin);
}
