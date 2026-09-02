#include "gpio.h"


int main(void){

    RCC ->AHB1ENR |= (1<< 0); 
    GPIOA -> MODER |= (1<<10);
    GPIOA -> ODR |= (1<<5);

    while(1){
        set_led();
        for(volatile int i = 0; i < 1000000; i++);
        reset_led();
        for(volatile int i = 0; i < 1000000; i++);
    }

}


