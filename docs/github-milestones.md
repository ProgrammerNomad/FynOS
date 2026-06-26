# GitHub Project Setup

This document defines Milestones M0-M8 and their issues for GitHub Project tracking.

## Setup (when `gh` CLI is available)

```bash
chmod +x scripts/setup-github.sh
./scripts/setup-github.sh
```

Or create milestones and issues manually using the definitions below.

## Project Board Columns

```
Backlog -> Design -> In Progress -> Review -> Done
```

## Milestones

### M0 - Bootloader

| Issue | Title | Status |
|-------|-------|--------|
| # | Multi-stage BIOS boot sector | Done |
| # | Stage 2 protected mode switch | Done |
| # | Load sufficient kernel sectors (32+) | Done |
| # | Enable A20 line in stage 2 | Done |

### M1 - C Kernel

| Issue | Title | Status |
|-------|-------|--------|
| # | Unify build on C kernel only | Done |
| # | Remove ASM kernel and build.bat | Done |
| # | Modular kernel layout | Done |
| # | objcopy flat binary output | Done |

### M2 - Memory

| Issue | Title | Status |
|-------|-------|--------|
| # | Physical bump allocator | Done |
| # | phys_alloc / phys_free_bytes API | Done |
| # | `mem` shell command | Done |

### M3 - Keyboard

| Issue | Title | Status |
|-------|-------|--------|
| # | PS/2 keyboard driver | Done |
| # | PIC remapping and IRQ 1 | Done |
| # | Scancode to ASCII translation | Done |

### M4 - Shell

| Issue | Title | Status |
|-------|-------|--------|
| # | Interactive readline loop | Done |
| # | Commands: help, clear, mem, version | Done |

### M5 - Filesystem

| Issue | Title | Status |
|-------|-------|--------|
| # | VFS layer foundation | Stubbed |
| # | FAT32 read-only driver | Planned |
| # | ATA/IDE disk driver | Planned |

### M6 - Graphics

| Issue | Title | Status |
|-------|-------|--------|
| # | VGA text mode driver | Done |
| # | Framebuffer driver (VBE/GOP) | Stubbed |
| # | 2D drawing primitives | Planned |

### M7 - GUI (Userspace)

| Issue | Title | Status |
|-------|-------|--------|
| # | Window manager app (apps/wm/) | Stubbed |
| # | Desktop shell app (apps/desktop/) | Stubbed |
| # | Mouse driver | Planned |

### M8 - Networking

| Issue | Title | Status |
|-------|-------|--------|
| # | Ethernet driver | Planned |
| # | IPv4 + ARP | Planned |
| # | TCP/IP stack | Planned |
