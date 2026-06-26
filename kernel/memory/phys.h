#ifndef FYNOS_PHYS_H
#define FYNOS_PHYS_H

#include "types.h"

/* Initialize the physical bump allocator. */
void phys_init(void);

/* Allocate size bytes from the physical pool. Returns NULL on exhaustion. */
void *phys_alloc(size_t size);

/* Return remaining free bytes in the physical pool. */
size_t phys_free_bytes(void);

#endif
