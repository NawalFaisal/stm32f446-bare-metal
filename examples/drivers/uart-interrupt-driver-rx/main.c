#include "gpio.h"
#include "nvic.h"
#include "rcc.h"
#include "ringbuffer.h"
#include "uart.h"


static ringbuf_t rx; //

void USART2_IRQHandler(void) {
    if (!usart_read_ready(USART2)) return;
    char c = usart_read_char_nb(USART2);
    rb_put(&rx, c); 
}

int main(void) {
    rcc_enable(RCC_GPIOA);
    rcc_enable(RCC_USART2);

    gpio_init(GPIOA, 2, GPIO_MODE_AF);
    gpio_set_af(GPIOA, 2, 7);
    gpio_init(GPIOA, 3, GPIO_MODE_AF);
    gpio_set_af(GPIOA, 3, 7);

    usart_init(USART2, BAUD_115200);
    usart_rx_interrupt_enable(USART2);
    nvic_enable(IRQ_USART2);

    while (1) {
        char c;
        if (rb_get(&rx, &c)) {
            usart_write_char(USART2, c);
        }
    }
}