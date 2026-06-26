# FynOS

> **Tiny core - endless growth**

FynOS is a modern educational operating system that begins with fewer than 512 bytes of executable code and grows step by step into a complete desktop operating system.

## Vision

Every subsystem is developed from first principles, with clean architecture, comprehensive documentation, and an emphasis on understanding how computers work at every layer - from firmware and bootloaders to graphics, multitasking, filesystems, networking, and graphical applications.

See [`docs/philosophy.md`](docs/philosophy.md) for design principles.

## Current Status

**v0.2.0-alpha** - Kernel foundation: heap, paging, PIT timer, IRQ keyboard.

See [`STATUS.md`](STATUS.md) for details.

## Quick Start

Linux/WSL is the **only** supported development platform:

```bash
# Install toolchain (WSL Ubuntu)
sudo apt update
sudo apt install -y nasm qemu-system-x86 build-essential gcc-multilib

# Build and run
make
make run
```

Windows users: use WSL Ubuntu, then `make`.

## Project Structure

```
FynOS/
|- boot/                    # Firmware entry (ASM only)
|   |- bios/                # Legacy BIOS boot
|   `- uefi/                # UEFI boot (planned)
|- kernel/
|   |- arch/x86/            # Entry, CPU routines
|   |- cpu/                 # GDT, IDT, interrupts
|   |- memory/              # Physical allocator, heap
|   |- drivers/             # Keyboard, disk, PCI, USB
|   |- terminal/            # CLI shell
|   |- video/               # VGA, framebuffer
|   |- fs/                  # VFS, FAT32
|   `- include/             # Shared headers
|- user/                    # Userspace libc (planned)
|- apps/                    # WM, desktop, apps (userspace)
|- libraries/               # Shared userspace libs
|- tools/                   # Host build helpers
|- scripts/                 # Thin wrappers around make
|- docs/                    # Architecture, standards
`- Makefile                 # Single build entry point
```

GUI lives in `apps/` as userspace programs - not in the kernel.

## Roadmap

| Version | Focus |
|---------|-------|
| v0.0 | Boot + Hello - **done** |
| v0.1 | C kernel, memory, keyboard, CLI - **done** |
| v0.2 | Heap, paging, IRQ, PIT timer - **done** |
| v0.3 | Driver registry, ATA, FAT32, VFS |
| v0.4 | Userspace + syscalls + Ring 3 |
| v0.5 | Framebuffer + 2D graphics |
| v0.6 | Window manager + desktop |
| v0.7 | Networking |
| v0.8 | USB + PCI |
| v0.9 | Package manager |
| v1.0 | Stable desktop OS |

## Documentation

- [`docs/philosophy.md`](docs/philosophy.md) - Design principles
- [`docs/coding-standard.md`](docs/coding-standard.md) - Coding rules
- [`docs/architecture/`](docs/architecture/) - Per-subsystem design docs
- [`docs/design-decisions/`](docs/design-decisions/) - Architecture decision records (ADRs)
- [`docs/dev-diary/`](docs/dev-diary/) - Release development notes
- [`docs/build-instructions.md`](docs/build-instructions.md) - Build guide
- [`CONTRIBUTING.md`](CONTRIBUTING.md) - How to contribute

## License

This project is licensed under the MIT License.
See the [LICENSE](LICENSE) file for details.

## Credits

Developed by [Shiv Singh](https://github.com/ProgrammerNomad) ([@ProgrammerNomad](https://github.com/ProgrammerNomad)).

Inspired by [OSDev Wiki](https://wiki.osdev.org/).
