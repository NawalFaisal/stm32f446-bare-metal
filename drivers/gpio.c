#include "gpio.h"


//function to set the led 
void set_led(void) {
    GPIOA->ODR |= (1<<5);

}

//function to reset the led
void reset_led(void){
    GPIOA->ODR &= ~(1<<5);

}