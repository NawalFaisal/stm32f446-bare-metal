#include "gpio.h"



//user button is connected to pc13
//port c pin 13
// 0x4002 0800 - 0x4002 0BFF GPIOC
//moder to turn on and off for the pin 
//user led is pa5

//use define to get the memory space and acst the memory space gpio a to it 
#define GPIOC ((TypeDef_GPIO *) 0x40020800)
#define GPIOA ((TypeDef_GPIO *) 0x40020000)  //only need the start
//gpio stuct is pointer to that memory space and we are naming that struct gpioA
//every bus has a clock
//the bus is AHB1 and its clock is is on memory space 0x4002 3800 - 0x4002 3BFF
#define RCC ((TypeDef_RCC *) 0x40023800)
int main(void){

    //first you need the clock to enable the bus 
    //shift left to the second operand and turn it on using 1 as the first operand
    //turn on gpioA
    RCC->AHB1ENR |= (1<<0);
    //turn on gpioC
    RCC->AHB1ENR |= (1<<2);


    //go into struct gpio and access struct member moder
    //moder 5 which is pin 5 is 10 and 11 bits
    GPIOA->MODER &= ~(3<<10);
     GPIOA->MODER |= (1<<10);
    //bits 26 and 27 both need to be reset
    GPIOC->MODER &=  ~(3<<26);


    //while the pc13 button is pressed keep the light on 
    //need somehting to hold the button pressed
    //if teh button is pressed variable needs to hold yes the user is pressing it so it needs to be 1 and 0 if user isnt pressing it 
    //so 1 should be set and 0 should be clearing
    while(1){
        if((GPIOC->IDR & (1<<13)) == 0){
            GPIOA->ODR |= (1<<5);
        } else{
            GPIOA->ODR &= ~(1<<5);
        }
      

        
        
    }

    

    return 0;
}