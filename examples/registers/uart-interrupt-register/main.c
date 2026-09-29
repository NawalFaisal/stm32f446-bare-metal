#include "uart.h"
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"
#include <stdint.h>

#define RX_SIZE 64

static volatile char rx_buf[RX_SIZE];  //static keywork: can only be used in this .c file need it to be global because two func below need it but i dont want outsiders to extern it
static volatile uint8_t head = 0;  //these are just array indexes
static volatile uint8_t tail = 0;  


/*The ring buffer is an array im designing that takes up my own ram space 
Why it exists: DR holds exactly one byte. The next byte overwrites it. 
I need somewhere to stash bytes until main is ready, so I allocated ana array.
*/

void uart_write_char(char c) {
    while (!(USART2->SR & (1U << 7))) { }   /* TXE */
    USART2->DR = (uint32_t)(c & 0xFF);
}

//interrupt handler function
void USART2_IRQHandler(void){
    if(!(USART2 -> SR & (1U << 5))) return;   //read the status register to see if data is ready to be read
    char c = USART2 -> DR; 
    uint8_t next = (head + 1) % RX_SIZE;  // next is only unique to this handler and than discarded dont make it global and its only touched by handler so i dont need it to be volatile
    if(next != tail){
        rx_buf[head] = c; //whatever is in data registe right it into the head of  buffer [DR is read one byte at a time]
        head = next; 
    }
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

    /* both the interrupt and Direction bits have to be 1 for interrupt to fire , then UE last */  
    USART2->CR1 |= (1U << 2);    /* RE — receiver */
    USART2->CR1 |= (1U << 3);    /* TE — transmitter */
    USART2 ->CR1 |= (1U << 5 );  //RX interrupt 
    // USART2 ->CR1 |= (1U << 7); //TX interrupt
    USART2->CR1 |= (1U << 13);   /* UE — USART enable last when everything is configured */ 
    

    //nvic calculate for usart2 interrupt at address 38 on index table 38 / 32 = 1 && 38 % 32 = 6  
    NVIC -> ISER[1] |= (1U << 6);  // when this interrupt is raised let it through the interrupt 

    //drain the buffer in main
    uart_write_char('R');
    for(;;){
        if (tail != head) {          /* is there anything? if tail==head it means its empty so exit loop */
            char c = rx_buf[tail];   /* read it */
            tail = (tail + 1) % RX_SIZE;
            uart_write_char(c);
        }
    }
}

/*
<main+198>  ldr r3, [pc, #84]    ┐
<main+200>  ldrb r3, [r3, #0]    │  load tail
<main+202>  uxtb r2, r3          │
<main+204>  ldr r3, [pc, #80]    │  load head
<main+206>  ldrb r3, [r3, #0]    │
<main+208>  uxtb r3, r3          │
<main+210>  cmp r2, r3           │  equal?
<main+212>  beq.n <main+198>     ┘  yes → jump back to +198

<main+210>  cmp r2, r3            tail vs head — not equal
<main+212>  beq.n <main+198>      ← condition false, no jump, fall through

char c = rx_buf[tail]; 
<main+214>  ldr r3, [pc, #68]     get tail's address
<main+216>  ldrb r3, [r3, #0]     load tail
<main+218>  uxtb r3, r3
<main+220>  mov r2, r3            tail → r2 (the index)
<main+222>  ldr r3, [pc, #68]     get rx_buf's base address
<main+224>  ldrb r3, [r3, r2]     ← rx_buf[tail]: base + index, load byte
<main+226>  strb r3, [r7, #7]     store into local c

tail = (tail + 1) % RX_SIZE; 
<main+228>  ldr r3, [pc, #52]
<main+230>  ldrb r3, [r3, #0]     load tail
<main+232>  uxtb r3, r3
<main+234>  adds r3, #1           tail + 1
<main+236>  negs r2, r3           ┐
<main+238>  and.w r3, r3, #63     │ the % 64
<main+240>  and.w r2, r2, #63     │
<main+242>  it pl                 │
<main+244>  negpl r3, r2          ┘
...
uart_write_char(c) 
 ldrb r0, [r7, #7]     load c into r0 (the argument)
 bl <uart_write_char>


 constant offset vs variable offset 
 ldr  r3, [r7, #4]      offset is a fixed number, baked into the instruction
ldrb r3, [r3, r2]      offset comes from a register, decided at runtime
1 byte loading 
ldrb r3, [r3, #0]      load one BYTE
strb r3, [r7, #7]      store one BYTE
widening
uxtb r2, r3            unsigned extend byte: low 8 bits, zero the top 24

*/