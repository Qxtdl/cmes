#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(const char *s) 
{
    const char *p = s;
    while (*p) p++;
    return (size_t)(p - s);
}

size_t strnlen(const char *s, size_t maxlen) 
{
    size_t i = 0;
    while (i < maxlen && s[i]) i++;
    return i;
}

char *strcpy(char *dest, const char *src) 
{
    char *d = dest;
    while ((*d++ = *src++));
    return dest;
}

char *strncpy(char *dest, const char *src, size_t n) 
{
    size_t i;
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

char *strncat(char *dest, const char *src, size_t n) 
{
    char *d = dest;
    while (*d) d++;
    size_t i;
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

int strncmp(const char *s1, const char *s2, size_t n) 
{
    size_t i = 0;
    for (; i < n; i++) {
        if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
            return (unsigned char)s1[i] - (unsigned char)s2[i];
    }
    return 0;
}

void *memcpy(void *dest, const void *src, size_t n) 
{
    unsigned char *d = dest;
    const unsigned char *s = src;
    for (size_t i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}

void *memset(void *s, int c, size_t n) 
{
    unsigned char *p = s;
    for (size_t i = 0; i < n; i++)
        p[i] = (unsigned char)c;
    return s;
}

int memcmp(const void *s1, const void *s2, size_t n) 
{
    const unsigned char *p1 = s1, *p2 = s2;
    for (size_t i = 0; i < n; i++) {
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
            asm volatile ("ebreak");
            return (char *)h;
        }
    }

    return NULL;
}

const char hex_chars[] = "0123456789ABCDEF";

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

#endif // STRING_H
