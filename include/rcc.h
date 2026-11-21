#ifndef RCC_H
#define RCC_H
#include <stdint.h>

typedef struct {
    volatile uint32_t RESERVED1[12]; // 0x00 - 0x2C
    volatile uint32_t AHB1ENR;       // 0x30
    volatile uint32_t RESERVED2[3];  // 0x34 - 0x3C
    volatile uint32_t APB1ENR;       // 0x40
    volatile uint32_t APB2ENR;       // 0x44
} rcc_t;

#define RCC ((rcc_t *)0x40023800)

// AHB1ENR:  GPIOA 0, GPIOB 1, GPIOC 2, DMA1 21, DMA2 22
// APB1ENR:  TIM2 0, SPI2 14, USART2 17
// APB2ENR:  TIM1 0, USART1 4, SPI1 12, SYSCFG 14
void enable_rcc_ahb1(rcc_t *rcc, uint8_t bit);
void enable_rcc_apb1(rcc_t *rcc, uint8_t bit);
void enable_rcc_apb2(rcc_t *rcc, uint8_t bit);

#endif // RCC_H