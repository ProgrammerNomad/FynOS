#ifndef FYNOS_VFS_H
#define FYNOS_VFS_H

#include "types.h"

typedef struct vfs_node vfs_node_t;

struct vfs_node {
    const char *name;
    int (*read)(vfs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buf);
    vfs_node_t *(*finddir)(vfs_node_t *node, const char *name);
};

/* Initialize the VFS layer (v0.2 foundation). */
void vfs_init(void);

/* Return the root VFS node, or NULL if not mounted. */
vfs_node_t *vfs_root(void);

#endif
