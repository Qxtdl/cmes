/*
    This manages getting input from the user,
    and outputting to the TTY console.
*/

#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>

#include "globals.h"
#include "memorymap.h"

char *gets(void);
void puts(const char *str);
void putc(char c);
int printf(const char* format, ...);
char *input(const char *prompt);
void buf_input(const char *prompt, char *buf);

#endif // STDIO_H