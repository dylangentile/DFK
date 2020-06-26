#include <string.h>

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