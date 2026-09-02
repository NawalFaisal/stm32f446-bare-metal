# stm32-bare-metal-programming

Bare-metal firmware for the **STM32F446RE** (ARM Cortex-M4), written in C with no
vendor HAL, no CubeMX, and no generated code. Startup code, linker script, and all
peripheral drivers are written from scratch against the reference manual and datasheet.

---

## Why bare-metal

ST's HAL works, but it hides the thing I wanted to learn. Using it, I would never see
what runs before `main()`, how the vector table is laid out, or why a peripheral needs
its bus clock enabled before its registers respond.

Writing the startup code and linker script myself meant I controlled the memory layout,
the `.data`/`.bss` initialization, and the reset path directly. The trade is development
speed for visibility: everything here took longer than it would have with CubeMX, and I
can explain every line of it.

---

## Hardware and toolchain

| | |
|---|---|
| Target | STM32F446RE (Nucleo-F446RE board) |
| Core | ARM Cortex-M4 |
| Compiler | `arm-none-eabi-gcc` |
| Debugger | GDB (`arm-none-eabi-gdb`) |
| On-chip debug | OpenOCD + ST-Link |
| Build | GNU Make |

---

## Repository layout

```
GPIO/
  blinky/                 LED on PA5 via direct register writes
  alternating-blinky/     Two LEDs alternating
  button-input-blinky/    Reads user button (PC13), drives LED
  startup.s               Reset handler, vector table, .data/.bss init
  link.ld                 Memory layout: FLASH, SRAM, stack placement
  Makefile

UART/
  main.c                  USART2 driver: init, transmit
  startup.s
  link.ld
  Makefile
```

---

## What is implemented

### Startup code (`startup.s`)

- Interrupt vector table placed at the start of FLASH
- Reset handler: copies `.data` from FLASH to SRAM, zeroes `.bss`, then branches to `main`
- Initial stack pointer set from the linker-provided symbol

### Linker script (`link.ld`)

- Defines FLASH and SRAM regions with their actual sizes and origins
- Places `.text`, `.rodata`, `.data`, `.bss`, and the stack
- Exports symbols the startup code uses to locate section boundaries

### GPIO driver

- Enables the GPIO port clock through `RCC->AHB1ENR`
- Configures pin mode, output type, and pull-up/pull-down through `MODER`, `OTYPER`, `PUPDR`
- Drives output through `ODR` / `BSRR`
- Reads the user button on PC13 through `IDR`

### UART driver

- Enables USART2 and its GPIO port clocks
- Configures PA2/PA3 alternate function through `AFR` and `MODER`
- Sets the baud rate divisor in `BRR` from the peripheral clock frequency
- Transmits by polling the `TXE` flag in the status register

---

## Building and flashing

```sh
cd UART            # or GPIO/blinky, etc.
make               # produces firmware.elf / firmware.bin
make flash         # flashes via OpenOCD + ST-Link
```

Serial output (UART project):

```sh
screen /dev/ttyACM0 115200
```

---

## Debugging

Start OpenOCD in one terminal:

```sh
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

Connect GDB in another:

```sh
arm-none-eabi-gdb firmware.elf
(gdb) target remote :3333
(gdb) break main
(gdb) continue
```

## References

- STM32F446xx Reference Manual (RM0390)
- STM32F446xx Datasheet
- ARM Cortex-M4 Devices Generic User Guide

## AI Use Declaration

I used AI assistance to write this README. The wording and structure here were
drafted with a model and then edited by me for accuracy.

All firmware in this repository, the startup assembly, the linker script, and
the GPIO and UART drivers  was written by me, from the STM32F446xx reference
manual and datasheet. 