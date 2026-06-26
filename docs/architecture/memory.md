# Memory Architecture

> Status: **v0.2 - heap + identity paging**

## Overview

FynOS memory management uses a physical bump allocator, a simple heap free-list, and identity-mapped paging for the low 4 MB.

## Physical Bump Allocator (v0.1)

**Module:** `kernel/memory/phys.c`

- Pool at `0x00100000`, 1 MB
- Allocate-only; used by heap for new blocks

## Heap (v0.2)

**Module:** `kernel/memory/heap.c`

```c
void heap_init(void);
void *kmalloc(size_t size);
void kfree(void *ptr);
size_t heap_free_bytes(void);
int heap_self_test(void);
```

- Singly-linked free-list; no coalescing or `realloc`
- Each allocation: `heap_block_t` header + user bytes from `phys_alloc`

## Paging (v0.2)

**Module:** `kernel/memory/paging.c`

- Identity maps first 4 MB (one PD entry + one PT)
- Page faults (IRQ 14) call `panic("Page fault")`

## Memory Map

```
0x00001000 - 0x000FFFFF  Kernel image
0x00090000 - 0x0009FFFF  Kernel stack
0x000B8000 - 0x000B8FA0  VGA text buffer
0x00100000 - 0x001FFFFF  Physical / heap pool
```

## Future (v0.3+)

- Higher-half or per-process page tables
- Heap improvements (coalescing, slabs)

## Rules

- Shell reports memory via `mem` command APIs only
- Scheduler must not map physical pages directly (future)
