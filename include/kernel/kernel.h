#pragma once
#include "module.h"

typedef struct RamData
{
	
} RamData;

typedef struct SystemInfo
{
	long ramsize;
} SystemInfo;


class Kernel
{
public:
	Kernel();
	~Kernel();

	void init();

	//void load_module(Module*);
private:
	SystemInfo mInfo;
};