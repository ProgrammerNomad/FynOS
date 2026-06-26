# Boot Architecture

> Status: **Implemented (BIOS)** - UEFI planned

## Overview

FynOS boots via a multi-stage BIOS loader, switching from 16-bit real mode to 32-bit protected mode before handing control to the C kernel.

## Boot Chain (BIOS)

```
BIOS -> boot.asm (0x7C00) -> stage2.asm (0x7E00) -> kernel (0x1000)
```

### Stage 1 - `boot/bios/boot.asm`

- Loaded by BIOS at `0x7C00`
- Sets up segments and stack
- Loads stage 2 from disk sector 2 to `0x7E00`
- Jumps to stage 2

### Stage 2 - `boot/bios/stage2.asm`

- Loads kernel from disk (sectors 3+, up to 32 sectors)
- Enables A20 line
- Sets up GDT, switches to 32-bit protected mode
- Sets stack at `0x90000`
- Jumps to kernel at `0x1000`

## Memory Map (Boot)

```
0x00007C00 - 0x00007DFF  Stage 1 bootloader
0x00007E00 - 0x00007FFF  Stage 2 bootloader
0x00001000 - 0x0000FFFF  Kernel code and data
0x00090000 - 0x0009FFFF  Stack
0x000B8000 - 0x000B8FA0  VGA text buffer
```

## Disk Layout

| Sector | Content |
|--------|---------|
| 1 | Stage 1 boot sector |
| 2 | Stage 2 loader |
| 3+ | Kernel binary |

## UEFI (Planned)

- Directory: `boot/uefi/`
- Will become primary boot path before desktop work
- BIOS retained for learning and QEMU simplicity

## Design Decisions

- Assembly only in `boot/` - no C in boot chain
- Kernel loaded as flat binary at fixed address `0x1000`
- A20 enabled before protected mode switch
- Minimal IDT installed in kernel (`kernel/cpu/idt.c`) before enabling IRQs

## References

- [OSDev Wiki - Boot Sequence](https://wiki.osdev.org/Boot_Sequence)
- [OSDev Wiki - A20 Line](https://wiki.osdev.org/A20_Line)
