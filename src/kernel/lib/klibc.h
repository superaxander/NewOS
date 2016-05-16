#ifndef _KLIBC_H_
#define _KLIBC_H_
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char*);
void* memset(void*, int, size_t);
void* memcpy(void* restrict destinationptr, const void* restrict sourceptr, size_t size);
int memcmp(const void* ptr1, const void* ptr2, size_t size);
void* memmove(void* destinationptr, const void* sourceptr, size_t size);

#endif
