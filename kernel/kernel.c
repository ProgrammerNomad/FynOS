// FynOS Kernel v0.1.0
// Simple C kernel with VGA text output

// VGA text mode constants
#define VGA_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Colors
#define VGA_COLOR_BLACK 0
#define VGA_COLOR_WHITE 15
#define VGA_COLOR_GREEN 2
#define VGA_COLOR_BLUE 1

// Global variables
static unsigned int cursor_x = 0;
static unsigned int cursor_y = 0;
static unsigned char current_color = VGA_COLOR_WHITE | (VGA_COLOR_BLACK << 4);

// Function prototypes
void kernel_main(void);
void clear_screen(void);
void print_char(char c);
void print_string(const char* str);
void set_cursor_pos(unsigned int x, unsigned int y);
void set_color(unsigned char color);

// Kernel entry point
void kernel_main(void) {
    // Clear screen and set up
    clear_screen();
    set_color(VGA_COLOR_GREEN | (VGA_COLOR_BLACK << 4));
    
    // Print welcome message
    print_string("Welcome to FynOS v0.1.0!\n");
    print_string("32-bit Protected Mode Kernel\n\n");
    
    set_color(VGA_COLOR_WHITE | (VGA_COLOR_BLACK << 4));
    print_string("Features:\n");
    print_string("- 32-bit protected mode\n");
    print_string("- C kernel\n");
    print_string("- VGA text output\n");
    print_string("- Multi-stage bootloader\n\n");
    
    set_color(VGA_COLOR_BLUE | (VGA_COLOR_BLACK << 4));
    print_string("System ready!\n");
    
    // Infinite loop
    while(1) {
        // Kernel is running but idle
        __asm__ volatile ("hlt");
    }
}

// Clear the entire screen
void clear_screen(void) {
    unsigned short* vga = (unsigned short*)VGA_MEMORY;
    unsigned short blank = ' ' | (current_color << 8);
    
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = blank;
    }
    
    cursor_x = 0;
    cursor_y = 0;
}

// Print a single character
void print_char(char c) {
    unsigned short* vga = (unsigned short*)VGA_MEMORY;
    
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\r') {
        cursor_x = 0;
    } else if (c >= ' ') {
        unsigned short entry = c | (current_color << 8);
        vga[cursor_y * VGA_WIDTH + cursor_x] = entry;
        cursor_x++;
    }
    
    // Handle line wrap
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    
    // Handle screen scroll (simple wrap-around for now)
    if (cursor_y >= VGA_HEIGHT) {
        cursor_y = 0;
    }
}

// Print a string
void print_string(const char* str) {
    while (*str) {
        print_char(*str);
        str++;
    }
}

// Set cursor position
void set_cursor_pos(unsigned int x, unsigned int y) {
    if (x < VGA_WIDTH && y < VGA_HEIGHT) {
        cursor_x = x;
        cursor_y = y;
    }
}

// Set text color
void set_color(unsigned char color) {
    current_color = color;
}