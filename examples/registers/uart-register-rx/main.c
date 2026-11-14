#include <stdint.h>
#include "gpio.h"
#include "rcc.h"
#include "uart.h"


char read_DR() {
    while (!(USART2->SR & (1U << 5))) {
    }
    return (char)USART2->DR; // the tyue f usart -> dr is int so im typecatsing to a char
}

void write_DR(char c) {
    while (!(USART2->SR & (1U << 7))) {
    }
    USART2->DR = (uint32_t)(c & 0xFF);
}

int main(void) {
    // configs
    // clocks
    RCC->AHB1ENR |= (1 << 0);  // enable gpioa
    RCC->APB1ENR |= (1 << 17); // enable usart2

    // let pa2 and pa3 pins be set to altnertave so it can be controlled by usart2

    GPIOA->MODER &= ~(3 << 4);   // clear pa2
    GPIOA->MODER |= (2 << 4);    // set pa2 mode to on
    GPIOA->AFR[0] &= ~(15 << 8); // clear
    GPIOA->AFR[0] |= (7 << 8);   // set

    GPIOA->MODER &= ~(3 << 6);
    GPIOA->MODER |= (2 << 6);


    GPIOA->AFR[0] &= ~(15 << 12);
    GPIOA->AFR[0] |= (7 << 12);

    USART2->BRR = (8U << 4) | 11U; /* 115200 @ 16 MHz */

    USART2->CR1 |= (1U << 2);
    USART2->CR1 |= (1U << 3);
    USART2->CR1 |= (1U << 13);

    while (1) {
        write_DR(read_DR());
    }
}
