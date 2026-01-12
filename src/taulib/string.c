#include "globals.h"
#include <stddef.h>

u32 strlen(const char *s) 
{
    const char *p = s;
    while (*p) p++;
    return (u32)(p - s);
}

u32 strnlen(const char *s, u32 maxlen) 
{
    u32 i = 0;
    while (i < maxlen && s[i]) i++;
    return i;
}

char *strcpy(char *dest, const char *src) 
{
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
}

char *strncpy(char *dest, const char *src, u32 n) 
{
    u32 i;
    for (i = 0; i < n && src[i]; i++)
        dest[i] = src[i];
    for (; i < n; i++)
        dest[i] = '\0';
    return dest;
}

char *strcat(char *dest, const char *src) 
{
    char *d = dest;
    while (*d) d++;
    while ((*d++ = *src++));
    return dest;
}

char *strncat(char *dest, const char *src, u32 n) 
{
    char *d = dest;
    while (*d) d++;
    u32 i;
    for (i = 0; i < n && src[i]; i++)
        d[i] = src[i];
    d[i] = '\0';
    return dest;
}

int strcmp(const char *s1, const char *s2) 
{
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

int strncmp(const char *s1, const char *s2, u32 n) 
{
    u32 i = 0;
    for (; i < n; i++) {
        if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
            return (unsigned char)s1[i] - (unsigned char)s2[i];
    }
    return 0;
}

void *memcpy(void *dest, const void *src, u32 n) 
{
    unsigned char *d = dest;
    const unsigned char *s = src;
    for (u32 i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}

void *memset(void *s, int c, u32 n) 
{
    unsigned char *p = s;
    for (u32 i = 0; i < n; i++)
        p[i] = (unsigned char)c;
    return s;
}

int memcmp(const void *s1, const void *s2, u32 n) 
{
    const unsigned char *p1 = s1, *p2 = s2;
    for (u32 i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return p1[i] - p2[i];
    }
    return 0;
}

char *strstr(const char *haystack, const char *needle) 
{
    if (!haystack || !needle) return NULL;

    if (*needle == '\0') return (char *)haystack;

    for (const char *h = haystack; *h; ++h) 
    {
        const char *hi = h;
        const char *ni = needle;

        while (*hi && *ni && (*hi == *ni)) 
        {
            ++hi;
            ++ni;
        }

        if (*ni == '\0') 
        {
            return (char *)h;
        }
    }

    return NULL;
}


char *strtok(char *str, const char *delim) {
    static char *strtok_saveptr = NULL;
    char *start;

    if (str)
        strtok_saveptr = str;
    else if (!strtok_saveptr)
        return NULL;

    start = strtok_saveptr;
    while (*start) {
        const char *d = delim;
        bool match = false;
        while (*d) {
            if (*start == *d) {
                match = true;
                break;
            }
            d++;
        }
        if (!match)
            break;
        start++;
    }

    if (*start == '\0') {
        strtok_saveptr = NULL;
        return NULL;
    }

    char *end = start;
    while (*end) {
        const char *d = delim;
        bool match = false;
        while (*d) {
            if (*end == *d) {
                match = true;
                break;
            }
            d++;
        }
        if (match)
            break;
        end++;
    }

    if (*end) {
        *end = '\0';
        strtok_saveptr = end + 1;
    } else {
        strtok_saveptr = NULL;
    }

    return start;
}


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
