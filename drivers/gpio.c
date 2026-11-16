#include "gpio.h"

static inline uint32_t pin_mask(uint8_t pin) {
    return (1U << pin);
}

void gpio_init(gpio_t *port, uint8_t pin, gpio_mode_t mode) {
    if (pin > 15U) return;
    port->MODER &= ~(0x3U << (pin * 2U));
    port->MODER |= ((uint32_t)mode << (pin * 2U));
}

void gpio_set_pull(gpio_t *port, uint8_t pin, gpio_pull_t pull) {
    if (pin > 15U) return;
    port->PUPDR &= ~(0x3U << (pin * 2U));
    port->PUPDR |= ((uint32_t)pull << (pin * 2U));
}

/* Selects the alternate function only. The pin must already be in
   GPIO_MODE_AF -- call gpio_init() first. */
void gpio_set_af(gpio_t *port, uint8_t pin, uint8_t af) {
    if (pin > 15U || af > 15U) return;
    port->AFR[pin / 8U] &= ~(0xFU << ((pin % 8U) * 4U));
    port->AFR[pin / 8U] |= ((uint32_t)af << ((pin % 8U) * 4U));
}

/* BSRR is write-only: the low half sets a pin, the high half clears it.
   A single store, so these are safe to call from an interrupt handler. */
void gpio_set(gpio_t *port, uint8_t pin) {
    if (pin > 15U) return;
    port->BSRR = pin_mask(pin);
}

void gpio_reset(gpio_t *port, uint8_t pin) {
    if (pin > 15U) return;
    port->BSRR = (pin_mask(pin) << 16U);
}

void gpio_toggle(gpio_t *port, uint8_t pin) {
    if (pin > 15U) return;
    if (port->ODR & pin_mask(pin)) {
        port->BSRR = (pin_mask(pin) << 16U);
    } else {
        port->BSRR = pin_mask(pin);
    }
}

void gpio_write(gpio_t *port, uint8_t pin, gpio_state_t state) {
    if (state == GPIO_HIGH) {
        gpio_set(port, pin);
    } else {
        gpio_reset(port, pin);
    }
}

gpio_state_t gpio_read(gpio_t *port, uint8_t pin) {
    if (pin > 15U) return GPIO_LOW;
    return (port->IDR & pin_mask(pin)) ? GPIO_HIGH : GPIO_LOW;
}