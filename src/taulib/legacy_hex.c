#include "globals.h"

const char hex_chars[] = "0123456789ABCDEF";

const char *u8_to_dec(u8 value)
{
    static char buf[4];
    char *p = buf;

    /* Hundreds */
    if (value >= 100) {
        u8 h = 0;
        while (value >= 100) {
            value -= 100;
            h++;
        }
        *p++ = '0' + h;
    }

    /* Tens */
    if (value >= 10 || p != buf) {
        u8 t = 0;
        while (value >= 10) {
            value -= 10;
            t++;
        }
        *p++ = '0' + t;
    }

    /* Ones */
    *p++ = '0' + value;
    *p = '\0';

    return buf;
}

u8 dec_to_u8(const char *s)
{
    u8 value = 0;

    while (*s >= '0' && *s <= '9') {
        u8 digit = *s - '0';

        /* value = value * 10 + digit */
        value = (value << 3) + (value << 1) + digit;

        /* Clamp to 255 */
        if (value < digit)
            return 255;

        s++;
    }

    return value;
}

const char *u16_to_hex(u16 value)
{
    static char buf[5];   /* max "FFFF" + '\0' */
    char *p = buf;
    int started = 0;

    for (int shift = 12; shift >= 0; shift -= 4) {
        u8 nibble = (value >> shift) & 0xF;

        if (nibble || started || shift == 0) {
            started = 1;
            *p++ = (nibble < 10)
                   ? ('0' + nibble)
                   : ('A' + nibble - 10);
        }
    }

    *p = '\0';
    return buf;
}

u16 hex_to_u16(const char *s)
{
    u16 value = 0;

    while (1) {
        u8 digit;

        if (*s >= '0' && *s <= '9')
            digit = *s - '0';
        else if (*s >= 'A' && *s <= 'F')
            digit = *s - 'A' + 10;
        else if (*s >= 'a' && *s <= 'f')
            digit = *s - 'a' + 10;
        else
            break;

        /* value = value * 16 + digit */
        u16 prev = value;
        value = (value << 4) | digit;

        /* Clamp on overflow */
        if (value < prev)
            return 0xFFFF;

        s++;
    }

    return value;
}


char *hex_to_u32(u32 value)
{
    static char hex[11];
    hex[0] = '0';
    hex[1] = 'x';
    for (int i = 0; i < 8; i++) 
    {
        hex[9 - i] = hex_chars[value & 0xF];
        value >>= 4;
    }
    hex[10] = '\0';
    return hex;
}

u8 hex_to_u8(const char *hex)
{
    u8 value = 0;
    for (int i = 0; i < 2; i++) 
    {
        value <<= 4;
        if (hex[i] >= '0' && hex[i] <= '9')
            value |= (hex[i] - '0');
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            value |= (hex[i] - 'A' + 10);
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            value |= (hex[i] - 'a' + 10);
        else
            return 0;
    }
    return value;
}