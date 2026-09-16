CFLAGS = -g -O0 -mcpu=cortex-m4 -mthumb -nostdlib -Iinclude

SRC = examples/uart/main.c

all: firmware.elf

firmware.elf: platform/startup.s $(SRC) $(DRIVERS)
	arm-none-eabi-gcc $(CFLAGS) -T platform/stm32f446.ld platform/startup.s $(DRIVERS) $(SRC) -o firmware.elf

clean:
	rm -f firmware.elf

flash:
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program firmware.elf verify reset exit"