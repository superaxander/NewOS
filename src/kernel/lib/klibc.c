#include "kernel/lib/klibc.h"

//Thanks Meaty Skeleton (sortie and other contributors to its wiki page)

size_t strlen(const char* str) {
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

void* memset(void* bufferptr, int value, size_t size)
{
	unsigned char* buffer = (unsigned char*) bufferptr;
	for ( size_t i = 0; i < size; i++ )
		buffer[i] = (unsigned char) value;
	return bufferptr;
}

void* memcpy(void* restrict destinationptr, const void* restrict sourceptr, size_t size)
{
	unsigned char* destination = (unsigned char*) destinationptr;
	const unsigned char* source = (const unsigned char*) sourceptr;
	for ( size_t i = 0; i < size; i++ )
		destination[i] = source[i];
	return destinationptr;
}

int memcmp(const void* ptr1, const void* ptr2, size_t size)
{
	const unsigned char* value1 = (const unsigned char*) ptr1;
	const unsigned char* value2 = (const unsigned char*) ptr2;
	for ( size_t i = 0; i < size; i++ )
		if ( value1[i] < value2[i] )
			return -1;
		else if ( value2[i] < value1[i] )
			return 1;
	return 0;
}

void* memmove(void* destinationptr, const void* sourceptr, size_t size)
{
	unsigned char* destination = (unsigned char*) destinationptr;
	const unsigned char* source = (const unsigned char*) sourceptr;
	if ( destination < source )
		for ( size_t i = 0; i < size; i++ )
			destination[i] = source[i];
	else
		for ( size_t i = size; i != 0; i-- )
			destination[i-1] = source[i-1];
	return destinationptr;
}

unsigned char inportb (unsigned short port)
{
	unsigned char return_value;
	__asm__ __volatile__ ("inb %1, %0" : "=a" (return_value) : "dN" (port));
	return return_value;
}

void outportb (unsigned short port, unsigned char data)
{
	__asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

char *inttostr(int num, int base, char buf[128])
{
	char *str = "0123456789ABCDEF";
	int pos = 0;
	if(num==0 || base > 16)
		return "0";

	while(num)
	{
		buf[pos] = str[num % base];
		pos++;
		num /= base;
	}
	buf[pos] = '\0';
	reverse(buf);
	return buf;
}

void strcpy(char dest[], const char source[])
{
	int i = 0;
	while (1)
        {
		dest[i] = source[i];
		if (dest[i] == '\0') break;
			i++;
	}
}

void disable_interrupts()
{
	__asm__ __volatile__ ("cli");
}

void restore_interrupts()
{
	__asm__ __volatile__ ("sti");
}
