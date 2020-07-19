#ifndef CSTDLIB_STRING_H
#define CSTDLIB_STRING_H

#include <stddef.h>
extern "C"
{

	size_t strlen(const char* str);
	char* strcpy(char* dest, const char* src);

	void* memcpy(void* dst, const void* src, size_t n);
	void* memset(void* b, int c, size_t len);
	void* memmove(void* dst, const void* src, size_t n);
















}

#endif //CSTDLIB_STRING_H