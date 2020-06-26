#pragma once
#include <kernel/kernint.h>

extern "C"
{
	int write(int fd, const void* data, size_t bytes);
	int open(const char* path);
	void klog(const char* str);
}