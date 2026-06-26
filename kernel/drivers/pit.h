#ifndef FYNOS_PIT_H
#define FYNOS_PIT_H

#include "types.h"

void pit_init(void);
void pit_irq_handler(void);
uint32_t pit_ticks(void);
uint32_t pit_uptime_seconds(void);

#endif
