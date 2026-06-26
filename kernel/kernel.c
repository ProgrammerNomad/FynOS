#include "cpu/idt.h"
#include "cpu/pic.h"
#include "video/vga.h"
#include "memory/phys.h"
#include "memory/heap.h"
#include "memory/paging.h"
#include "drivers/keyboard.h"
#include "drivers/pit.h"
#include "terminal/shell.h"
#include "fs/vfs.h"
#include "debug/panic.h"
#include "debug/serial.h"
#include "debug/logger.h"
#include "version.h"

void kernel_main(void)
{
    serial_init();
    serial_write("FynOS kernel starting\n");

    boot_stage(1);
    pic_init();
    log_info("PIC initialized");

    boot_stage(2);
    idt_init();
    log_info("IDT initialized");

    boot_stage(3);
    vga_init();
    log_info("VGA initialized");

    boot_stage(4);
    phys_init();
    heap_init();
    log_info("Physical memory and heap initialized");

    boot_stage(5);
    paging_init();
    log_info("Paging enabled");

    boot_stage(6);
    keyboard_init();
    pit_init();
    vfs_init();
    log_info("Drivers and VFS stubs initialized");

    if (heap_self_test() != 0) {
        PANIC("Heap self-test failed");
    }
    log_info("Heap self-test passed");

    vga_set_color(2, 0);
    vga_print_string("Welcome to FynOS ");
    vga_print_string(FYNOS_VERSION);
    vga_print_string("!\n");
    vga_set_color(7, 0);
    vga_print_string("32-bit Protected Mode C Kernel\n\n");

    boot_stage(7);
    pic_unmask(0);
    pic_unmask(1);
    __asm__ volatile("sti");
    boot_stage(8);
    log_info("IRQ enabled (PIT + keyboard)");
    shell_run();
}
