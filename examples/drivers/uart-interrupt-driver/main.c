#include <stdint.h>
#include "uart.h"
#include "gpio.h"
#include "rcc.h"
#include "ringbuffer.h"
#include "nvic.h"

static TypeDef_RINGBUF rx;  // create an instance of struct. 

void USART2_IRQHandler(void){
    if (!usart_read_ready(USART2)) return;
    char c = usart_read_char_nb(USART2);
    rb_put(&rx, c);   //pass the memory address of buffer and char
}

int main(void){
    RCC->AHB1ENR |= (1U << 0);    /* GPIOA */
    RCC->APB1ENR |= (1U << 17);   /* USART2 */

    gpio_init(GPIOA, 2, GPIO_MODE_AF);
    gpio_set_af(GPIOA, 2, 7);
    gpio_init(GPIOA, 3, GPIO_MODE_AF);
    gpio_set_af(GPIOA, 3, 7);

    usart_init(USART2, BAUD_115200);
    nvic_enable(IRQ_USART2);

    while(1){
        char c;
        if (rb_get(&rx, &c)) {
            usart_write_char(USART2, c);
        }
    }
}