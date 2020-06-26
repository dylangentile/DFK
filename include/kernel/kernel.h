#pragma once
#include <kernel/alloc.h>
#include <kernel/module.h>


class Kernel
{
public:
	Kernel();
	~Kernel();

	void init();
};