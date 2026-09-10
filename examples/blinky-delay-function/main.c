#include <stdint.h>
#include "delay.h"

// volatile = don't be clever with this one.
// the compiler thinks it knows everything happening to memory, so it deletes
// writes nobody reads, merges repeated reads, and moves things around.
// that's fine for normal variables. it's wrong for hardware, because writing
// to ODR turns on an LED and the compiler can't see that.
// i watched it happen at -O2: it read MODER before turning the clock on.
#define RCC_AHB1ENR  (*(volatile uint32_t *)0x40023830)
#define GPIOA_MODER  (*(volatile uint32_t *)0x40020000)
#define GPIOA_ODR    (*(volatile uint32_t *)0x40020014)

// Current counter violates DRY DO NOT REPEAT YOURSELF"
//use delay function

int main(void) {
    RCC_AHB1ENR |= (1U << 0);        
    GPIOA_MODER &= ~(3U << 10);      
    GPIOA_MODER |=  (1U << 10);

    while (1) {
        GPIOA_ODR |= (1U << 5);  
        delay(); 
        GPIOA_ODR &= ~(1U << 5);
        delay();   
    }
}