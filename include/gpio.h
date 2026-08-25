#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];   // AFR[0] = AFRL (pins 0-7), AFR[1] = AFRH (pins 8-15)
} TypeDef_GPIO;


typedef struct {
    volatile uint32_t RESERVED1[12];  // offset 0x00 to 0x2C
    volatile uint32_t AHB1ENR;        // offset 0x30
    volatile uint32_t RESERVED2[3];   // offset 0x34 to 0x3C
    volatile uint32_t APB1ENR;        // offset 0x40
} TypeDef_RCC;

#endif