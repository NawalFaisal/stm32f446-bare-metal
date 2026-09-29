#include "uart.h"
#include <stdint.h>
#include "gpio.h"
#define SYSTEM_CLOCK_HZ 16000000


void usart_init(TypeDef_USART *usart, baud_rate_t baud){
    uint32_t divisor = (SYSTEM_CLOCK_HZ + (baud / 2)) / baud;
    usart->BRR = divisor;

    usart->CR1 |= (1U << 2);    /* RE */
    usart->CR1 |= (1U << 3);    /* TE */
    usart->CR1 |= (1U << 5);    /* RXNEIE */
    usart->CR1 |= (1U << 13);   /* UE */
    
}

//polled + blocking. 
void usart_write_char(TypeDef_USART *usart, char c){
    while(!(usart -> SR & (1U << 7))){ }  /*wait for TXE*/
    usart -> DR = c; 
}

char usart_read_char(TypeDef_USART *usart){
    while(!(usart -> SR & (1U << 5))) {}
    return usart -> DR; 
    

}

//ISR needs to get the info without being stuck in loop
char usart_read_char_nb(TypeDef_USART *usart){
    return usart -> DR; 
}

int usart_read_ready(TypeDef_USART *usart){
    return (usart->SR & (1U << 5)) != 0;
}
