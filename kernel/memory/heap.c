#include "memory/heap.h"
#include "memory/phys.h"

typedef struct heap_block {
    size_t            size;
    struct heap_block *next;
} heap_block_t;

static heap_block_t *heap_free_list = NULL;

static size_t align_up(size_t n, size_t align)
{
    return (n + align - 1) & ~(align - 1);
}

void heap_init(void)
{
    heap_free_list = NULL;
}

static heap_block_t *block_from_ptr(void *ptr)
{
    return (heap_block_t *)((uint8_t *)ptr - sizeof(heap_block_t));
}

void *kmalloc(size_t size)
{
    heap_block_t *block;
    heap_block_t *prev;
    heap_block_t *cur;
    size_t need;
    void *user_ptr;

    if (size == 0) {
        return NULL;
    }

    need = align_up(size, 4);

    prev = NULL;
    cur = heap_free_list;
    while (cur != NULL) {
        if (cur->size >= need) {
            if (prev == NULL) {
                heap_free_list = cur->next;
            } else {
                prev->next = cur->next;
            }
            user_ptr = (void *)((uint8_t *)cur + sizeof(heap_block_t));
            return user_ptr;
        }
        prev = cur;
        cur = cur->next;
    }

    block = (heap_block_t *)phys_alloc(sizeof(heap_block_t) + need);
    if (block == NULL) {
        return NULL;
    }

    block->size = need;
    block->next = NULL;
    user_ptr = (void *)((uint8_t *)block + sizeof(heap_block_t));
    return user_ptr;
}

void kfree(void *ptr)
{
    heap_block_t *block;

    if (ptr == NULL) {
        return;
    }

    block = block_from_ptr(ptr);
    block->next = heap_free_list;
    heap_free_list = block;
}

size_t heap_free_bytes(void)
{
    size_t total = 0;
    heap_block_t *cur = heap_free_list;

    while (cur != NULL) {
        total += cur->size;
        cur = cur->next;
    }
    return total;
}

int heap_self_test(void)
{
    void *a;
    void *b;

    a = kmalloc(64);
    if (a == NULL) {
        return -1;
    }

    b = kmalloc(32);
    if (b == NULL) {
        kfree(a);
        return -1;
    }

    kfree(a);
    kfree(b);

    a = kmalloc(32);
    if (a == NULL) {
        return -1;
    }
    kfree(a);

    return 0;
}
