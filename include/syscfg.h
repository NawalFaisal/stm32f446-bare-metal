#ifndef SYSCFG_H
#define SYSCFG_H
#include <stdint.h>

typedef struct {
    uint32_t volatile SYSCFG_MEMRMP;
    uint32_t volatile SYSCFG_PMC;
    uint32_t volatile SYSCFG_EXTICR1;  //pins 0-3
    uint32_t volatile SYSCFG_EXTICR2;  //pins 4-7
    uint32_t volatile SYSCFG_EXTICR3;  //pins 8-11
    uint32_t volatile SYSCFG_EXTICR4;  //pins 12-15
    uint32_t volatile SYSCFG_CMPCR;
    uint32_t volatile SYSCFG_CFGR;
} TypeDef_SYSCFG;

//0x4001 3800 - 0x4001 3BFF

#define SYSCFG ((TypeDef_SYSCFG *)0x40013800)

#endif //SYSCFG_H


    /*SYSCFG is a peripheal its a piece of hardware on our micornctroller but unlike others it deals with internal wirining of memory 
    1. syscfr_mem  tell the cpu where to boot from at 0000
    2.syscfr_pmc periheal mode configuration  not important to me 
    //four external registers
    you write the port you want to be wired into its correct pin number
    ex. 
    3. syscfr_exticr1   EXTI0-3  deals with pin numbers 0-3
    4. syscrf_exticr2   EXTI4-7  deals with pin numbers 4-7
    5.syscrf_exticr3    EXTI8-11 deals with pin numbers 8-11
    6.syscrf_exticr4    EXTI12-15 deals with pin numbers 12-15
    //however the port of that pin is undecided how does it know if i want pc13 or pa13 
    //it doesnt hence why you must write the port number into the exti configuration
    //port a = 0000
    //port b == 0001
    //port c = 0010 etc etc 
    7. syscfg_cfg configuration regsiter
    8. syscfg_ccr some cell map controll not important to me 
    */