#include "memory/paging.h"
#include "types.h"

#define PAGE_PRESENT   0x001
#define PAGE_WRITE     0x002
#define PAGE_FLAGS     (PAGE_PRESENT | PAGE_WRITE)
#define IDENTITY_MB    4

static uint32_t page_directory[1024] __attribute__((aligned(4096)));
static uint32_t page_table[1024]   __attribute__((aligned(4096)));

void paging_init(void)
{
    uint32_t i;

    for (i = 0; i < 1024; i++) {
        page_table[i] = (i * 4096) | PAGE_FLAGS;
        page_directory[i] = 0;
    }

    page_directory[0] = ((uint32_t)page_table) | PAGE_FLAGS;

    __asm__ volatile(
        "mov %0, %%cr3\n"
        "mov %%cr0, %%eax\n"
        "or $0x80000000, %%eax\n"
        "mov %%eax, %%cr0"
        :
        : "r"(page_directory)
        : "eax");
}
