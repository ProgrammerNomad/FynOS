# Filesystem Architecture

> Status: **v0.2 - VFS foundation stubbed**

## Overview

FynOS uses a Virtual File System (VFS) layer with pluggable filesystem drivers. FAT32 is the first practical filesystem.

## VFS Layer - `kernel/fs/vfs.c`

```c
typedef struct vfs_node {
    const char *name;
    int (*read)(vfs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buf);
    int (*write)(vfs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buf);
    vfs_node_t *(*finddir)(vfs_node_t *node, const char *name);
} vfs_node_t;

void vfs_init(void);
vfs_node_t *vfs_root(void);
```

## FAT32 - `kernel/fs/fat32.c` (Planned)

- Read-only initially
- Mount from first partition on ATA disk
- Used to load userspace apps from disk

## Native Filesystem (Future)

- FynFS - native FynOS filesystem for v1.0+

## Rules

- Filesystem never draws graphics
- All file access from userspace goes through syscalls (future)
- Kernel shell (v0.1) does not access filesystem

## Dependencies

- ATA/IDE disk driver (M5)
- Memory allocator for buffers

## References

- [OSDev Wiki - VFS](https://wiki.osdev.org/VFS)
- [OSDev Wiki - FAT](https://wiki.osdev.org/FAT)
