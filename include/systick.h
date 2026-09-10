#ifndef SYSTICK_H
#define SYSTICK_H
#include <stdint.h>

typedef struct {
    uint32_t volatile SYST_CSR;
    uint32_t volatile SYST_RVR;
    uint32_t volatile SYST_CVR;
    uint32_t volatile SYST_CALIB;
} TypeDef_SYST;

//cast this memory space to that struct 
#define SYST ((TypeDef_SYST *)0xE000E010)
void systick_init(void);
void delay_ms(uint32_t ms);
extern volatile uint32_t ticks;

#endif //SYSTICK_H

