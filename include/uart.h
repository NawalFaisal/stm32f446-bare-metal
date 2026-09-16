#ifndef UART_H
#define UART_H
#include <stdint.h>


typedef struct {
    volatile uint32_t SR;    // offset 0x00
    volatile uint32_t DR;    // offset 0x04
    volatile uint32_t BRR;   // offset 0x08  //sets baude rate the speed the two communciate at
    volatile uint32_t CR1;   // offset 0x0C   //configures if its transmitting or reciveing
} TypeDef_USART;

#define USART2 ((TypeDef_USART *)0x40004400)

#endif //UART_H