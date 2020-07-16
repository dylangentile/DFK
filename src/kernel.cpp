#include <kernel/kernel.h>
#include <kernel/kio.h>
#include <kernel/cpuio.h>


Kernel::Kernel()
{

}

Kernel::~Kernel()
{
	
}

void
Kernel::init()
{
	mP64.ACPI = 		(uint64_t*)0x5000;
	mP64.BSP_ID = 		(uint32_t*)0x5008;
	mP64.CPUSPEED = 	(uint16_t*)0x5010;
	mP64.CORES_ACTIVE = (uint16_t*)0x5012;
	mP64.CORES_DETECT = (uint16_t*)0x5014;

	mP64.RAMAMOUNT = 	(uint32_t*)0x5020;

	mP64.IOAPIC_COUNT = (uint8_t*) 0x5030;

	mP64.HPET = 		(uint64_t*)0x5040;

	mP64.LAPIC = 		(uint64_t*)0x5060;
	mP64.IOAPIC = 		(uint64_t*)0x5068;
	mP64.VIDEO_BASE = 	(uint32_t*)0x5080;
	mP64.VIDEO_X = 		(uint16_t*)0x5084;
	mP64.VIDEO_Y = 		(uint16_t*)0x5086;
	mP64.VIDEO_DEPTH = 	(uint8_t*) 0x5088;

	mP64.APIC_ID = 		(uint8_t*) 0x5100;


	uint8_t* video_pointer = (uint8_t*)*mP64.VIDEO_BASE;
	for(int i = 0; i < 0x400 * 0x300 * 3;)
	{
		video_pointer[i] = 0x1f;
		i++;
		video_pointer[i] = 0x1f;
		i++;
		video_pointer[i] = 0xEE;
		i++;
	}
}
