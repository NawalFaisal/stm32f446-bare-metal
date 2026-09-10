.syntax unified
.cpu cortex-m4
.thumb

.global Reset_Handler
.global _estack

/* Everything we don't explicitly handle lands here */
.thumb_func
Default_Handler:
    b Default_Handler

/* Weak alias: if C code defines SysTick_Handler (strong symbol),
 * the linker uses that instead. If not, it points at Default_Handler. */
.weak SysTick_Handler
.thumb_set SysTick_Handler, Default_Handler

/* The first two words of flash. The CPU reads these at power-on:
 * slot 0 -> initial stack pointer, slot 1 -> where to start executing.
 */
.section .isr_vector,"a",%progbits
.word _estack              /* 0: initial stack pointer          */
.word Reset_Handler        /* 1: Reset                          */
.word Default_Handler      /* 2: NMI                            */
.word Default_Handler      /* 3: HardFault                      */
.word Default_Handler      /* 4: MemManage                      */
.word Default_Handler      /* 5: BusFault                       */
.word Default_Handler      /* 6: UsageFault                     */
.word 0                    /* 7: reserved                       */
.word 0                    /* 8: reserved                       */
.word 0                    /* 9: reserved                       */
.word 0                    /* 10: reserved                      */
.word Default_Handler      /* 11: SVCall                        */
.word Default_Handler      /* 12: Debug Monitor                 */
.word 0                    /* 13: reserved                      */
.word Default_Handler      /* 14: PendSV                        */
.word SysTick_Handler      /* 15: SysTick                       */

.section .text
.type Reset_Handler, %function

/* Globals initialized to 0 live in .bss, which is only reserved space —
 * nothing is stored there. Something has to zero it at runtime, and that
 * something is this startup code, before main runs.
 * _sbss and _ebss are exported by the linker script.
 */
Reset_Handler:
    ldr r0, =_sbss      /* start of .bss */
    ldr r1, =_ebss      /* end of .bss */
    movs r2, #0         /* the value to write */
    str r2, [r0]        /* TODO: only zeroes the FIRST word — needs a loop */
    bl main

loop:
    b loop