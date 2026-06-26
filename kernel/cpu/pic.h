#ifndef FYNOS_PIC_H
#define FYNOS_PIC_H

#include "types.h"

/* Remap PIC to IRQ 0-15 -> INT 0x20-0x2F. */
void pic_init(void);

/* Send end-of-interrupt to PIC for the given IRQ (0-15). */
void pic_send_eoi(uint8_t irq);

/* Unmask (enable) an IRQ line. */
void pic_unmask(uint8_t irq);

#endif
