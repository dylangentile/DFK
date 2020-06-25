#pragma once


extern "C"
{
	int write(int fd, const void* data, int bytes);
	int open(const char* path);
}