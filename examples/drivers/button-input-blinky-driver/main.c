#include "gpio.h"
#include "rcc.h"

int main(void) {
    RCC->AHB1ENR |= (1U << 0);   // GPIOA clock
    RCC->AHB1ENR |= (1U << 2);   // GPIOC clock

    gpio_init(GPIOA, 5,  GPIO_MODE_OUTPUT);
    gpio_init(GPIOC, 13, GPIO_MODE_INPUT);

    while (1) {
        // PC13 on the Nucleo is wired to the user button, active low.
        // GPIO_LOW means the button is pressed.
        if (gpio_read(GPIOC, 13) == GPIO_LOW) {
            gpio_set(GPIOA, 5);
        } else {
            gpio_reset(GPIOA, 5);
        }
    }
}