#include "gpio.h"



//function to set the led 
void set_led(TypeDef_GPIO *port , uint8_t pin ) {
    port->ODR |= (1<<pin);

}

//function to reset the led
void reset_led( TypeDef_GPIO *port, uint8_t pin ){
    port->ODR &= ~(1<<pin);

}


// set button input
uint8_t set_button(TypeDef_GPIO *port, uint8_t pin) {
    if ((port -> IDR & (1<<pin))) {
        return 1; 
    } else {
        return 0 ; 
    }
    
}



