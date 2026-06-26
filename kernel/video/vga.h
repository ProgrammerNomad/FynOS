#ifndef FYNOS_VGA_H
#define FYNOS_VGA_H

#include "types.h"

/* Initialize VGA text mode (clear screen). */
void vga_init(void);

/* Clear the entire screen. */
void vga_clear(void);

/* Set foreground and background colors (0-15). */
void vga_set_color(uint8_t fg, uint8_t bg);

/* Print a single character. Handles \n, \r, \b. */
void vga_print_char(char c);

/* Print a null-terminated string. */
void vga_print_string(const char *str);

#endif
