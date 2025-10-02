/*
    This manages getting input from the user,
    and outputting to the TTY console.
*/

#ifndef STDIO_H
#define STDIO_H

#include "globals.h"
#include "memorymap.h"

#define GETS_BUFSIZE 128

char *stdio_gets(void)
{
    static char input[GETS_BUFSIZE];

    u8 i = 0;
    u8 scancode;
    while (1)
    {
        if (*USER_READY)
        {
            scancode = *USER_ASCII;

            // Check wether to end getting input
            if (scancode == '\r' || i == GETS_BUFSIZE - 1)
            {
                input[i] = '\0';
                return input;
            }
            // Backspace support
            if (scancode == '\b' && i > 0)
            {
                i--;
                continue;
            }
            input[i++] = scancode;
        }
    }
}

// May be better to code this in ASM
u8 stdio_puts(const char *str)
{
    u8 i = 0;
    while (str[i] != '\0')
    {
        *TTY_LOC = i;
        *TTY_CHAR = str[i++];
        *TTY_WRITE = true;
    }
    return i;
}

#endif // STDIO_H