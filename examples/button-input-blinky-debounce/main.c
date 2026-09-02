#include "gpio.h"

//goal use user button click on it and pa6 should turn on and off for each click
//the user button is connected to the I/O PC13
#define GPIOC ((TypeDef_GPIO *) 0x40020800)  
#define GPIOA ((TypeDef_GPIO *) 0x40020000)
#define RCC  ((TypeDef_RCC *) 0x40023800)


int main(void){
    RCC -> AHB1ENR |= (1<<0);  //GPIOA
    RCC -> AHB1ENR |= (1<<2);

    //clear bits 10 11 and set to output
    GPIOA -> MODER &= ~(3<<10);
    GPIOA -> MODER |= (1<<10);

     //clear bit 5 and set it to off intially
    GPIOA -> ODR &= ~(1<<5);

    //clear mode for safety
    //PC13 is at bits 2627 so shift left 3 to get 00
    GPIOC -> MODER &= ~(3<<26);

    //variable 
    int led_state = 0;
    int last_button_state = 0;

    while(1){
        
        int button_pressed = !(GPIOC -> IDR >>13) & 1;
          //toggle states
        if(button_pressed == 1 && last_button_state == 0){
            if(led_state == 0){
                led_state = 1;
            } else{
                led_state = 0;
            }
        }

        //update led based on its state
        if(button_pressed == 1 ){
            GPIOA -> ODR |= (1<<5);
        }   else{
            GPIOA -> ODR &= ~(1<<5);
        }
        // last_button_state = button_pressed;
        //debounce delay
        for (volatile int i = 0; i < 10000; i++);

    }



}

