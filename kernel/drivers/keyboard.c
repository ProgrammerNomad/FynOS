#include "drivers/keyboard.h"
#include "cpu/io.h"

#define KEYBUF_SIZE 256

static char keybuf[KEYBUF_SIZE];
static int keybuf_read  = 0;
static int keybuf_write = 0;

static const char scancode_ascii[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

static void keybuf_push(char c)
{
    int next = (keybuf_write + 1) % KEYBUF_SIZE;

    if (next != keybuf_read) {
        keybuf[keybuf_write] = c;
        keybuf_write = next;
    }
}

static void keyboard_read_scancode(void)
{
    uint8_t scancode;

    if ((inb(0x64) & 1) == 0) {
        return;
    }

    scancode = inb(0x60);

    if (scancode & 0x80) {
        return;
    }

    if (scancode < 128 && scancode_ascii[scancode]) {
        keybuf_push(scancode_ascii[scancode]);
    }
}

void keyboard_irq_handler(void)
{
    keyboard_read_scancode();
}

void keyboard_init(void)
{
    keybuf_read  = 0;
    keybuf_write = 0;
}

int keyboard_has_key(void)
{
    return keybuf_read != keybuf_write;
}

char keyboard_read_char(void)
{
    char c;

    while (!keyboard_has_key()) {
        __asm__ volatile("sti; hlt");
    }

    c = keybuf[keybuf_read];
    keybuf_read = (keybuf_read + 1) % KEYBUF_SIZE;
    return c;
}
