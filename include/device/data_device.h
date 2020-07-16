#pragma once
#include <kernel/device.h>


class PhysicalDataDevice;
class LogicalDataDevice;


class PhysicalDataDevice : public Device
{
public:
	PhysicalDataDevice();
	~PhysicalDataDevice();
	virtual int getDataDeviceCount() = 0;
	virtual void getLogicalArray(LogicalDataDevice** array) = 0;
};


class LogicalDataDevice : public Device
{
public:
	LogicalDataDevice();
	~LogicalDataDevice();

	virtual bool init() = 0;
	virtual size_t getSize() = 0;

	//read n-bytes into data pointer from address, return true/false for success
	virtual bool read(void* data, uintptr_t address, size_t bytes) = 0;
	//write n-bytes into address from data pointer, return true/false for success
	virtual bool write(uintptr_t address, void* data, size_t bytes) = 0;


};