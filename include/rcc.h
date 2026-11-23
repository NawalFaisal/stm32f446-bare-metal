#ifndef RCC_H
#define RCC_H
#include <stdint.h>

typedef struct {
    volatile uint32_t RESERVED1[12]; // 0x00 - 0x2C
    volatile uint32_t AHB1ENR;       // 0x30
    volatile uint32_t AHB2ENR;       // 0x34
    volatile uint32_t AHB3ENR;       // 0x38
    volatile uint32_t RESERVED2;     // 0x3C
    volatile uint32_t APB1ENR;       // 0x40
    volatile uint32_t APB2ENR;       // 0x44
} rcc_t;

#define RCC ((rcc_t *)0x40023800)

//remember high  byte picks the bus, low byte is the bit within that register,
//so the caller never has to know which bus a peripheral lives on  
#define RCC_BUS_AHB1 0x0000
#define RCC_BUS_APB1 0x0100
#define RCC_BUS_APB2 0x0200

typedef enum {
    RCC_GPIOA  = RCC_BUS_AHB1 | 0,
    RCC_GPIOB  = RCC_BUS_AHB1 | 1,
    RCC_GPIOC  = RCC_BUS_AHB1 | 2,

    RCC_USART2 = RCC_BUS_APB1 | 17,

    RCC_SPI1   = RCC_BUS_APB2 | 12,
    RCC_SYSCFG = RCC_BUS_APB2 | 14,
} rcc_periph_t;

void rcc_enable(rcc_periph_t periph);
void rcc_disable(rcc_periph_t periph);

#endif // RCC_H