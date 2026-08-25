#include "gpio.h"


#define RCC   ((TypeDef_RCC *)0x40023800)
#define GPIOA ((TypeDef_GPIO *)0x40020000)

int main(void){

    RCC ->AHB1ENR |= (1<< 0); 
    GPIOA -> MODER |= (1<<10);
    GPIOA -> ODR |= (1<<5);

    while(1){
        GPIOA -> ODR ^= (1<<5);
        for(volatile int i = 0; i < 1000000; i++);
    }

}


