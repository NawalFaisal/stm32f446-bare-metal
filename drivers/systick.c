#include "systick.h"

// how the handler gets hooked up:
// 1. the function name has to match what's in the vector table exactly
// 2. if it doesn't, slot 15 keeps pointing at Default_Handler and the chip
//    just freezes there when the timer fires. no error, nothing.
// 3. when the name matches, the linker finds my function's symbol and writes
//    its address into slot 15. that's the whole connection.
// 4. the vector table is an array of function pointers. each slot holds the
//    address of a FUNCTION (not a register). hardware reads slot N and jumps there.

// two different jobs here
//   systick_init()    -> I call it, once, from main. sets up the hardware. 
// they don't call each other. they share the `ticks` variable.

#define SYSTEM_CLOCK_HZ 16000000U   // default HSI clock. if I set up the PLL later this is wrong.

// volatile is mandatory. main reads this in a loop and never writes it, so
// without volatile the compiler caches it in a register and delay_ms hangs forever.
volatile uint32_t ticks = 0;


// runs ONCE from main
void systick_init(void) {
    // RVR = how many ticks between interrupts.
    // 16,000,000 / 1000 = 16000 ticks per ms.
    // minus 1 because the counter counts down TO zero, so zero is one of the counts.
    SYST->SYST_RVR = (SYSTEM_CLOCK_HZ / 1000U) - 1U;   // 15999

    SYST->SYST_CVR = 0;   // clear whatever garbage is in the counter

    // CSR last, so the timer doesn't start running before it's configured
    // bit 0 ENABLE     turn the counter on
    // bit 1 TICKINT    fire an interrupt when it hits zero
    // bit 2 CLKSOURCE  1 = processor clock
    SYST->SYST_CSR = (1U << 0) | (1U << 1) | (1U << 2);
}

// runs EVERY TIME the timer hits zero. keep it short.
void SysTick_Handler(void) {
    ticks++;
}

// counts real time, not loop iterations like my old for-loop delay did.
// subtracting unsigned handles wraparound correctly.
void delay_ms(uint32_t ms) {
    uint32_t start = ticks;
    while ((ticks - start) < ms);
}