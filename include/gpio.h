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
    volatile uint32_t AFR[2];
} TypeDef_GPIO;

#define GPIOA ((TypeDef_GPIO *)0x40020000)
#define GPIOB ((TypeDef_GPIO *)0x40020400)
#define GPIOC ((TypeDef_GPIO *)0x40020800)

typedef enum {
    GPIO_MODE_INPUT  = 0x0,
    GPIO_MODE_OUTPUT = 0x1,
    GPIO_MODE_AF     = 0x2,
    GPIO_MODE_ANALOG = 0x3,
} gpio_mode_t;

typedef enum {
    GPIO_LOW  = 0,
    GPIO_HIGH = 1,
} gpio_state_t;

void gpio_init (TypeDef_GPIO *port, uint8_t pin, gpio_mode_t mode);


void         gpio_set   (TypeDef_GPIO *port, uint8_t pin);
void         gpio_reset (TypeDef_GPIO *port, uint8_t pin);
void         gpio_toggle(TypeDef_GPIO *port, uint8_t pin);
void         gpio_write (TypeDef_GPIO *port, uint8_t pin, gpio_state_t state);
gpio_state_t gpio_read  (TypeDef_GPIO *port, uint8_t pin);

#endif
