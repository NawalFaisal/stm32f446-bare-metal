#ifndef DWT_H
#define DWT_H
#include <stdint.h>

// DWT is the data watchpoint and trace unit inside the cortex-m4 core

typedef struct {
    volatile uint32_t CTRL;   
    volatile uint32_t CYCCNT; 
} dwt_t;

#define DWT   ((dwt_t *)0xE0001000)
#define DEMCR (*(volatile uint32_t *)0xE000EDFC) 

void     dwt_init(void);
uint32_t dwt_cycles(void);

#endif // DWT_H