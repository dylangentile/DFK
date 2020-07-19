#include <kernel/cpuio.h>
/*
The bootstrapper reads from the master drive using ATA PIO with 28-bit lba
The bootstrapper reads the kernel and the modules into memory locations accesssible
by the kernel

*/

#define READ_SECTORS 0x20

void poll_busy()
{
	while((inb(0x1F7)& 0x80) != 0);
}

void poll_drq()
{
	while((!(inb(0x1F7)&0x08)) != 0);
}

// Remember each sector is 512 bytes
void read_ata_drive(uint16_t* dst, uint32_t sector, uint8_t sector_count)
{
	poll_busy();
	outb(0x1F6, 0xE0 | ((sector >> 24) & 0x0F));
	//outb(0x1F1, 0x00);
	outb(0x1F2, sector_count);
	outb(0x1F3, (uint8_t)sector);
	outb(0x1F4, (uint8_t)(sector >> 8));
	outb(0x1F5, (uint8_t)(sector >> 16));

	outb(0x1F7, READ_SECTORS);

	for(int i = 0; i < sector_count; i++)
	{
		poll_busy();
		poll_drq();

		for(int j = 0; j < 256; j++)
		{
			*dst = inw(0x1F0);
			dst++;
		}
		


	}
	

}

extern "C"
{
	void bmain(void)
	{
		uint8_t* buf = (uint8_t*)0x800000;
		read_ata_drive((uint16_t*)buf, 0x800000 / 0x200, 1);

		while(1);
	}
}