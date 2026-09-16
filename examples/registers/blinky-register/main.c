#include "gpio.h"
#include "rcc.h"

//goal: blinky on PA5, raw registers only

int main(void){
    RCC -> AHB1ENR |= (1<<0);  //GPIOA

    //clear bits 10 11 and set to output
    GPIOA -> MODER &= ~(3<<10);
    GPIOA -> MODER |= (1<<10);

    while(1){
        GPIOA -> ODR |= (1<<5);     //on
        for (volatile int i = 0; i < 1000000; i++);
        GPIOA -> ODR &= ~(1<<5);    //off
        for (volatile int i = 0; i < 1000000; i++);
    }
}