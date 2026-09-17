#include "uart.h"
#include "stdint.h"
#define SYSTEM_CLOCK_HZ 16000000


void usart_init(TypeDef_USART *usart, baud_rate_t baud){
    uint8_t divisor = SYSTEM_CLOCK_HZ / baud;
    usart -> BRR = divisor;  

    usart->CR1 |= (1U << 2);    /* RE */
    usart->CR1 |= (1U << 3);    /* TE */
    usart->CR1 |= (1U << 13);   /* UE */
    
}

void usart_write_char(TypeDef_USART *usart, char c){
    while(!(usart -> SR & (1U << 7))){ }  /*wait for TXE*/
        usart -> DR = c; 
}

void usart_read_char(TypeDef_USART *usart){
    while(!(usart -> SR & (1U << 5))) {}
    return usart -> DR; 

}