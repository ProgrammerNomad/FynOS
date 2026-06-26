# Memory Architecture

> Status: **v0.1 - bump allocator implemented**

## Overview

FynOS memory management starts with a simple physical bump allocator and will evolve toward paging and virtual memory.

## v0.1 - Physical Bump Allocator

**Module:** `kernel/memory/phys.c` + `phys.h`

- Allocates from a fixed region starting at `0x00100000` (1 MB)
- No free - allocate-only for v0.1
- Used by kernel subsystems for temporary buffers

### API

```c
void phys_init(void);
void *phys_alloc(size_t size);   /* Returns NULL on exhaustion */
size_t phys_free_bytes(void);    /* Remaining bytes */
```

## Memory Map (v0.1)

```
0x00000000 - 0x000003FF  Real-mode IVT (unused in PM)
0x00001000 - 0x000FFFFF  Kernel image
0x00100000 - 0x001FFFFF  Bump allocator pool (1 MB)
0x00090000 - 0x0009FFFF  Kernel stack
0x000B8000 - 0x000B8FA0  VGA text buffer
```

## Future (v0.2+)

- Heap allocator with free (`kernel/memory/heap.c`)
- Page directory and paging (`kernel/memory/paging.c`)
- Virtual address space per process

## Rules

- Scheduler never maps physical memory directly - uses memory subsystem APIs
- Shell reports memory via syscall/API, never reads hardware registers for RAM size (v0.1 uses static pool size)
