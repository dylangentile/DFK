#pragma once
#include <kernel/alloc.h>
#include <kernel/module.h>


typedef struct 
{
	uint64_t* ACPI;
	uint32_t* BSP_ID;
	uint16_t* CPUSPEED;
	uint16_t* CORES_ACTIVE;
	uint16_t* CORES_DETECT;

	uint32_t* RAMAMOUNT;

	uint8_t* IOAPIC_COUNT;

	uint64_t* HPET;
	
	uint64_t* LAPIC;
	uint64_t* IOAPIC;
	uint32_t* VIDEO_BASE;
	uint16_t* VIDEO_X;
	uint16_t* VIDEO_Y;
	uint8_t* VIDEO_DEPTH;

	uint8_t* APIC_ID;

}Pure64Data;

class Kernel
{
public:
	Kernel();
	~Kernel();

	void init();
private:
	Pure64Data mP64;
};