# Driver Architecture

> Status: **v0.1 - keyboard driver**

## Overview

Device drivers live in `kernel/drivers/` and expose a consistent API to the kernel. Drivers access hardware; kernel services call drivers - never the reverse.

## v0.1 Drivers

### PS/2 Keyboard - `kernel/drivers/keyboard.c`

- Polls and handles IRQ 1 (keyboard interrupt)
- Translates scancodes to ASCII
- Ring buffer for key events consumed by shell

```c
void keyboard_init(void);
int keyboard_has_key(void);
char keyboard_read_char(void);
```

## Driver Framework (v0.2 - Planned)

```c
typedef struct driver {
    const char *name;
    int (*probe)(void);
    int (*init)(void);
} driver_t;

void drivers_register(driver_t *drv);
void drivers_init_all(void);
```

## Future Drivers

| Driver | Module | Milestone |
|--------|--------|-----------|
| PS/2 Keyboard | `keyboard.c` | M3 |
| ATA/IDE Disk | `ata.c` | M5 |
| PS/2 Mouse | `mouse.c` | M6 |
| PCI enumeration | `pci.c` | v1.0 |
| USB | `usb.c` | v1.0 |

## Rules

- Drivers never call applications
- Drivers never draw graphics (video module handles output)
- All port I/O via `kernel/cpu/io.h` (`inb`/`outb`)
