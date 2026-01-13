/*
    This manages getting input from the user,
    and outputting to the TTY console.
*/

#include <stdarg.h>

#include "globals.h"
#include "memorymap.h"
#include "string.h"

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
            if (scancode == ENTER_KEY || i == GETS_BUFSIZE - 1)
            {
                input[i] = '\0';
                return input;
            }
            // Backspace support
            if (scancode == '\b' && i > 0)
            {
                i--;
                *TTY_CHAR = '\0';
                *TTY_WRITE = true;
				input[i] = '\0';
                continue;
            }
            putc(scancode);
            input[i++] = scancode;
        }
    }
    putc('\n');
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

int printf(const char* format, ...)
{
	va_list parameters;
	va_start(parameters, format);

	while (*format != '\0') {
		if (*format != '%')
			putc(*format);
		else {
			// this char is format specifier
			const char *format_specifier = format + 1;

			if (!strncmp(format_specifier, "s", 1)) {
				format = format_specifier;
				const char *str = va_arg(parameters, const char *);
				puts(str);
			}
			if (!strncmp(format_specifier, "c", 1)) {
				format = format_specifier;
				const char ch = (char)va_arg(parameters, int);
				putc(ch);
			}
			if (!strncmp(format_specifier, "x", 1)) {
				format = format_specifier;
				printf("$");
				
				u32 n = va_arg(parameters, u32);

				for (int i = 0; i < 8; i++) {
					u8 digit = (n >> (7 - i) * 4) & 0xF;
					// if (digit < 10) {
					// 	tty_putchar(digit | 0x20);
					// } else tty_putchar(digit | 0x40);
					switch (digit) {
						case 0x0: putc('0'); break;
						case 0x1: putc('1'); break;
						case 0x2: putc('2'); break;
						case 0x3: putc('3'); break;
						case 0x4: putc('4'); break;
						case 0x5: putc('5'); break;
						case 0x6: putc('6'); break;
						case 0x7: putc('7'); break;
						case 0x8: putc('8'); break;
						case 0x9: putc('9'); break;
						case 0xA: putc('A'); break;
						case 0xB: putc('B'); break;
						case 0xC: putc('C'); break;
						case 0xD: putc('D'); break;
						case 0xE: putc('E'); break;
						case 0xF: putc('F'); break;
					}
				}
                
			}
            if (!strncmp(format_specifier, "hx", 2)) {
				format = format_specifier;
				printf("$");
				
				u32 n = va_arg(parameters, u32);

				for (int i = 0; i < 4; i++) {
					u8 digit = (n >> (7 - i) * 4) & 0xF;
					// if (digit < 10) {
					// 	tty_putchar(digit | 0x20);
					// } else tty_putchar(digit | 0x40);
					switch (digit) {
						case 0x0: putc('0'); break;
						case 0x1: putc('1'); break;
						case 0x2: putc('2'); break;
						case 0x3: putc('3'); break;
						case 0x4: putc('4'); break;
						case 0x5: putc('5'); break;
						case 0x6: putc('6'); break;
						case 0x7: putc('7'); break;
						case 0x8: putc('8'); break;
						case 0x9: putc('9'); break;
						case 0xA: putc('A'); break;
						case 0xB: putc('B'); break;
						case 0xC: putc('C'); break;
						case 0xD: putc('D'); break;
						case 0xE: putc('E'); break;
						case 0xF: putc('F'); break;
					}
				}
                
			}
		}
		format++;
	}

	return 0; // no error
}

char *input(const char *prompt) {
    putc('\n');
    puts(prompt);
    putc(' ');
    char *input = gets();
    putc('\n');
    return input;
}

void buf_input(const char *prompt, char *buf) {
    putc('\n');
    puts(prompt);
    putc (' ');
    char *input = gets();
    strcpy(buf, input);
    return;
}
