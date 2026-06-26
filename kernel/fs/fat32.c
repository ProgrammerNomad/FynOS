#include "fs/fat32.h"

int fat32_mount(uint8_t drive)
{
    (void)drive;
    return -1;
}

vfs_node_t *fat32_root(void)
{
    return NULL;
}
