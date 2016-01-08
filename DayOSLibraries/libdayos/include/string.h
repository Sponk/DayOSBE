#ifndef STRING_H
#define STRING_H

#include "stddef.h"
#include "stdarg.h"

#ifdef __cplusplus
extern "C" {
#endif

int strcmp(const char* str1, const char* str2);
int strcasecmp(const char* str1, const char* str2);
char* strcat(char* str1, const char* str2);
char* strchr(const char* str, int chr);
int strcoll(const char* str1, const char* str2);
char* strcpy(char* dest, const char* src);
size_t strcspn(const char* s1, const char* s2);
size_t strlen(const char* str);
int strncasecmp(const char* str1, const char* str2, size_t n);
char* strncat(char* src1, const char* src2, size_t n);
int strncmp(const char* str1, const char* str2, size_t n);
char* strncpy(char* dest, const char* src, size_t n);
char* strpbrk(const char* s1, const char* s2);
char* strrchr(const char* s, int c);
size_t strspn(const char* string, const char* spanset);
char* strstr(const char* haystack, const char* needle);
char* strsep(char** stringp, const char* delim);
char* strtok(char* s, const char* delim);
void* memccpy(void* dest, const void* src, int c, size_t n);
void* memcpy(void* dest, const void* src, int n);
void* memset(void* dest, int val, size_t n);
void* memchr(const void* src, int c, size_t n);
int memcmp(const void* srca, const void* srcb, size_t n);
void* memmove(void* dest, const void* src, size_t n);

char* strdup(const char* s);
char* strndup(const char* s, size_t n);
char* strdupa(const char* s);
char* strndupa(const char* s, size_t n);
size_t strxfrm (char* destination, const char* source, size_t num);
char* strerror(int errnum);

#ifdef __cplusplus
}
#endif

#endif
