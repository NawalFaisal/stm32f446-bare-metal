#include <stdint.h>
#include "gpio.h"
#include "rcc.h"
#include "uart.h"

char uart_read_char(void) {
    while (!(USART2->SR & (1U << 5))) { }   /* RXNE */
    return (char)(USART2->DR & 0xFF);
}

void uart_write_char(char c) {
    while (!(USART2->SR & (1U << 7))) { }   /* TXE */
    USART2->DR = (uint32_t)(c & 0xFF);
}

int main(void) {
    /* Clocks */
    RCC->AHB1ENR |= (1U << 0);    /* GPIOA */
    RCC->APB1ENR |= (1U << 17);   /* USART2 */

    /* PA2 = TX, alternate function AF7 */
    GPIOA->MODER &= ~(3U << (2*2));
    GPIOA->MODER |=  (2U << (2*2));
    GPIOA->AFR[0] &= ~(0xFU << (2*4));
    GPIOA->AFR[0] |=  (0x7U << (2*4));

    /* PA3 = RX, alternate function AF7 */
    GPIOA->MODER &= ~(3U << (3*2));
    GPIOA->MODER |=  (2U << (3*2));
    GPIOA->AFR[0] &= ~(0xFU << (3*4));
    GPIOA->AFR[0] |=  (0x7U << (3*4));

    /* Baud rate */
    USART2->BRR = (8U << 4) | 11U;   /* 115200 @ 16 MHz */

    /* Direction bits, then UE last */
    USART2->CR1 |= (1U << 2);    /* RE — receiver enable */
    USART2->CR1 |= (1U << 3);    /* TE — transmitter enable */
    USART2->CR1 |= (1U << 13);   /* UE — USART enable */

    for (;;) {
        uart_write_char(uart_read_char());
    }
}