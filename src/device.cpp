#include <kernel/device.h>

Device::Device(DeviceType type) : mType(type)
{

}

Device::~Device()
{

}


PhysicalDataDevice::PhysicalDataDevice() : Device(kDeviceType_PhysicalDataDevice) 
{

}

PhysicalDataDevice::~PhysicalDataDevice()
{

}


LogicalDataDevice::LogicalDataDevice() : Device(kDeviceType_LogicalDataDevice)
{

}

LogicalDataDevice::~LogicalDataDevice()
{
	
}