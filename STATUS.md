# FynOS Development Status

## Current Version: v0.1.0-alpha

Interactive C kernel with modular architecture and CLI shell.

## Completed

### v0.0 - Boot + Hello
- 512-byte BIOS boot sector
- "Welcome to FynOS!" message

### v0.1 - Interactive Kernel (done)
- Multi-stage BIOS bootloader (protected mode)
- C kernel with modular layout
- VGA text output with hardware cursor sync (`kernel/video/vga.c`)
- Physical bump allocator (`kernel/memory/phys.c`)
- PS/2 keyboard driver (`kernel/drivers/keyboard.c`)
- CLI shell with command table (`kernel/terminal/shell.c`, `commands.c`)
- Shell commands: `help`, `about`, `clear`, `echo`, `mem`, `version`
- IDT and interrupt handling (`kernel/cpu/idt.c`)
- Single build system: WSL/Linux + `make`
- MIT License (`LICENSE`)

## Build

```bash
make        # Build fynos.img
make run    # Run in QEMU
make clean  # Remove build artifacts
make legacy # Build v0.0 boot sector only
```

## Milestones

| Milestone | Scope | Status |
|-----------|-------|--------|
| M0 | Bootloader | Done |
| M1 | Interactive Kernel | Done |
| M2 | Memory (heap, paging) | Planned (v0.2) |
| M3 | Keyboard (IRQ, timer) | Planned (v0.2) |
| M4 | Shell polish | Done |
| M5 | Filesystem | Stubbed |
| M6 | Graphics | VGA done; framebuffer stubbed |
| M7 | GUI (userspace) | Stubbed |
| M8 | Networking | Planned |

## Next (v0.2)

- Memory manager improvements beyond bump allocator
- Interrupt-driven keyboard and PIT timer
- Driver framework
- VFS + FAT32, load apps from disk
- Userspace foundation

## Requirements

- WSL Ubuntu (or native Linux)
- NASM, GCC (32-bit), LD, QEMU

See [`docs/build-instructions.md`](docs/build-instructions.md).
