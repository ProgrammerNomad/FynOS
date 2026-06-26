# FynOS Design Philosophy

Principles that guide every decision in FynOS.

## Core Principles

- **Learn by building.** Understand every subsystem by implementing it from first principles.
- **Keep every subsystem simple.** Complexity is earned, not assumed.
- **No magic.** If something happens, the code and docs must explain why.
- **One way to build.** Linux/WSL + `make`. No duplicated build logic.
- **One kernel.** C for the kernel; assembly reserved for bootloaders and CPU-specific routines only.
- **Documentation is part of the source code.** Docs are written before or alongside code, never after.
- **Architecture before features.** Design documents precede implementation.
- **Every release must boot.** No merge that breaks the boot chain.

## Learning vs Production

FynOS serves two complementary goals - both are intentional:

| Mode | Goal |
|------|------|
| **Educational** | Understand every layer by writing it yourself - scheduler, filesystem, drivers, compositor. |
| **Practical** | Make design choices that keep the OS maintainable and extensible over years. |

We write our own scheduler, filesystem, and drivers **not** because existing implementations don't exist, but because the educational value is in the journey - while the practical value is in clean boundaries that survive growth.

## Project Identity

> FynOS is a modern educational operating system that begins with fewer than 512 bytes of executable code and grows step by step into a complete desktop operating system. Every subsystem is developed from first principles, with clean architecture, comprehensive documentation, and an emphasis on understanding how computers work at every layer - from firmware and bootloaders to graphics, multitasking, filesystems, networking, and graphical applications.

This is **not** an OSDev tutorial that stops at "Hello World." The goal is something people can eventually boot and use daily.

## Architecture Rules

### Vertical stack

```
Applications  ->  System Calls  ->  Kernel Services  ->  Drivers  ->  Hardware
```

Applications cannot access hardware directly. Ever.

### Horizontal boundaries

| Rule | Rationale |
|------|-----------|
| Drivers never call applications | Drivers serve the kernel, not userspace |
| Filesystem never draws graphics | FS handles data; video handles pixels |
| Video driver never manages windows | Window management is userspace (`apps/wm/`) |
| Scheduler never touches hardware directly | Scheduler uses HAL/driver APIs only |
| Terminal/shell never maps physical memory | Shell uses syscalls only |

Violations of these rules are architecture bugs, not shortcuts.

## Professional Discipline

1. Never code before the architecture doc for that subsystem exists (even as a draft).
2. Update the doc when the design changes - doc and code change together.
3. Every PR references the relevant architecture doc section.
4. GitHub Issues track work; Markdown roadmap is the vision.
