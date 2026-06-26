#include "fs/vfs.h"

static vfs_node_t *root_node = NULL;

void vfs_init(void)
{
    root_node = NULL;
}

vfs_node_t *vfs_root(void)
{
    return root_node;
}
