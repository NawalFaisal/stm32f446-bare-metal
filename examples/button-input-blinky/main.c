#include "gpio.h"

int main(void){
    RCC->AHB1ENR |= (1<<0);
    RCC->AHB1ENR |= (1<<2);


    GPIOA->MODER &= ~(3<<10);
    GPIOA->MODER |= (1<<10);
    GPIOC->MODER &=  ~(3<<26);
    
    while(1){
        if (set_button(GPIOC,13) == 1) {
            set_led(GPIOA, 5 );
        } else{
            reset_led(GPIOA, 5);
        }  
    }
}