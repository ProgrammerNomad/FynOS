# Changelog

All notable changes to FynOS are documented in this file.

## [0.2.0-alpha] - 2026-06-26

Kernel foundation release. Milestones M2 (memory) and M3 (interrupts) complete.

### Highlights

- Kernel panic handler (`panic.c`) with visible halt screen
- Heap allocator: `kmalloc`, `kfree`, simple free-list
- Paging: identity map first 4 MB; page fault calls panic
- PIT timer at 100 Hz; `uptime` shell command
- IRQ-driven keyboard (shell blocks with `hlt` while waiting)
- Regression checklist (`make test`) and architecture decision records

### Shell commands

- `mem` - physical free + heap free (KB)
- `uptime` - seconds since boot

### Known limitations

- No filesystem, userspace, or driver registry yet (v0.3+)
- Simple heap: no coalescing or `realloc`
- Identity map only; no per-process virtual memory

### Next (v0.3)

- Driver registry, ATA, FAT32, VFS, `ls`, `cat`

## [0.1.0-alpha] - 2026-06-26

First interactive kernel release. Milestone M1 (Interactive Kernel) complete.

### Highlights

- Multi-stage BIOS bootloader with protected mode entry
- Modular C kernel (VGA, memory, keyboard, shell, IDT)
- Interactive CLI shell with command table dispatch
- VGA hardware cursor sync
- QEMU floppy boot (`make run` with `-fda`)

### Shell commands

- `help` - list available commands
- `about` - version, copyright, license, and repository URL
- `clear` - clear the screen
- `echo` - print text
- `mem` - show free physical memory
- `version` - show version string

### Known limitations

- No filesystem, multitasking, paging, or userspace
- BIOS + floppy boot only (no UEFI)
- VGA text mode only
- Polling keyboard (IRQ path not used by shell yet)
- VFS and framebuffer are stubbed

### Next (v0.2)

- Memory manager improvements
- Interrupt-driven keyboard and PIT timer
- Driver framework
- VFS + FAT32
- Userspace foundation

[0.2.0-alpha]: https://github.com/ProgrammerNomad/FynOS/releases/tag/v0.2.0-alpha
[0.1.0-alpha]: https://github.com/ProgrammerNomad/FynOS/releases/tag/v0.1.0-alpha
