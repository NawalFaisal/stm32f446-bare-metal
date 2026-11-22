#ifndef SYS_H
#define SYS_H
#include <stdint.h>

typedef struct {
    volatile uint32_t MEMRMP;      // 0x00
    volatile uint32_t PMC;         // 0x04
    volatile uint32_t EXTICR[4];   // 0x08 - 0x14, pins 0-3, 4-7, 8-11, 12-15
    volatile uint32_t RESERVED[2]; // 0x18 - 0x1C
    volatile uint32_t CMPCR;       // 0x20
} sys_t;

typedef enum {
    PORTA = 0,
    PORTB = 1,
    PORTC = 2,
    PORTD = 3,
    PORTE = 4,
    PORTH = 7,
} exti_port_t;

#define SYSCFG ((sys_t *)0x40013800)

void select_exti_port(sys_t *sys, uint8_t pin, exti_port_t port);

#endif // SYS_H


/*SYSCFG is a peripheal its a piece of hardware on our micornctroller but unlike
others it deals with internal wirining of memory
1. syscfr_mem  tell the cpu where to boot from at 0000
2.syscfr_pmc periheal mode configuration  not important to me
//four external registers
you write the port you want to be wired into its correct pin number
ex.
3. syscfr_exticr1   EXTI0-3  deals with pin numbers 0-3
4. syscrf_exticr2   EXTI4-7  deals with pin numbers 4-7
5.syscrf_exticr3    EXTI8-11 deals with pin numbers 8-11
6.syscrf_exticr4    EXTI12-15 deals with pin numbers 12-15
//however the port of that pin is undecided how does it know if i want pc13 or
pa13
//it doesnt hence why you must write the port number into the exti configuration
//port a = 0000
//port b == 0001
//port c = 0010 etc etc
7. syscfg_cfg configuration regsiter
8. syscfg_ccr some cell map controll not important to me
*/