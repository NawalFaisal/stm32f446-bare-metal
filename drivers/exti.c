#include "exti.h"

void enable_exti_interrupt(exti_t *exti, uint8_t line) {
    exti->IMR |= (1u << line);          // OR, so other lines stay unmasked
}

void disable_exti_interrupt(exti_t *exti, uint8_t line) {
    exti->IMR &= ~(1u << line);         // invert the mask and AND it out
}

void rising_exti_interrupt(exti_t *exti, uint8_t line) {
    exti->RTSR |= (1u << line);
}

void falling_exti_interrupt(exti_t *exti, uint8_t line) {
    exti->FTSR |= (1u << line);
}


void clear_exti_pending(exti_t *exti, uint8_t line) {
    exti->PR = (1u << line);
}

uint32_t read_exti_pending(exti_t *exti, uint8_t line) {
    return exti->PR & (1u << line);
}