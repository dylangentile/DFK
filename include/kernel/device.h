#pragma once

class Device
{
public:
	Device() = delete;
	~Device();

};

class DataDevice;


class PhysicalDevice : public Device
{
public:
	PhysicalDevice();
	~PhysicalDevice();
	virtual int getDataDeviceCount() = 0;
	virtual void getDataDeviceArray(DataDevice** array);
};


class DataDevice : public Device
{
public:
	DataDevice();
	~DataDevice();

	virtual bool init() = 0;

};