#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define BUFF_SIZE BUFSIZ
#define s21_NULL ((void *)0)

typedef long unsigned s21_size_t;

void *s21_memset(void *str, int c, s21_size_t n);

char *s21_strncat(char *destination, const char *append, s21_size_t n);

int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

int s21_strlen(char *str);

char *s21_strncpy(char *dest, const char *src, size_t n);

s21_size_t s21_strcspn(const char *str1, const char *str2);

char *s21_strpbrk(const char *str1, const char *str2);

void *s21_memcpy(void *dest, const void *src, s21_size_t n);

void *s21_memchr(const void *str, int c, s21_size_t n);

int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

char *s21_strerror(int errnum);

void s21_errnum_tostring(char *str, int num);

void s21_strcat(char *str1, char *str2);

char *s21_strrchr(const char *str, int c);

char *s21_strtok(char *str, const char *delim);

void *s21_trim(const char *src, const char *trim_chars);

void *s21_to_upper(const char *str);

void *s21_to_lower(const char *str);

void *s21_insert(const char *src, const char *str, size_t start_index);

char *s21_strchr(const char *str, int ch);

char *s21_strstr(const char *haystack, const char *needle);

int s21_sprintf(char *str, const char *format, ...);

