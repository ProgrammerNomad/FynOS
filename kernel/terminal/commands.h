#ifndef FYNOS_COMMANDS_H
#define FYNOS_COMMANDS_H

/* Parse and run one shell command line. Returns 0 if handled, 1 if unknown. */
int shell_dispatch(const char *line);

#endif
