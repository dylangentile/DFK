#ifndef CSTDLIB_STDLIB_H
#define CSTDLIB_STDLIB_H
#include <stddef.h>

void* malloc(size_t size);
void* calloc(size_t n, size_t size);
void free(void* ptr);


#endif //CSTDLIB_STDLIB_H