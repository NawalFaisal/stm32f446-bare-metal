# stm32f446-bare-metal

Register-level peripheral drivers for the STM32F446RE, written in C and a bit of AArch32 assembly.

## Overview

No abstractions. Peripherals are structs overlaid on their base addresses, the vector table and startup code are hand-written, and the data structures are unit-tested on the host.

## Target Hardware

| Feature | Detail |
|---|---|
| MCU | STM32F446RE |
| Core | Arm Cortex-M4F |
| Clock | 16 MHz HSI, no PLL |
| Board | Nucleo-F446RE |
| Debug | ST-Link V2-1 over OpenOCD |
| Toolchain | `arm-none-eabi-gcc` |

## Project Structure

```
stm32f446-bare-metal/
├── drivers/        # gpio, rcc, spi, uart, exti, nvic, systick, dwt, sys
├── include/        # public headers, the only include path a consumer needs
├── utils/          # ring buffer, SPSC queue, delay
├── platform/       # startup.s and the linker script
├── examples/       # one main.c per peripheral, register level and driver level
├── tests/          # Unity tests, run on the host
├── Makefile
└── stm32f446.mk    # include file for projects consuming this as a submodule
```

## Quick Start

| Command | Description |
|---|---|
| `make` | Build one example into `firmware.elf` |
| `make flash` | Flash over OpenOCD |
| `make test` | Build and run host unit tests, no board needed |
| `make clean` | Remove build artifacts |

The example is hardcoded in the Makefile's link line. Edit the path to build a different one.

## Drivers

| Peripheral | Provides |
|---|---|
| `rcc` | `rcc_enable(RCC_GPIOA)`, bus and bit packed into one enum |
| `gpio` | mode, alternate function, set, reset |
| `spi` | master or slave, modes 0-3, eight prescalers, blocking transfer |
| `uart` | polled and interrupt-driven, both directions |
| `exti` | external interrupt lines with SYSCFG port selection |
| `nvic` | enable, disable, pend, clear |
| `systick` | 24-bit down counter |
| `dwt` | cycle-exact timing from the core debug unit |

## Notes

**Weak handlers.** Handlers are aliased to `Default_Handler` in `startup.s`. Define one in C and the linker takes the strong symbol. Vector slot number is IRQ + 16. The table runs to slot 56, IRQ 40.

**Write-1-to-act registers.** `NVIC->ICER`, `ICPR`, `EXTI->PR` and `GPIOx->BSRR` read back state, not the last value written, so they take `=` and not `|=`. Read-modify-write on `ICER` disables every interrupt in the bank.

**`.bss`.** The linker only reserves it; the startup code zeroes it before `main`. Without that loop, zero-initialized globals hold whatever was in RAM and no fault is raised.

**DWT.** A core debug unit, not an ST peripheral, so no clock enable. `TRCENA` in `DEMCR` must be set before `CYCCNTENA`.

## Debugging

```
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
arm-none-eabi-gdb firmware.elf -ex "target remote :3333"
```

`x/16xb &symbol` to check what a global holds. `x/8xw 0x40013000` to read a peripheral directly rather than trusting the driver that wrote it.

## Known Limitations

| Issue | Impact |
|---|---|
| `.data` never copied from flash to RAM | `static int x = 5;` reads garbage. Latent, since every global here is zero-initialized |
| No PLL setup | Stuck at 16 MHz HSI |
| No FPU enable | `-mfloat-abi=hard` would fault, `CPACR` is never written |
| Vector table stops at IRQ 40 | DMA2, higher timers, I2C and SPI error vectors absent |
| `usart_init` uses `\|=` without clearing CR1 | Calling it twice leaves stale config. `spi_init` clears first |
| UART buffers are single-instance | A second port needs them per-instance |
| `ringbuf_t` fixed at 64 bytes of `char` | Depth and element type are compile-time |
| `queue_t` unused | Built for an ISR handoff that isn't wired up |
| SPI ignores `OVR` and `MODF` | Error flags silently discarded |
| `delay()` is an unmeasured busy loop | Duration depends on optimization level |
| No I2C, DMA, timer, ADC or PWM | |
| `-Werror` not set | Only `-Wall -Wextra` |

## AI Use

README drafted with AI. Drivers, startup code and linker script are mine. The DWT driver, the generic queue and the Unity test files were written with AI assistance. Bugs in my own drivers were surfaced through AI review and reproduced on hardware before being changed.

## License

MIT — see LICENSE.