#include "gpio.h"
#include "rcc.h"

int main(void) {
    RCC->AHB1ENR |= (1U << 0);                  // GPIOA clock
    gpio_init(GPIOA, 5, GPIO_MODE_OUTPUT);      // PA5 as output

    while (1) {
        gpio_set(GPIOA, 5);
        for (volatile int i = 0; i < 1000000; i++);
        gpio_reset(GPIOA, 5);
        for (volatile int i = 0; i < 1000000; i++);
    }
}

