#pragma once

#include "globals.h"
#include <stddef.h>

u32 strlen(const char *s); 
u32 strnlen(const char *s, u32 maxlen); 
char *strcpy(char *dest, const char *src); 
char *strncpy(char *dest, const char *src, u32 n); 
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, u32 n); 
int strcmp(const char *s1, const char *s2); 
int strncmp(const char *s1, const char *s2, u32 n); 
void *memcpy(void *dest, const void *src, u32 n); 
void *memset(void *s, int c, u32 n); 
int memcmp(const void *s1, const void *s2, u32 n); 
char *strstr(const char *haystack, const char *needle); 
char *strtok(char *str, const char *delim);
u32 hex_str_to_u32(const char *hex);

