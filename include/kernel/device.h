#pragma once
#include "kernel/alloc.h"

extern "C"
{
	typedef enum
	{
		kDeviceType_NULL,
		kDeviceType_PhysicalDataDevice,
		kDeviceType_LogicalDataDevice
	} DeviceType;

	typedef struct
	{
		long driverId;
		DeviceType deviceType;
	}DriverInfo;
}



class Device
{
protected:
	Device(DeviceType type);
public:
	~Device();

	const DeviceType mType;

};

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


#define GENERATE_DEVICE_DRIVER(_DRIVERID, _DEVTYPE, _OBJECT) \
extern "C" { \
void generated_getDriverInfo(DriverInfo* info) { \
	info->driverId = _DRIVERID; \
	info->deviceType = _DEVTYPE; \
} \
Device* generated_createDriverInstance() { \
	_OBJECT* dev = new _OBJECT(); \
	return static_cast<Device*>(dev); \
} }
