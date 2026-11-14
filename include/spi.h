#ifndef SPI_H
#define SPI_H
#include <stdint.h>

typedef struct{
    volatile uint32_t CR1; //SPI mode, data format, clock settings,
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
}TypeDef_SPI;


/*Mode 0 — CPOL=0, CPHA=0. Idles low, samples on rising. Most common by far.
Mode 1 — CPOL=0, CPHA=1. Idles low, samples on falling.
Mode 2 — CPOL=1, CPHA=0. Idles high, samples on falling.
Mode 3 — CPOL=1, CPHA=1. Idles high, samples on rising. Second most common. */
typedef enum {
    SPI_MODE_0 = 0,   /* CPOL=0, CPHA=0 */
    SPI_MODE_1 = 1,   /* CPOL=0, CPHA=1 */
    SPI_MODE_2 = 2,   /* CPOL=1, CPHA=0 */
    SPI_MODE_3 = 3,   /* CPOL=1, CPHA=1 */
} spi_mode_t;

typedef enum {
    SPI_BAUD_DIV2   = 0,
    SPI_BAUD_DIV4   = 1,
    SPI_BAUD_DIV8   = 2,
    SPI_BAUD_DIV16  = 3,
    SPI_BAUD_DIV32  = 4,
    SPI_BAUD_DIV64  = 5,
    SPI_BAUD_DIV128 = 6,
    SPI_BAUD_DIV256 = 7,
} spi_baud_t;


#define SPI1 ((TypeDef_SPI *)0x40013000)
#define SPI2 ((TypeDef_SPI *)0x40003800)
#define SPI3 ((TypeDef_SPI *)0x40003C00)

#endif // SPI_H