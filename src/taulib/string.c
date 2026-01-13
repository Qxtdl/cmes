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

u32 hex_str_to_u32(const char *hex)
{
    u32 value = 0;

    for (; *hex; hex++) {
        value <<= 4;

        if (*hex >= '0' && *hex <= '9')
            value |= (*hex - '0');
        else if (*hex >= 'a' && *hex <= 'f')
            value |= (*hex - 'a' + 10);
        else if (*hex >= 'A' && *hex <= 'F')
            value |= (*hex - 'A' + 10);
        else
            return 0;
    }

    return value;
}