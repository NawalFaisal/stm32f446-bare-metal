CFLAGS = -g -O0 -mcpu=cortex-m4 -mthumb -nostdlib -Iinclude

DRIVERS = drivers/gpio.c drivers/uart.c drivers/ringbuffer.c drivers/nvic.c
SRC = examples/drivers/uart-interrupt-driver/main.c

all: firmware.elf

firmware.elf: platform/startup.s $(SRC) $(DRIVERS)
	arm-none-eabi-gcc $(CFLAGS) -T platform/stm32f446.ld platform/startup.s $(DRIVERS) $(SRC) -o firmware.elf

clean:
	rm -f firmware.elf

flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program firmware.elf verify reset exit"

# Tooling

FMT_FILES := $(shell find drivers include examples platform utils \
                      \( -name '*.c' -o -name '*.h' \) 2>/dev/null)

format:
	clang-format -i $(FMT_FILES)

format-check:
	clang-format --dry-run --Werror $(FMT_FILES)

tidy:
	clang-tidy $(FMT_FILES) -- -Iinclude

test:
	$(MAKE) -C tests/unit

check: format-check test

.PHONY: format format-check tidy test check


