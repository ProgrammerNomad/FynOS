#include "memory/phys.h"

#define PHYS_POOL_BASE  0x00100000
#define PHYS_POOL_SIZE  0x00100000

static uint32_t phys_next = PHYS_POOL_BASE;
static uint32_t phys_end  = PHYS_POOL_BASE + PHYS_POOL_SIZE;

void phys_init(void)
{
    phys_next = PHYS_POOL_BASE;
}

void *phys_alloc(size_t size)
{
    uint32_t aligned;
    void *ptr;

    aligned = (phys_next + 3) & (uint32_t)~3;
    if (aligned + size > phys_end) {
        return NULL;
    }
    ptr = (void *)aligned;
    phys_next = aligned + (uint32_t)size;
    return ptr;
}

size_t phys_free_bytes(void)
{
    return (size_t)(phys_end - phys_next);
}
