#ifndef FYNOS_ASSERT_H
#define FYNOS_ASSERT_H

#include "debug/panic.h"

#define ASSERT(cond) \
    do { \
        if (!(cond)) { \
            panic("Assertion failed: " #cond); \
        } \
    } while (0)

#endif
