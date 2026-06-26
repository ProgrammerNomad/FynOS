#include "terminal/shell.h"
#include "terminal/commands.h"
#include "video/vga.h"
#include "drivers/keyboard.h"

#define SHELL_LINE_MAX 256

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
            shell_dispatch(line);
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
