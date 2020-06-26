#include <string.h>
#include <stdint.h>

size_t strlen(const char* str)
{
	size_t result = 0;
	while(*str != '\0')
	{
		result++;
		str++;
	}
	return result;	
}

char* strcpy(char* dest, const char* src)
{
	size_t size = strlen(src) + 1;
	
	for(int i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}

	return dest;
}

void* memcpy(void* dst, const void* src, size_t n)
{
	for(int i = 0; i < n; i++)
	{
		((uint8_t*)dst)[i] = ((uint8_t*)src)[i];
	}

	return dst;
}

void* memset(void* b, int c, size_t len)
{
	for(uint8_t* ptr = (uint8_t*)b; ptr < (uint8_t*)b + len; ptr++)
	{
		*ptr = (uint8_t)c;
	}
	return b;
}