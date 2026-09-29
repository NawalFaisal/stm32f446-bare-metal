#include "nvic.h"
#include <stdint.h>

void nvic_enable(IRQn_Type irqn){
    NVIC -> ISER[irqn / 32] |= (1U << (irqn % 32));

}

void nvic_clear_enable(IRQn_Type irqn){
    NVIC -> ICER[irqn / 32] |= (1U << (irqn % 32));
}

void nvic_pending(IRQn_Type irqn){
    NVIC -> ISPR[irqn / 32] |= (1U << (irqn % 32));
}

void nvic_clear_pending(IRQn_Type irqn){
    NVIC -> ICPR[irqn / 32] |= (1U << (irqn % 32));
}