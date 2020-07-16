#pragma once
#include "kernel/alloc.h"

extern "C"
{
	typedef enum
	{
		kDeviceType_NULL,
		kDeviceType_PhysicalDataDevice,
		kDeviceType_LogicalDataDevice,
		kDeviceType_GraphicsDevice
	} DeviceType;

	typedef struct
	{
		uint32_t driverId;
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
