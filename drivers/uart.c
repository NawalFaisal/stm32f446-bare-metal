#include "uart.h"
#include <stdint.h>
#define SYSTEM_CLOCK_HZ 16000000

void usart_init(usart_t *usart, baud_rate_t baud) {
    uint32_t divisor = (SYSTEM_CLOCK_HZ + (baud / 2)) / baud;
    usart->BRR = divisor;

    usart->CR1 |= (1U << 2);  /* RE */
    usart->CR1 |= (1U << 3);  /* TE */
    usart->CR1 |= (1U << 13); /* UE */
}


int usart_read_ready(usart_t *usart) {
    return usart->SR & (1U << 5); /* RXNE */
}

// busy waiting. wait to read letter.
char usart_read_char(usart_t *usart) {
    while (!(usart->SR & (1U << 5))) {
    }
    return usart->DR;
}

// ISR needs to get the info without being stuck in loop
char usart_read_char_nb(usart_t *usart) {
    return usart->DR;
}

void usart_rx_interrupt_enable(usart_t *usart) {
    usart->CR1 |= (1U << 5); /* RXNEIE */
}

void usart_rx_interrupt_disable(usart_t *usart) {
    usart->CR1 &= ~(1U << 5);
}

// busy waiting. wait for letter to be written
void usart_write_char(usart_t *usart, char c) {
    while (!(usart->SR & (1U << 7))) {
    } /*wait for TXE*/
    usart->DR = c;
}

int usart_write_ready(usart_t *usart) {
    return usart->SR & (1U << 7); /* TXE */
}

void usart_write_char_nb(usart_t *usart, char c) {
    usart->DR = c;
}

void usart_tx_interrupt_enable(usart_t *usart) {
    usart->CR1 |= (1U << 7); /* TXEIE */
}

void usart_tx_interrupt_disable(usart_t *usart) {
    usart->CR1 &= ~(1U << 7);
}