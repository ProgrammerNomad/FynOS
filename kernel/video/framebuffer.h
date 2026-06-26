#ifndef FYNOS_FRAMEBUFFER_H
#define FYNOS_FRAMEBUFFER_H

#include "types.h"

typedef struct framebuffer {
    uint32_t *address;
    uint32_t  width;
    uint32_t  height;
    uint32_t  pitch;
} framebuffer_t;

/* Initialize linear framebuffer (v0.3 - stub). Returns 0 on success. */
int framebuffer_init(framebuffer_t *fb);

/* Draw a single pixel (stub). */
void framebuffer_put_pixel(framebuffer_t *fb, uint32_t x, uint32_t y, uint32_t color);

#endif
