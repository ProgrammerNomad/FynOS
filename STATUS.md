# FynOS Development Status

## Current Version: v0.1

Interactive C kernel with modular architecture.

## Completed

### v0.0 - Boot + Hello
- 512-byte BIOS boot sector
- "Welcome to FynOS!" message

### v0.1 - Interactive Kernel (in progress)
- Multi-stage BIOS bootloader (protected mode)
- C kernel with modular layout
- VGA text output (`kernel/video/vga.c`)
- Physical bump allocator (`kernel/memory/phys.c`)
- PS/2 keyboard driver (`kernel/drivers/keyboard.c`)
- CLI shell (`kernel/terminal/shell.c`)
- IDT and interrupt handling (`kernel/cpu/idt.c`)
- Single build system: WSL/Linux + `make`

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
| M1 | C Kernel | Done |
| M2 | Memory | Done |
| M3 | Keyboard | Done |
| M4 | Shell | Done |
| M5 | Filesystem | Stubbed |
| M6 | Graphics | VGA done; framebuffer stubbed |
| M7 | GUI (userspace) | Stubbed |
| M8 | Networking | Planned |

## Next

- v0.2: VFS + FAT32, load apps from disk
- UEFI boot path (`boot/uefi/`)
- Framebuffer and 2D graphics

## Requirements

- WSL Ubuntu (or native Linux)
- NASM, GCC (32-bit), LD, QEMU

See [`docs/build-instructions.md`](docs/build-instructions.md).
