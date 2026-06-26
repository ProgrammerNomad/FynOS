# Architecture Decision Records

Each ADR documents a significant design choice.

## Format

1. **Problem** - what needed deciding
2. **Options** - alternatives considered
3. **Decision** - what we chose
4. **Why** - rationale

## Index

| ADR | Title |
|-----|-------|
| [0001](0001-use-c-kernel.md) | C kernel with ASM for boot/arch only |
| [0002](0002-use-vga-text.md) | VGA text mode first |
| [0003](0003-use-fat32-first.md) | FAT32 for first filesystem (v0.3) |
| [0004](0004-use-make-only.md) | Linux/WSL + Makefile only |
| [0005](0005-simple-heap-free-list.md) | Simple heap free-list for v0.2 |
| [0006](0006-identity-map-paging.md) | Identity-map first 4 MB for paging |
| [0007](0007-serial-debug-first.md) | COM1 serial + QEMU run-debug |
| [0008](0008-irq-stack-frame.md) | IRQ ISR stack frame (OSDev layout) |
