#include "debug/serial.h"
#include "cpu/io.h"

#define COM1_DATA       0x3F8
#define COM1_IER        0x3F9
#define COM1_FCR        0x3FA
#define COM1_LCR        0x3FB
#define COM1_LSR        0x3FD

#define LSR_TX_EMPTY    0x20

static int serial_is_transmit_empty(void)
{
    return (inb(COM1_LSR) & LSR_TX_EMPTY) != 0;
}

void serial_init(void)
{
    outb(COM1_IER, 0x00);
    outb(COM1_LCR, 0x80);
    outb(COM1_DATA, 0x03);
    outb(COM1_IER, 0x00);
    outb(COM1_LCR, 0x03);
    outb(COM1_FCR, 0xC7);
    outb(COM1_DATA + 4, 0x0B);
}

void serial_write_char(char c)
{
    while (!serial_is_transmit_empty()) {
    }
    outb(COM1_DATA, (uint8_t)c);
}

void serial_write(const char *str)
{
    if (str == NULL) {
        return;
    }

    while (*str != '\0') {
        serial_write_char(*str);
        str++;
    }
}
