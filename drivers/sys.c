#include "sys.h"

// EXTICR[0] covers pins 0-3, EXTICR[1] pins 4-7, and so on.
// each register holds four 4-bit fields, one per pin.
void select_exti_port(sys_t *sys, uint8_t pin, exti_port_t port) {
    uint8_t reg   = pin / 4;         // which of the four registers
    uint8_t shift = (pin % 4) * 4;   // which 4-bit field inside it

    sys->EXTICR[reg] &= ~(0xFu << shift);          // clear the old port
    sys->EXTICR[reg] |= ((uint32_t)port << shift); // write the new one
}