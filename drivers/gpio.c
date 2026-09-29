#include "gpio.h"

//inline helper fucntion so yoou dont have to keeping masking the 32 bites to turn it on
static inline uint32_t pin_mask(uint8_t pin) {
    return (1U << pin);
}

void gpio_init(TypeDef_GPIO *port, uint8_t pin, gpio_mode_t mode){
    if (pin > 15U) return;
    port->MODER &= ~(0x3U << (pin * 2U));
    port->MODER |=  ((uint32_t)mode << (pin * 2U));
}

//use BSRR because its write only register whereas ODR is read modify store this isnt good in case interript fires at modify than somehting wrong gets stored
void gpio_set(TypeDef_GPIO *port, uint8_t pin){
    port->BSRR = pin_mask(pin); 
}

void gpio_reset(TypeDef_GPIO *port, uint8_t pin){
    port->BSRR = (pin_mask(pin) << 16U);
}

void gpio_toggle(TypeDef_GPIO *port, uint8_t pin){
    port->ODR ^= pin_mask(pin);
}

void gpio_write(TypeDef_GPIO *port, uint8_t pin, gpio_state_t state){
    if (state == GPIO_HIGH){
        gpio_set(port, pin);
    }else 
        gpio_reset(port, pin);
}

void gpio_set_af(TypeDef_GPIO *port, uint8_t pin, uint8_t af) {
    if (pin > 15U) return;
    port->AFR[pin / 8U] &= ~(0xFU << ((pin % 8U) * 4U));
    port->AFR[pin / 8U] |=  ((uint32_t)af << ((pin % 8U) * 4U));
}

gpio_state_t gpio_read(TypeDef_GPIO *port, uint8_t pin){
    return (port->IDR & pin_mask(pin)) ? GPIO_HIGH : GPIO_LOW;
}