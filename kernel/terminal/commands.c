#include "terminal/commands.h"
#include "video/vga.h"
#include "memory/phys.h"
#include "memory/heap.h"
#include "drivers/pit.h"
#include "version.h"

#include "types.h"

typedef void (*shell_cmd_fn)(const char *args);

typedef struct {
    const char   *name;
    const char   *help;
    shell_cmd_fn  handler;
} shell_command_t;

static void cmd_help(const char *args);
static void cmd_about(const char *args);
static void cmd_clear(const char *args);
static void cmd_echo(const char *args);
static void cmd_mem(const char *args);
static void cmd_uptime(const char *args);
static void cmd_version(const char *args);

static const shell_command_t shell_commands[] = {
    { "help",    "List available commands", cmd_help },
    { "about",   "System information",      cmd_about },
    { "clear",   "Clear the screen",        cmd_clear },
    { "echo",    "Print text",              cmd_echo },
    { "mem",     "Show free memory",        cmd_mem },
    { "uptime",  "Show uptime in seconds",  cmd_uptime },
    { "version", "Show version string",     cmd_version },
};

static const size_t shell_command_count =
    sizeof(shell_commands) / sizeof(shell_commands[0]);

static int str_equals(const char *a, const char *b)
{
    while (*a && *b) {
        if (*a != *b) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == *b;
}

static void print_uint(uint32_t n)
{
    char buf[12];
    int i = 0;

    if (n == 0) {
        vga_print_char('0');
        return;
    }

    while (n > 0) {
        buf[i++] = (char)('0' + (n % 10));
        n /= 10;
    }

    while (i > 0) {
        vga_print_char(buf[--i]);
    }
}

static void cmd_help(const char *args)
{
    size_t i;

    (void)args;

    vga_print_string("Available commands:\n");
    for (i = 0; i < shell_command_count; i++) {
        vga_print_string("  ");
        vga_print_string(shell_commands[i].name);
        vga_print_string(" - ");
        vga_print_string(shell_commands[i].help);
        vga_print_char('\n');
    }
}

static void cmd_about(const char *args)
{
    (void)args;

    vga_print_string("FynOS ");
    vga_print_string(FYNOS_VERSION);
    vga_print_string("\n\n");
    vga_print_string(FYNOS_COPYRIGHT);
    vga_print_string("\n\nLicensed under the ");
    vga_print_string(FYNOS_LICENSE_NAME);
    vga_print_string("\n\n");
    vga_print_string(FYNOS_REPO_URL);
    vga_print_char('\n');
}

static void cmd_clear(const char *args)
{
    (void)args;
    vga_clear();
}

static void cmd_echo(const char *args)
{
    if (args[0] == '\0') {
        vga_print_char('\n');
        return;
    }

    vga_print_string(args);
    vga_print_char('\n');
}

static void cmd_mem(const char *args)
{
    size_t phys_free;
    size_t heap_free;
    uint32_t phys_kb;
    uint32_t heap_kb;

    (void)args;

    phys_free = phys_free_bytes();
    heap_free = heap_free_bytes();
    phys_kb = (uint32_t)(phys_free / 1024);
    heap_kb = (uint32_t)(heap_free / 1024);

    vga_print_string("Physical free: ");
    print_uint(phys_kb);
    vga_print_string(" KB\nHeap free: ");
    print_uint(heap_kb);
    vga_print_string(" KB\n");
}

static void cmd_uptime(const char *args)
{
    (void)args;

    vga_print_string("Uptime: ");
    print_uint(pit_uptime_seconds());
    vga_print_string(" seconds\n");
}

static void cmd_version(const char *args)
{
    (void)args;

    vga_print_string("FynOS ");
    vga_print_string(FYNOS_VERSION);
    vga_print_char('\n');
}

static void skip_spaces(const char **p)
{
    while (**p == ' ') {
        (*p)++;
    }
}

int shell_dispatch(const char *line)
{
    const char *p = line;
    const char *name_start;
    const char *name_end;
    char name[32];
    size_t name_len;
    size_t i;

    skip_spaces(&p);

    if (*p == '\0') {
        return 0;
    }

    name_start = p;
    while (*p != '\0' && *p != ' ') {
        p++;
    }
    name_end = p;

    name_len = (size_t)(name_end - name_start);
    if (name_len == 0 || name_len >= sizeof(name)) {
        return 1;
    }

    for (i = 0; i < name_len; i++) {
        name[i] = name_start[i];
    }
    name[name_len] = '\0';

    skip_spaces(&p);

    for (i = 0; i < shell_command_count; i++) {
        if (str_equals(name, shell_commands[i].name)) {
            shell_commands[i].handler(p);
            return 0;
        }
    }

    vga_print_string("Unknown command: ");
    vga_print_string(name);
    vga_print_string("\nType 'help' to see available commands.\n");
    return 1;
}
