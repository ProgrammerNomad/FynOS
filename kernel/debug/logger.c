#include "debug/logger.h"
#include "debug/serial.h"

static void write_uint_serial(unsigned int n)
{
    char buf[12];
    int i = 0;

    if (n == 0) {
        serial_write_char('0');
        return;
    }

    while (n > 0) {
        buf[i++] = (char)('0' + (n % 10));
        n /= 10;
    }

    while (i > 0) {
        serial_write_char(buf[--i]);
    }
}

void boot_stage(unsigned int stage)
{
    serial_write("BOOT ");
    write_uint_serial(stage);
    serial_write("\n");
}

static void log_prefix(const char *level, const char *msg)
{
    serial_write("[");
    serial_write(level);
    serial_write("] ");
    serial_write(msg);
    serial_write("\n");
}

void log_info(const char *msg)
{
    log_prefix("INFO", msg);
}

void log_warn(const char *msg)
{
    log_prefix("WARN", msg);
}

void log_error(const char *msg)
{
    log_prefix("ERROR", msg);
}
