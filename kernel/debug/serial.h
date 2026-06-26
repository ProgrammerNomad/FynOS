#ifndef FYNOS_SERIAL_H
#define FYNOS_SERIAL_H

/* COM1 (0x3F8) - QEMU maps to host stdio with -serial stdio */
void serial_init(void);
void serial_write_char(char c);
void serial_write(const char *str);

#endif
