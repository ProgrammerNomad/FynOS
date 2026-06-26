#ifndef FYNOS_FAT32_H
#define FYNOS_FAT32_H

#include "types.h"
#include "fs/vfs.h"

/* Mount FAT32 from drive (v0.2 - not yet implemented). Returns 0 on success. */
int fat32_mount(uint8_t drive);

/* Return root VFS node after mount. */
vfs_node_t *fat32_root(void);

#endif
