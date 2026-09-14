#ifndef EXTI_H
#define EXTI_H
#include <stdint.h>

typedef struct {
    uint32_t volatile EXTI_IMR; //mask register 0-22 rw bits each corrresponding to each interrupt 23 line.  0 = masked 1 = unmasked
    uint32_t volatile EXTI_EMR; //event mask register
    uint32_t volatile EXTI_RTSR; //rising trigger sellection register 0 disabled for event&interrupt 1 = enabled 
    uint32_t volatile EXTI_FTSR; //falling trigger selection register
    uint32_t volatile EXTI_SWIER; // software inteerupt event register;
    uint32_t volatile EXTI_PR;  //pending register


} TypeDef_EXTI;

//0x4001 3C00 - 0x4001 3FFF
#define EXTI ((TypeDef_EXTI *)0x40013C00)
#endif //EXTI_H