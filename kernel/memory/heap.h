#ifndef FYNOS_HEAP_H
#define FYNOS_HEAP_H

#include "types.h"

void heap_init(void);
void *kmalloc(size_t size);
void kfree(void *ptr);
size_t heap_free_bytes(void);

/* Smoke test kmalloc/kfree; returns 0 on success. */
int heap_self_test(void);

#endif
