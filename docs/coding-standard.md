# FynOS Coding Standards

Apply these rules before thousands of lines accumulate.

## Module Structure

- One module = one responsibility
- Every module contains paired `xxx.c` + `xxx.h` - no exceptions
- No global variables unless unavoidable; prefer module-local `static` state
- Every public function documented in its `.h` file
- Every feature has a corresponding design doc in `docs/architecture/`

## Compilation

- `-Wall -Wextra -Werror` - **no warnings allowed**
- `-std=c99` for all C code
- `-ffreestanding -m32 -nostdlib -fno-builtin -fno-stack-protector` for kernel code
- Assembly for bootloaders and CPU-specific routines only

## Naming

| Item | Convention | Example |
|------|------------|---------|
| Files | `snake_case.c` / `snake_case.h` | `vga.c`, `keyboard.h` |
| Functions | `module_action()` | `vga_print_string()` |
| Types | `snake_case_t` | `phys_addr_t` |
| Constants | `MODULE_NAME_VALUE` | `VGA_WIDTH` |
| Static functions | same as public, but file-local | `static void vga_scroll()` |

## Includes

1. Module's own `.h` first
2. `kernel/include/` headers (`types.h`, etc.)
3. Other kernel module headers
4. No circular dependencies between modules

## Documentation

Every public function in a `.h` file:

```c
/* Print a null-terminated string to the VGA text buffer. */
void vga_print_string(const char *str);
```

## Directory Layout

```
kernel/video/vga.c       kernel/video/vga.h
kernel/drivers/keyboard.c   kernel/drivers/keyboard.h
kernel/memory/phys.c     kernel/memory/phys.h
```

Shared types and macros live in `kernel/include/`.

## Git Commits

- Clear, imperative subject line
- Reference issue/milestone when applicable
- Every commit must keep the boot chain working
