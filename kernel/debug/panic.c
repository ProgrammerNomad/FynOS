#include "debug/panic.h"
#include "debug/serial.h"
#include "video/vga.h"

static void panic_write_serial(const char *message, const char *file, int line)
{
    serial_write("\n*********************************\n");
    serial_write("KERNEL PANIC\n");
    if (message != NULL && message[0] != '\0') {
        serial_write("Reason: ");
        serial_write(message);
        serial_write("\n");
    }
    if (file != NULL && file[0] != '\0') {
        serial_write("File: ");
        serial_write(file);
        serial_write("\n");
    }
    if (line > 0) {
        serial_write("Line: ");
        /* minimal int print */
        {
            char buf[12];
            int i = 0;
            int n = line;

            if (n == 0) {
                serial_write_char('0');
            } else {
                while (n > 0) {
                    buf[i++] = (char)('0' + (n % 10));
                    n /= 10;
                }
                while (i > 0) {
                    serial_write_char(buf[--i]);
                }
            }
        }
        serial_write("\n");
    }
    serial_write("System halted\n");
    serial_write("*********************************\n");
}

static void panic_write_vga(const char *message)
{
    vga_set_color(4, 0);
    vga_print_string("\n*********************************\n");
    vga_print_string("KERNEL PANIC\n");
    if (message != NULL && message[0] != '\0') {
        vga_print_string(message);
        vga_print_char('\n');
    }
    vga_print_string("System halted\n");
    vga_print_string("*********************************\n");
    vga_set_color(7, 0);
}

void panic_at(const char *message, const char *file, int line)
{
    panic_write_serial(message, file, line);
    panic_write_vga(message);

    for (;;) {
        __asm__ volatile("cli; hlt");
    }
}

void panic(const char *message)
{
    panic_at(message, NULL, 0);
}
