#include "video/vga.h"
#include "cpu/io.h"

#define VGA_MEMORY    0xB8000
#define VGA_WIDTH     80
#define VGA_HEIGHT    25
#define VGA_CRT_INDEX 0x3D4
#define VGA_CRT_DATA  0x3D5

static uint32_t cursor_x = 0;
static uint32_t cursor_y = 0;
static uint8_t  current_color = 0x07;

static void vga_update_hw_cursor(void)
{
    uint16_t pos = (uint16_t)(cursor_y * VGA_WIDTH + cursor_x);

    outb(VGA_CRT_INDEX, 0x0F);
    outb(VGA_CRT_DATA, (uint8_t)(pos & 0xFF));
    outb(VGA_CRT_INDEX, 0x0E);
    outb(VGA_CRT_DATA, (uint8_t)((pos >> 8) & 0xFF));
}

static void vga_enable_hw_cursor(void)
{
    outb(VGA_CRT_INDEX, 0x0A);
    outb(VGA_CRT_DATA, (uint8_t)((inb(VGA_CRT_DATA) & 0xC0) | 0x0E));
    outb(VGA_CRT_INDEX, 0x0B);
    outb(VGA_CRT_DATA, 0x0F);
}

static void vga_scroll(void)
{
    uint16_t *vga = (uint16_t *)VGA_MEMORY;
    uint32_t i;
    uint16_t blank = (uint16_t)(' ' | ((uint16_t)current_color << 8));

    for (i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1); i++) {
        vga[i] = vga[i + VGA_WIDTH];
    }
    for (i = VGA_WIDTH * (VGA_HEIGHT - 1); i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = blank;
    }
    cursor_y = VGA_HEIGHT - 1;
}

void vga_init(void)
{
    vga_clear();
    vga_enable_hw_cursor();
    vga_update_hw_cursor();
}

void vga_clear(void)
{
    uint16_t *vga = (uint16_t *)VGA_MEMORY;
    uint32_t i;
    uint16_t blank = (uint16_t)(' ' | ((uint16_t)current_color << 8));

    for (i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = blank;
    }
    cursor_x = 0;
    cursor_y = 0;
    vga_update_hw_cursor();
}

void vga_set_color(uint8_t fg, uint8_t bg)
{
    current_color = (uint8_t)(fg | (bg << 4));
}

void vga_print_char(char c)
{
    uint16_t *vga = (uint16_t *)VGA_MEMORY;

    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\r') {
        cursor_x = 0;
    } else if (c == '\b') {
        if (cursor_x > 0) {
            cursor_x--;
            vga[cursor_y * VGA_WIDTH + cursor_x] =
                (uint16_t)(' ' | ((uint16_t)current_color << 8));
        }
    } else if (c >= ' ') {
        vga[cursor_y * VGA_WIDTH + cursor_x] =
            (uint16_t)(c | ((uint16_t)current_color << 8));
        cursor_x++;
    }

    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= VGA_HEIGHT) {
        vga_scroll();
    }

    vga_update_hw_cursor();
}

void vga_print_string(const char *str)
{
    while (*str) {
        vga_print_char(*str);
        str++;
    }
}
