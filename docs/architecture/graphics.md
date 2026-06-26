# Graphics Architecture

> Status: **v0.1 - VGA text; v0.3+ framebuffer planned**

## Evolution Path

```
VGA Text  ->  Framebuffer  ->  2D Primitives  ->  WM (apps/)  ->  Desktop (apps/)
```

## v0.1 - VGA Text Mode

**Module:** `kernel/video/vga.c` + `vga.h`

- Direct write to `0xB8000` text buffer
- 80x25 characters, 16 colors
- Screen scroll on line overflow

```c
void vga_init(void);
void vga_clear(void);
void vga_set_color(uint8_t fg, uint8_t bg);
void vga_print_char(char c);
void vga_print_string(const char *str);
```

## v0.3 - Framebuffer (Planned)

**Module:** `kernel/video/framebuffer.c`

- Linear framebuffer via VBE or UEFI GOP
- Pixel-level drawing primitives

## v0.3 - 2D Primitives (Planned)

**Module:** `kernel/video/gfx.c`

- Lines, rectangles, blits
- Font rendering

## Userspace GUI (M7)

- Window manager: `apps/wm/` - **not kernel code**
- Desktop environment: `apps/desktop/`
- Kernel provides framebuffer access via syscalls; WM manages windows

## Rules

- Video driver never manages windows
- Compositor (future kernel module) composites surfaces; WM positions windows in userspace
- Filesystem never draws graphics
