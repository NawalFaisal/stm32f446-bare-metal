# stm32f446-bare-metal

Bare-metal firmware for the STM32F446RE (Cortex-M4) on a Nucleo-F446RE, written in C and assembly with no  HAL, no CubeMX and no generated code. The startup code, linker script and drivers are written from the reference manual and the datasheet.

I started this to learn what runs before `main()`, how the vector table is laid out, and why a peripheral does nothing until its bus clock is on.

## What's implemented

- **Startup code:** vector table, reset handler, and `.data` and `.bss` initialization
- **Linker script:** places the vector table and controls the memory layout
- **GPIO driver:** register-level driver using BSRR, plus LED and button helpers
- **SysTick:** timer driver with a blocking delay and an interrupt example
- **EXTI:** NVIC, SYSCFG and EXTI setup, with an interrupt-driven button toggle
- **UART (USART2):** polled transmit, and interrupt-driven receive that feeds a ring buffer
- **Ring buffer:** a small standalone driver used by the UART receive path

## Layout

```
drivers/    peripheral drivers (GPIO, SysTick, EXTI, UART, ring buffer)   
platform/   startup code and linker script                                
include/    headers
examples/   small programs that use the drivers
utils/      helpers
```

## Hardware and tools

| | |
|---|---|
| Board | Nucleo-F446RE |
| Compiler | arm-none-eabi-gcc |
| Build | GNU Make |
| Flash and debug | OpenOCD with ST-Link, GDB |

## Build and flash

```
make
make flash
```

Serial output: `screen /dev/ttyACM0 115200`

## Debugging

Start OpenOCD with the ST-Link and STM32F4x configs, then connect GDB to port 3333.

```
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

## References

- RM0390 reference manual
- STM32F446xx datasheet
- ARM Cortex-M4 generic user guide

## Note on AI

I used AI to help word this README. The firmware itself is my own code.
