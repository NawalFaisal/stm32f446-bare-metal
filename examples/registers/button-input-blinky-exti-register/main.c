/* Goals:
   configure the led and the button but now when the button is pressed you use the interrupt
   instead of writing the manual code for pressed = 0 and unpressed = 1
*/

#include "gpio.h"
#include "rcc.h"
#include "syscfg.h"
#include "exti.h"
#include "nvic.h"

// Led is PA5
// the user button is connected to the I/O PC13
void EXTI15_10_IRQHandler(void) {
        EXTI -> EXTI_PR |= (1<<13);
        GPIOA -> ODR  ^= (1<<5);

}
int main(void){
    RCC -> AHB1ENR |= (1<<0);  
    RCC -> AHB1ENR |= (1<<2);
    RCC -> APB2ENR |= (1<<14);
    // EXTI itself has no clock enable — it sits between the pins and NVIC and is always on.
    // SYSCFG does need one though, and that's what bit 14 of APB2ENR is.

  
    GPIOA -> MODER &= ~(3<<10);
    GPIOA -> MODER |= (1<<10);

    GPIOA -> ODR &= ~(1<<5);
    GPIOC -> MODER &= ~(3<<26);


    // bits 4,5,6,7 select the port for EXTI line 13. port C is 0010 = 2.
    // shift that 2 up by 4 to land it in the right field.
    SYSCFG -> SYSCFG_EXTICR4 |= (2<<4);
    
    // unmask line 13 so it can actually reach NVIC
    EXTI -> EXTI_IMR |=(1<<13);


    // falling edge: button has a pull-up so idle is 3.3V and pressing drags it to 0V.
    // rising would be the release instead.
    EXTI -> EXTI_FTSR |=(1<<13);

    // vector table slot 56 holds EXTI15_10_IRQHandler, which is IRQ 40.
    // ISER[1] covers IRQs 32-63, so bit = 40 - 32 = 8.
    NVIC -> ISER[1] |= (1<<8);  

  /*Falling edge detected → EXTI raises IRQ 40 → NVIC lets it through 
  → CPU jumps to your handler → handler clears the flag and XORs the LED bit → returns to main.*/
    while(1){
        
    }

}


// main sets all the configurations, then sits in while(1) doing nothing.
//
// when I press the button:
//   PC13 falls 3.3V -> 0V
//   EXTI sees the falling edge, sets PR bit 13, raises IRQ 40
//   NVIC checks ISER[1] bit 8 -- enabled, so it interrupts the CPU
//   HARDWARE pushes r0-r3, r12, lr, pc, xPSR onto the stack (32 bytes, automatic)
//   CPU reads vector slot 56, jumps to my handler
//   my handler runs: clear PR, toggle the LED bit
//   bx lr with lr = 0xfffffff9 -> hardware unstacks and returns to main
//
// the push {r7} / add r7, sp, #0 at the top of my handler is just the normal
// C function prologue, same as any function. the real state save already
// happened before that instruction ran.
//
// main never knew anything happened. it's still spinning in the same b.n.