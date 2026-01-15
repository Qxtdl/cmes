#include "../../taulib/globals.h"
#include "../../taulib/string.h"
#include "../../taulib/stdio.h"
#include "legacy/legacy_shell.h"

#include "commands/clear.h"
#include "commands/cat.h"
#include "commands/run.h"
#include "commands/ls.h"
#include "commands/malloc.h"
#include "commands/hex.h"
#include "commands/dump.h"
#include "commands/wtxt.h"
#include "commands/dskfmt.h"
#include "commands/mkf.h"
#include "commands/diskstat.h"
#include "commands/cd.h"

#define MAX_COMMANDS 64
#define MAX_COMMAND_NAME 16

#define MAX_ARGC 8

u8 argc;
char *argv[MAX_ARGC];

struct {
    const char *name;
    void (*func)(int, char *[]);
} commands[MAX_COMMANDS] = {
    {"clear", clear},
    {"cat", cat},
    {"run", run},
    {"ls", ls},
    {"malloc", c_malloc},
    {"hex", hex},
    {"dump", dump},
    {"wtxt", wtxt},
    {"dskfmt", diskfmt},
    {"mkf", mkf},
    {"cd", cd},
    {"diskstat", diskstat},
    {NULL, NULL}
};

static inline void dispatch_command(char *command) {
    if (!strcmp(command, "l")) {
        clear_tty
        legacy_shell();
        return;
    }
    if (!strcmp(command, "help")) {
        clear_tty
        putc('\n');
        for (u32 i = 0; i < MAX_COMMANDS; i++) {
            if (!commands[i].name) {
                return;
            }
            puts(commands[i].name);
            putc('\n');
        }
        return;
    }

    argc = 0;
    argv[0] = NULL;

    char *command_name = strtok(command, " ");
    char *arg = strtok(NULL, " ");

    while (arg != NULL && argc < MAX_ARGC) {
        argv[argc++] = arg;
        arg = strtok(NULL, " ");
    }

    argv[argc] = NULL;

    for (u32 i = 0; i < MAX_COMMANDS; i++) {
        if (!commands[i].name) break;
        if (!strcmp(command_name, commands[i].name))
        {
            putc('\n');
            commands[i].func(argc, argv);
        }
    }
}

void shell(void) {
    puts(">");
    char *command = gets();
    dispatch_command(command);
    putc('\n');
}

void shell_loop(void) {
    while (1)
        shell();
}