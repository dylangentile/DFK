#pragma once
#include <kernel/kernint.h>
#include <device/graphics_device.h>

extern "C"
{
	int write(int fd, const void* data, size_t bytes);
	int open(const char* path);
	void klog(const char* str);
	void setGd(GraphicsDevice* GD);
}


