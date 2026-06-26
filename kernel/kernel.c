#include "cpu/idt.h"
#include "cpu/pic.h"
#include "video/vga.h"
#include "memory/phys.h"
#include "drivers/keyboard.h"
#include "terminal/shell.h"
#include "fs/vfs.h"
#include "version.h"

void kernel_main(void)
{
    pic_init();
    idt_init();
    vga_init();
    phys_init();
    keyboard_init();
    vfs_init();

    vga_set_color(2, 0);
    vga_print_string("Welcome to FynOS ");
    vga_print_string(FYNOS_VERSION);
    vga_print_string("!\n");
    vga_set_color(7, 0);
    vga_print_string("32-bit Protected Mode C Kernel\n\n");

    shell_run();
}
