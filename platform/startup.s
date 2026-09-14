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
.weak EXTI0_IRQHandler
.thumb_set EXTI0_IRQHandler, Default_Handler
.weak EXTI1_IRQHandler
.thumb_set EXTI1_IRQHandler, Default_Handler
.weak EXTI2_IRQHandler
.thumb_set EXTI2_IRQHandler, Default_Handler
.weak EXTI3_IRQHandler
.thumb_set EXTI3_IRQHandler, Default_Handler
.weak EXTI4_IRQHandler
.thumb_set EXTI4_IRQHandler, Default_Handler
.weak EXTI9_5_IRQHandler
.thumb_set EXTI9_5_IRQHandler, Default_Handler
.weak EXTI15_10_IRQHandler
.thumb_set EXTI15_10_IRQHandler, Default_Handler

/* The first two words of flash. The CPU reads these at power-on:
 * slot 0 -> initial stack pointer, slot 1 -> where to start executing.
 */
.section .isr_vector,"a",%progbits
.word _estack                   /*  0                        */
.word Reset_Handler             /*  1                        */
.word Default_Handler           /*  2: NMI                   */
.word Default_Handler           /*  3: HardFault             */
.word Default_Handler           /*  4: MemManage             */
.word Default_Handler           /*  5: BusFault              */
.word Default_Handler           /*  6: UsageFault            */
.word 0                         /*  7: reserved              */
.word 0                         /*  8: reserved              */
.word 0                         /*  9: reserved              */
.word 0                         /* 10: reserved              */
.word Default_Handler           /* 11: SVCall                */
.word Default_Handler           /* 12: Debug Monitor         */
.word 0                         /* 13: reserved              */
.word Default_Handler           /* 14: PendSV                */
.word SysTick_Handler           /* 15: SysTick               */

/* ---- peripheral interrupts: slot = IRQ + 16 ---- */
.word Default_Handler           /* 16: IRQ0  WWDG            */
.word Default_Handler           /* 17: IRQ1  PVD             */
.word Default_Handler           /* 18: IRQ2  TAMP_STAMP      */
.word Default_Handler           /* 19: IRQ3  RTC_WKUP        */
.word Default_Handler           /* 20: IRQ4  FLASH           */
.word Default_Handler           /* 21: IRQ5  RCC             */
.word EXTI0_IRQHandler          /* 22: IRQ6  EXTI0           */
.word EXTI1_IRQHandler          /* 23: IRQ7  EXTI1           */
.word EXTI2_IRQHandler          /* 24: IRQ8  EXTI2           */
.word EXTI3_IRQHandler          /* 25: IRQ9  EXTI3           */
.word EXTI4_IRQHandler          /* 26: IRQ10 EXTI4           */
.word Default_Handler           /* 27: IRQ11 DMA1_Stream0    */
.word Default_Handler           /* 28: IRQ12 DMA1_Stream1    */
.word Default_Handler           /* 29: IRQ13 DMA1_Stream2    */
.word Default_Handler           /* 30: IRQ14 DMA1_Stream3    */
.word Default_Handler           /* 31: IRQ15 DMA1_Stream4    */
.word Default_Handler           /* 32: IRQ16 DMA1_Stream5    */
.word Default_Handler           /* 33: IRQ17 DMA1_Stream6    */
.word Default_Handler           /* 34: IRQ18 ADC             */
.word Default_Handler           /* 35: IRQ19 CAN1_TX         */
.word Default_Handler           /* 36: IRQ20 CAN1_RX0        */
.word Default_Handler           /* 37: IRQ21 CAN1_RX1        */
.word Default_Handler           /* 38: IRQ22 CAN1_SCE        */
.word EXTI9_5_IRQHandler        /* 39: IRQ23 EXTI9_5         */
.word Default_Handler           /* 40: IRQ24 TIM1_BRK_TIM9   */
.word Default_Handler           /* 41: IRQ25 TIM1_UP_TIM10   */
.word Default_Handler           /* 42: IRQ26 TIM1_TRG_TIM11  */
.word Default_Handler           /* 43: IRQ27 TIM1_CC         */
.word Default_Handler           /* 44: IRQ28 TIM2            */
.word Default_Handler           /* 45: IRQ29 TIM3            */
.word Default_Handler           /* 46: IRQ30 TIM4            */
.word Default_Handler           /* 47: IRQ31 I2C1_EV         */
.word Default_Handler           /* 48: IRQ32 I2C1_ER         */
.word Default_Handler           /* 49: IRQ33 I2C2_EV         */
.word Default_Handler           /* 50: IRQ34 I2C2_ER         */
.word Default_Handler           /* 51: IRQ35 SPI1            */
.word Default_Handler           /* 52: IRQ36 SPI2            */
.word Default_Handler           /* 53: IRQ37 USART1          */
.word Default_Handler           /* 54: IRQ38 USART2          */
.word Default_Handler           /* 55: IRQ39 USART3          */
.word EXTI15_10_IRQHandler      /* 56: IRQ40 EXTI15_10  <-- PC13 */

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