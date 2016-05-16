#ifndef _KLIBC_H_
#define _KLIBC_H_
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char*);
void* memset(void*, int, size_t);
void* memcpy(void* restrict, const void* restrict, size_t);
int memcmp(const void*, const void*, size_t);
void* memmove(void*, const void*, size_t );
void outportb (unsigned short, unsigned char);
unsigned char inportb (unsigned short);
char *inttostr(int, int, char[128]);
void strcpy(char[], const char[]);
void disable_interrupts();
void restore_interrupts();
#endif
