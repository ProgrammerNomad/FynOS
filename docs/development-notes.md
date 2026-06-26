# FynOS Development Notes

## Version History

### v0.0 - Boot + Hello (done)

- 512-byte BIOS boot sector (`boot/bios/boot-simple.asm`)
- Prints "Welcome to FynOS!"

### v0.1 - Interactive C Kernel (current)

- Multi-stage BIOS bootloader with A20 and 32-sector kernel load
- C kernel with modular layout
- VGA text (`kernel/video/vga.c`)
- Physical bump allocator (`kernel/memory/phys.c`)
- PS/2 keyboard with IRQ 1 (`kernel/drivers/keyboard.c`)
- CLI shell (`kernel/terminal/shell.c`)
- IDT and PIC (`kernel/cpu/`)

### v0.2 - Storage (stubbed)

- VFS foundation (`kernel/fs/vfs.c`)
- FAT32 stub (`kernel/fs/fat32.c`)

## Boot Process

1. **Stage 1** (`boot/bios/boot.asm`): BIOS loads at `0x7C00`, loads stage 2
2. **Stage 2** (`boot/bios/stage2.asm`): Loads 32 kernel sectors, enables A20, protected mode
3. **Kernel** (`kernel/arch/x86/entry.asm` -> `kernel_main()`): Initializes subsystems, runs shell

## Memory Map

```
0x00007C00  Stage 1 bootloader
0x00007E00  Stage 2 bootloader
0x00001000  Kernel
0x00090000  Stack
0x000B8000  VGA text buffer
0x00100000  Physical allocator pool (1 MB)
```

## Build

Linux/WSL only:

```bash
make
make run
```

See `docs/build-instructions.md`.

## Architecture Docs

Per-subsystem design: `docs/architecture/`
