#ifndef EXTI_H
#define EXTI_H
#include <stdint.h>

typedef struct {
    volatile uint32_t IMR;    // 0x00  interrupt mask
    volatile uint32_t EMR;    // 0x04  event mask
    volatile uint32_t RTSR;   // 0x08  rising trigger select
    volatile uint32_t FTSR;   // 0x0C  falling trigger select
    volatile uint32_t SWIER;  // 0x10  software interrupt event
    volatile uint32_t PR;     // 0x14  pending
} exti_t;

#define EXTI ((exti_t *)0x40013C00)

void enable_exti_interrupt(exti_t *exti, uint8_t line);
void disable_exti_interrupt(exti_t *exti, uint8_t line);
void rising_exti_interrupt(exti_t *exti, uint8_t line);
void falling_exti_interrupt(exti_t *exti, uint8_t line);
void clear_exti_pending(exti_t *exti, uint8_t line);
uint32_t read_exti_pending(exti_t *exti, uint8_t line);

#endif // EXTI_H