#ifndef FYNOS_KEYBOARD_H
#define FYNOS_KEYBOARD_H

#include "types.h"

/* Initialize PS/2 keyboard (PIC, IRQ 1). */
void keyboard_init(void);

/* IRQ handler called from IDT for IRQ 1. */
void keyboard_irq_handler(void);

/* Return 1 if a key is available in the buffer. */
int keyboard_has_key(void);

/* Read and remove the next key from the buffer. Blocks not - check has_key first. */
char keyboard_read_char(void);

#endif
