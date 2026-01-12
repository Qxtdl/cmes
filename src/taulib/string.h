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
char *hex_to_u32(u32 value);
u8 hex_to_u8(const char *hex);
const char *u8_to_dec(u8 value);
u8 dec_to_u8(const char *s);
const char *u16_to_hex(u16 value);
u16 hex_to_u16(const char *s);

