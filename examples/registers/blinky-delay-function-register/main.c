#include <stdint.h>
#include "delay.h"
#include "rcc.h"
#include "gpio.h"

// volatile = don't be clever with this one.
// the compiler thinks it knows everything happening to memory, so it deletes
// writes nobody reads, merges repeated reads, and moves things around.
// that's fine for normal variables. it's wrong for hardware, because writing
// to ODR turns on an LED and the compiler can't see that.
// i watched it happen at -O2: it read MODER before turning the clock on.

int main(void) {
    RCC -> AHB1ENR |= (1U << 0);        
    GPIOA -> MODER &= ~(3U << 10);      
    GPIOA -> MODER |=  (1U << 10);

    while (1) {
        GPIOA -> ODR |= (1U << 5);  
        delay(); 
        GPIOA -> ODR &= ~(1U << 5);
        delay();   
    }
}