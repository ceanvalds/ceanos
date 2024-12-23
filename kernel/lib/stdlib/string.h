#ifndef __STRING_H__ 
#define __STRING_H__

#include <stdint.h>

size_t strlen(const char *str);
void strcpy(char *dest, const char *src);
char* strncpy(char *dest, const char *src, size_t n);

void strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
char *strchr(const char *str, int c);

char *strrchr(const char *str, int c);
char *strdup(const char *str);
int strcmp(char *s, char *t); 

int strncmp(const char *str1, const char *str2, size_t n);
char *strstr(const char *haystack, const char *needle);
char *strtok(char *str, const char *delim);

int atoi(const char *str);
long atol(const char *str);
long long atoll(const char *str);
long strtol(const char *str, char **endptr, int base);
unsigned long strtoul(const char *str, char **endptr, int base);

#endif 
