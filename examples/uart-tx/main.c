#include <stdint.h>
#include "gpio.h"
#include "uart.h"


#define GPIOA  ((TypeDef_GPIO *)0x40020000)
#define RCC    ((TypeDef_RCC *)0x40023800)
#define USART2 ((TypeDef_USART *)0x40004400)

void uart_write_char(char c) {
    while (!(USART2 -> SR & (1<<7))) {
        // wait
    }
    USART2 -> DR = c;
}

int main(void) {
    // 1. Enable GPIOA clock (AHB1)
    RCC->AHB1ENR |= (1 << 0);

    // 2. Enable USART2 clock (APB1, bit 17)
    RCC->APB1ENR |= (1 << 17);

    // 3. PA5 as output (onboard LED, for testing)
    GPIOA->MODER &= ~(3 << 10);
    GPIOA->MODER |=  (1 << 10);
    GPIOA->ODR   |=  (1 << 5);

    // 4. PA2 as alternate function (USART2 TX)
    GPIOA->MODER &= ~(3 << 4);
    GPIOA->MODER |=  (2 << 4);

    // 5. PA2 alternate function = AF7 (USART2), AFRL controls pins 0-7
    GPIOA->AFR[0] &= ~(0xF << 8);   // clear bits 11:8 (pin 2's AF field)
    GPIOA->AFR[0] |=  (7 << 8);     // set AF7

    // 6. Baud rate = 115200 at 16MHz clock

    // USART2->BRR = (8 << 4) | 11;
    //9600
    // USART2->BRR = (104 << 4) | 3;
    //19200
    USART2->BRR = (52 << 4) | 1;

    // 7. Enable transmitter (bit 3) and USART (bit 13)
    USART2->CR1 |= (1 << 3);
    USART2->CR1 |= (1 << 13);

   while (1) {
    uart_write_char('O');
    for (volatile int i = 0; i < 1000000; i++);  // delay so terminal can keep up
}
}