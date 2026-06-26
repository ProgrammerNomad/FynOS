# FynOS Development Status

## Current Version: v0.2.0-alpha

Kernel foundation: panic handler, heap, paging, PIT timer, IRQ keyboard.

## Completed

### v0.1 - Interactive Kernel
- Multi-stage BIOS boot, C kernel, VGA, shell, MIT license

### v0.2 - Kernel Foundation
- `kernel/debug/panic.c` - kernel panic banner + halt
- `kernel/memory/heap.c` - `kmalloc` / `kfree` (simple free-list)
- `kernel/memory/paging.c` - identity map 4 MB, page fault → panic
- `kernel/drivers/pit.c` - 100 Hz timer, `uptime` shell command
- IRQ-driven keyboard (no polling in read path)
- Shell: improved `mem` (physical + heap), `uptime`
- Regression checklist (`make test`) and ADRs in `docs/design-decisions/`

## Build

```bash
make        # Build fynos.img
make run    # Run in QEMU
make test   # Print regression checklist
make clean
```

## Milestones

| Milestone | Scope | Status |
|-----------|-------|--------|
| M0 | Bootloader | Done |
| M1 | Interactive Kernel | Done |
| M2 | Heap + paging | Done |
| M3 | PIT + IRQ keyboard | Done |
| M5 | Filesystem | Stubbed (v0.3) |
| M6 | Graphics | VGA done; framebuffer stubbed |

## Next (v0.3)

- Driver registry
- ATA/IDE driver
- FAT32 + VFS
- Shell: `ls`, `cat`

See [`docs/build-instructions.md`](docs/build-instructions.md).
