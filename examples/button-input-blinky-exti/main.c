/*Goals: 
cofnigure the led and the button but now when the button is pressed you use the interrutp 
instead of writing the manual code for pressed = 0 and unpressed = 1
*/



#include "gpio.h"
#include "rcc.h"
#include "syscfg.h"
#include "exti.h"
#include "nvic.h"

//Led is PA5
//the user button is connected to the I/O PC13

int main(void){
    RCC -> AHB1ENR |= (1<<0);  
    RCC -> AHB1ENR |= (1<<2);
    RCC -> APB2ENR |= (1<<14);
    //even though my exti is on apb2 bus i dont seem to have to enable the clock is not  aperiohreal?

  
    GPIOA -> MODER &= ~(3<<10);
    GPIOA -> MODER |= (1<<10);

    GPIOA -> ODR &= ~(1<<5);
    GPIOC -> MODER &= ~(3<<26);


    // bits 4,5,6,7 need to be configured to 0010 for port c which is 0010
    // 2 is 0010 in binary and 0x2 in hex i can shift that in their
    SYSCFG -> SYSCFG_EXTICR4 |= (2<<4); // start at 4 and shift 0010 into it 
    
    //exti mask mask pin13 on port c that was set by the syyscfg
    EXTI -> EXTI_IMR |=(1<<13);


    //whats the difference between a falling edge vs a rising edge 
    //using falling because your button is being pressed and going from 3.3v to 0 v 
    EXTI -> EXTI_FTSR |=(1<<13);

  



 



    while(1){
        
    }



}

