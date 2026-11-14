#include "spi.h"
#include "rcc.h"
#include "gpio.h"
#include <stdint.h>
 
// spi sends and recives 
//param = what i give it 
//the front int is what it returns
//The mental model: write, then read. SPI is full duplex, so sending eight bits also clocks eight bits back in. 
//You can't receive without sending — that's why reading from a device means sending a dummy byte.
uint8_t spi_transfer(uint8_t out){
    while (!(SPI1->SR & (1U << 1))) { }   /* TXE — room to write */
    SPI1->DR = out;                        /* send the byte */
    while (!(SPI1->SR & (1U << 0))) { }   /* RXNE — a byte came back */
    return SPI1->DR;                       /* take it */
}
int main(void){
    //config
    RCC -> AHB1ENR |= (1U << 0 );  //enable clock for gpioa perpheal
    RCC -> APB2ENR |= (1U << 12);  //enable clock for spi peripea

    // need to set three gpios to alternate 
    //dealut pins for spi PA5 — SCK PA6 — MISO PA7 — MOSI
    GPIOA -> MODER |= (2U << 5*2);  //2 is 10 in binary 
    GPIOA -> MODER |= (2U << 6*2);
    GPIOA -> MODER |= (2U << 7*2);

    //set pins to be controled by alter function spi
    GPIOA->AFR[0] |= (5U << (5*4));
    GPIOA->AFR[0] |= (5U << (6*4));
    GPIOA->AFR[0] |= (5U << (7*4));


    //master configuration. zero if its slave 1 if its master
    //CPOL is just what voltage the clock line sits at when nothing is happening. 0 means it rests low. 1 means it rests high. That's all. No effect on data, only on the idle level.
    //cpha it's first edge or second edge. Which one is rising depends on CPOL. With CPOL=0, the first edge is rising. With CPOL=1, the first edge is falling. That's why there are four modes rather than two.
    //mode to only revieve only if set to 0 than its full duplex master can give and recive from slave. 1 only master recievd 
    //each device gets its own private wire, called chip select or slave select. The master pulls one device's CS low, and that device wakes up and listens. Every other device sees its own CS still high and ignores the bus entirely.
    //NSS is the physical chip-select pin. SSM=1 says "ignore that pin, use the SSI bit instead." SSI=1 then says "pretend NSS is high," which means no other master owns this bus.

    SPI1->CR1 |= (3U << 3);   /* baud prescaler, div16 */
    SPI1->CR1 |= (1U << 2);   /* MSTR — master */
    SPI1->CR1 |= (1U << 9);   /* SSM — software slave management */
    SPI1->CR1 |= (1U << 8);   /* SSI — pretend NSS is high */
    SPI1->CR1 |= (1U << 6);   /* SPE — enable, last */

    while(1){
    uint8_t got = spi_transfer(0xA5);
    }





}

