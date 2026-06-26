#ifndef FYNOS_IDT_H
#define FYNOS_IDT_H

#include "types.h"

/* CPU register snapshot passed to interrupt handlers (matches isr.asm stack). */
typedef struct registers {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp_dummy, ebx, edx, ecx, eax;
    uint32_t int_no;
    uint32_t err_code;
} registers_t;

/* Initialize IDT and load it. */
void idt_init(void);

/* Common C interrupt handler called from ASM stubs. */
void isr_handler(registers_t *regs);

#endif
