#ifndef FYNOS_LOGGER_H
#define FYNOS_LOGGER_H

void boot_stage(unsigned int stage);
void log_info(const char *msg);
void log_warn(const char *msg);
void log_error(const char *msg);

#endif
