
#include "gpio.h"
#include "rcc.h"

//goal:Alternate two blinkys

int main(void) {
    RCC->AHB1ENR |= (1 << 0);
    GPIOA->MODER &= ~(3 << 10);
    GPIOA->MODER |= (1 << 10);
    GPIOA->ODR |= (1 << 5);      //start high
    
    // clear + configure
    GPIOA->MODER &= ~(3 << 12);
    GPIOA->MODER |= (1 << 12);
    GPIOA->ODR &= ~(1 << 6);       //start low
    
    while(1) {
        GPIOA->ODR ^= (1 << 5);
        GPIOA->ODR ^= (1 << 6);
        for(volatile int i = 0; i < 100000; i++);
    }
}