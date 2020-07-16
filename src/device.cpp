#include <kernel/device.h>

Device::Device(DeviceType type) : mType(type)
{

}

Device::~Device()
{

}

#include <device/data_device.h>

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


#include <device/graphics_device.h>

GraphicsDevice::GraphicsDevice() : Device(kDeviceType_GraphicsDevice)
{

}

GraphicsDevice::~GraphicsDevice()
{

}


