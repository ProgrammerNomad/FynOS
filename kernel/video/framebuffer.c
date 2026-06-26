#include "video/framebuffer.h"

int framebuffer_init(framebuffer_t *fb)
{
    if (fb) {
        fb->address = NULL;
        fb->width   = 0;
        fb->height  = 0;
        fb->pitch   = 0;
    }
    return -1;
}

void framebuffer_put_pixel(framebuffer_t *fb, uint32_t x, uint32_t y, uint32_t color)
{
    (void)fb;
    (void)x;
    (void)y;
    (void)color;
}
