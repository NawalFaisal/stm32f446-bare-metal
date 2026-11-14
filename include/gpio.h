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
} gpio_t;

#define GPIOA ((gpio_t *)0x40020000)
#define GPIOB ((gpio_t *)0x40020400)
#define GPIOC ((gpio_t *)0x40020800)

typedef enum {
    GPIO_MODE_INPUT  = 0x0,
    GPIO_MODE_OUTPUT = 0x1,
    GPIO_MODE_AF     = 0x2,
    GPIO_MODE_ANALOG = 0x3,
} gpio_mode_t;

typedef enum {
    GPIO_PULL_NONE = 0x0,
    GPIO_PULL_UP   = 0x1,
    GPIO_PULL_DOWN = 0x2,
} gpio_pull_t;

typedef enum {
    GPIO_LOW  = 0,
    GPIO_HIGH = 1,
} gpio_state_t;

void gpio_init(gpio_t *port, uint8_t pin, gpio_mode_t mode);
void gpio_set_pull(gpio_t *port, uint8_t pin, gpio_pull_t pull);
void gpio_set_af(gpio_t *port, uint8_t pin, uint8_t af);
void gpio_set(gpio_t *port, uint8_t pin);
void gpio_reset(gpio_t *port, uint8_t pin);
void gpio_toggle(gpio_t *port, uint8_t pin);
void gpio_write(gpio_t *port, uint8_t pin, gpio_state_t state);
gpio_state_t gpio_read(gpio_t *port, uint8_t pin);

#endif /* GPIO_H */