#ifndef FYNOS_PANIC_H
#define FYNOS_PANIC_H

/* Print a kernel panic message and halt. Does not return. */
void panic(const char *message) __attribute__((noreturn));

void panic_at(const char *message, const char *file, int line) __attribute__((noreturn));

#define PANIC(msg) panic_at((msg), __FILE__, __LINE__)

#endif
