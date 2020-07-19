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
	size_t div = n / sizeof(uint64_t);
	size_t mod = n % sizeof(uint64_t);
	
	uint64_t* dst_ptr = (uint64_t*)dst;
	uint64_t* src_ptr = (uint64_t*)src;
	for(;dst_ptr != (uint64_t*)dst + div; dst_ptr++, src_ptr++)
	{
		*dst_ptr = *src_ptr;
	}

	for(int i = 0; i < mod; i++)
	{
		((uint8_t*)dst_ptr)[i] = ((uint8_t*)src_ptr)[i];
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

void* memmove(void* dst, const void* src, size_t n)
{
	if(dst == src)
		return dst;

	if(src < dst && (size_t)dst > (size_t)src + n)
	{
		for(int i = n - 1; i >= 0; i--)
		{
			((uint8_t*)dst)[i] = ((const uint8_t*)src)[i];
		}
	}
	else
	{
		return memcpy(dst, src, n);
	}

	return dst;
}