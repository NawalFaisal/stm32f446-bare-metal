#include "gpio.h"


int main(void){

    RCC ->AHB1ENR |= (1<< 0); 
    GPIOA -> MODER &= ~(3<<10);
    GPIOA -> MODER |= (1<<10);

    while(1){
        set_led(GPIOA,5);
        for(volatile int i = 0; i < 1000000; i++);
        reset_led(GPIOA,5);
        for(volatile int i = 0; i < 1000000; i++);
    }

}


