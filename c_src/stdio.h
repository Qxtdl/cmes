/*
    This manages getting input from the user,
    and outputting to the TTY console.
*/

#ifndef STDIO_H
#define STDIO_H

#include "globals.h"
#include "memorymap.h"

#define GETS_BUFSIZE 128

void putc(char c);

char *gets(void)
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
                *TTY_LOC = (*TTY_LOC - 1);
                *TTY_CHAR = ' ';
                continue;
            }
            putc(scancode);
            input[i++] = scancode;
        }
    }
}

void putc(char c)
{
    bool newline = false;
    if (c == '\n')
    {
        *TTY_LOC = ((*TTY_LOC + 32) & 0b11100000);
        newline = true;
        *TTY_CHAR = c;
        return;
    }
    if (!newline)
        (*TTY_LOC)++;;
    *TTY_CHAR = c;
    *TTY_WRITE = true;
}

void puts(const char *str)
{
    u8 i = 0;
    while (str[i] != '\0')
    {
        bool newline = false;
        if (str[i] == '\n' || *TTY_LOC == 255)
        {
            *TTY_LOC = ((*TTY_LOC + 32) & 0b11100000);
            newline = true;
        }
        if (!newline)
            (*TTY_LOC)++;;
        *TTY_CHAR = str[i++];
        *TTY_WRITE = true;
    }
}


#endif // STDIO_H