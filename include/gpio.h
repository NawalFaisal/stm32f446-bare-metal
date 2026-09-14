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

#define GPIOA ((TypeDef_GPIO *)0x40020000)
#define GPIOC ((TypeDef_GPIO *)0x40020800)


void set_led(TypeDef_GPIO *port, uint8_t pin);
void reset_led(TypeDef_GPIO *port, uint8_t pin);

uint8_t set_button(TypeDef_GPIO *port, uint8_t pin);


#endif
