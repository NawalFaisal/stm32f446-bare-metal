F446_DIR  := $(dir $(lastword $(MAKEFILE_LIST)))
F446_SRCS := $(wildcard $(F446_DIR)drivers/*.c) $(wildcard $(F446_DIR)utils/*.c)
F446_ASM  := $(F446_DIR)platform/startup.s
F446_INC  := -I$(F446_DIR)include
F446_LD   := $(F446_DIR)platform/stm32f446.ld