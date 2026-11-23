#include "spi.h"

static inline void reg_clear(volatile uint32_t *reg, uint32_t mask) {
    *reg &= ~mask;
}

void spi_init(spi_t *spi, spi_mode_t mode, spi_baud_t baud, spi_role_t role) {
    reg_clear(&spi->CR1, 0xFFFFFFFFU); // known state, SPE off while we configure

    // mode lands straight on bits 1:0. bit 0 is CPHA, bit 1 is CPOL, and the
    // the enum value is the register value
    // masked so a bad argument cannot reach bit 2, which is MSTR
    spi->CR1 |= (mode & 3U);

    // BR is bits 5:3 and selects one of eight dividers
    spi->CR1 |= ((baud & 7U) << 3);

    if (role == SPI_MASTER) {
        spi->CR1 |= (1U << 2); // MSTR
        spi->CR1 |= (1U << 9); // SSM, take NSS from the SSI bit not the pin
        spi->CR1 |= (1U << 8); // SSI held high, so no other master is seen
    } else {
        // slave needs nothing set the reg clear fucntion has it all set to slave untill callee deicded otherwise
    }

    spi->CR1 |= (1U << 6); // SPE last, once everything else is set
}

uint8_t spi_transfer(spi_t *spi, uint8_t out) {
    while (!(spi->SR & (1U << 1))) {} // TXE, tx buffer free
    spi->DR = out;
    while (!(spi->SR & (1U << 0))) {} // RXNE, a byte came back
    return spi->DR;
}

void spi_wait_idle(spi_t *spi) {
    while (spi->SR & (1U << 7)) {} // BSY
}