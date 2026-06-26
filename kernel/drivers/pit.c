#include "drivers/pit.h"
#include "cpu/io.h"

#define PIT_CHANNEL0   0x40
#define PIT_COMMAND    0x43
#define PIT_HZ         100
#define PIT_DIVISOR    (1193182 / PIT_HZ)

static volatile uint32_t pit_tick_count = 0;

void pit_init(void)
{
    pit_tick_count = 0;

    outb(PIT_COMMAND, 0x36);
    outb(PIT_CHANNEL0, (uint8_t)(PIT_DIVISOR & 0xFF));
    outb(PIT_CHANNEL0, (uint8_t)((PIT_DIVISOR >> 8) & 0xFF));
}

void pit_irq_handler(void)
{
    pit_tick_count++;
}

uint32_t pit_ticks(void)
{
    return pit_tick_count;
}

uint32_t pit_uptime_seconds(void)
{
    return pit_tick_count / PIT_HZ;
}
