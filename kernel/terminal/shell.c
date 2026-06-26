#include "terminal/shell.h"
#include "video/vga.h"
#include "memory/phys.h"
#include "drivers/keyboard.h"

#define SHELL_LINE_MAX 256

static int str_equals(const char *a, const char *b)
{
    while (*a && *b) {
        if (*a != *b) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == *b;
}

static void shell_print_uint(uint32_t n)
{
    char buf[12];
    int i = 0;

    if (n == 0) {
        vga_print_char('0');
        return;
    }

    while (n > 0) {
        buf[i++] = (char)('0' + (n % 10));
        n /= 10;
    }

    while (i > 0) {
        vga_print_char(buf[--i]);
    }
}

static void shell_print_mem(void)
{
    size_t free_bytes = phys_free_bytes();
    uint32_t kb = (uint32_t)(free_bytes / 1024);

    vga_print_string("Free memory: ");
    shell_print_uint(kb);
    vga_print_string(" KB\n");
}

static void shell_execute(const char *line)
{
    if (line[0] == '\0') {
        return;
    }

    if (str_equals(line, "help")) {
        vga_print_string("Commands: help, clear, mem, version\n");
    } else if (str_equals(line, "clear")) {
        vga_clear();
    } else if (str_equals(line, "mem")) {
        shell_print_mem();
    } else if (str_equals(line, "version")) {
        vga_print_string("FynOS v0.1.0\n");
    } else {
        vga_print_string("Unknown command. Type 'help'.\n");
    }
}

void shell_run(void)
{
    char line[SHELL_LINE_MAX];
    int pos = 0;

    vga_print_string("FynOS shell ready. Type 'help'.\n");
    vga_print_string("FynOS> ");

    while (1) {
        char c = keyboard_read_char();

        if (c == '\n') {
            vga_print_char('\n');
            line[pos] = '\0';
            shell_execute(line);
            pos = 0;
            vga_print_string("FynOS> ");
        } else if (c == '\b') {
            if (pos > 0) {
                pos--;
                vga_print_char('\b');
            }
        } else if (c >= ' ' && pos < SHELL_LINE_MAX - 1) {
            line[pos++] = c;
            vga_print_char(c);
        }
    }
}
