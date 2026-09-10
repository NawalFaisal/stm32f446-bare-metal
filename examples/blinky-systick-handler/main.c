#include <stdint.h>
#include "systick.h"

#define RCC_AHB1ENR  (*(volatile uint32_t *)0x40023830)
#define GPIOA_MODER  (*(volatile uint32_t *)0x40020000)
#define GPIOA_ODR    (*(volatile uint32_t *)0x40020014)


int main(void) {
    RCC_AHB1ENR |= (1U << 0);        
    
    GPIOA_MODER &= ~(3U << 10);      
    GPIOA_MODER |=  (1U << 10);

    systick_init();  //call this fucntion to configure my regsiter and enable them, clear the current value in there and relaod it with th amount of ticks taht must happen beofre interrupt fires to syst_handler i have 10000ms as of right now
    while (1) {
    GPIOA_ODR |= (1U << 5);  
    delay_ms(500); 
    GPIOA_ODR &= ~(1U << 5);
    delay_ms(500);   
}
}

// The function parameters get stored in R0 register due to ab1 rules. the mov instruction is booking. im assuming all arguments go into the first couple of regsiters 
// str r3, [r2, #0]      ; write ODR — LED on
// mov.w r0,#500        ; set up the argument
// bl <delay_ms>         ; wait
// bic.w r3, r3, #32     ; clear the bit
// str r3, [r2, #0]      ; write ODR — LED off
// mov.w r0,#500
// bl <delay_ms>         ; wait again