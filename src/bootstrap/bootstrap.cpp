#include <kernel/cpuio.h>
/*
The bootstrapper reads from the master drive using ATA PIO with 28-bit lba
The bootstrapper reads the kernel and the modules into memory locations accesssible
by the kernel

*/
void write_str(const char* msg);

void write_bytes(void* buf, size_t bytes, bool spaces = false, bool little_endian = false);


#define READ_SECTORS 0x20
#define KERNEL_LOCATION 0x400000
#define MODULE_HEADER_LOCATION 0x800000
#define KERNEL_SIZE 0x400000

static_assert(KERNEL_SIZE % 0x200 == 0, "kernel is not evenly divisible!");


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

	if(sector_count == 0)
	{
		for(int i = 0; i < 0x100; i++)
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
	else
	{
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
	

}

void
read_pages(uintptr_t dst, uint32_t page_count, uint32_t page_offset)
{
	write_str("Reading to memory location ");
	write_bytes(&dst, sizeof(dst));
	write_str(", ");
	write_bytes(&page_count, sizeof(page_count));
	write_str(" pages from page ");
	write_bytes(&page_offset, sizeof(page_offset));
	write_str("\r\n");

	uint32_t floor_pages  = (page_count/0x100)*0x100;
	uint32_t extra_pages = page_count%0x100;

	uint32_t current_page = page_offset;
	for(; current_page < floor_pages + page_offset; 
		current_page += 0x100, dst += 0x100 * 0x200)
	{
		/*write_bytes(&current_page, sizeof(current_page));
		write_str(" ");
		write_bytes(&dst, sizeof(dst));
		write_str("\r\n");*/
		read_ata_drive((uint16_t*)dst, current_page, 0x00);

	}

	if(extra_pages != 0)
	{
		read_ata_drive((uint16_t*)dst, current_page, extra_pages);
	}
}




#define PORT 0x3f8   /* COM1 */
 
void init_serial() {
	outb(PORT + 1, 0x00);    // Disable all interrupts
	outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(PORT + 1, 0x00);    //                  (hi byte)
	outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int is_transmit_empty() {
   return inb(PORT + 5) & 0x20;
}
 
void write_serial(char a) {
   while (is_transmit_empty() == 0);
 
   outb(PORT,a);
}

void write_str(const char* msg)
{
	for(const char* ptr = msg; *ptr != '\0'; ptr++)
	{
		write_serial(*ptr);
	}
}

int serial_received() {
   return inb(PORT + 5) & 1;
}
 
char read_serial() {
   while (serial_received() == 0);
 
   return inb(PORT);
}

void
write_bytes(void* buf, size_t bytes, bool spaces, bool little_endian)
{
	if(little_endian)
	{
		for(uint8_t* ptr = (uint8_t*)buf; ptr != (uint8_t*)buf + bytes; ptr++)
		{
			uint8_t tmp = 0;
			char a = (tmp =   *ptr & 0x0F)       < 0x0A ? tmp + '0' : (tmp - 0x0A) + 'A'; 
			char b = (tmp = ((*ptr & 0xF0) >> 4))< 0x0A ? tmp + '0' : (tmp - 0x0A) + 'A';
			write_serial(b);
			write_serial(a);
			if(spaces)
				write_serial(' ');
		}

	}
	else
	{
		for(uint8_t* ptr = (uint8_t*)buf + bytes - 1; ptr >= (uint8_t*)buf; ptr--)
		{
			uint8_t tmp = 0;
			char a = (tmp =   *ptr & 0x0F)       < 0x0A ? tmp + '0' : (tmp - 0x0A) + 'A'; 
			char b = (tmp = ((*ptr & 0xF0) >> 4))< 0x0A ? tmp + '0' : (tmp - 0x0A) + 'A';
			write_serial(b);
			write_serial(a);
			if(spaces)
				write_serial(' ');
		}
	}
}

#define EI_NIDENT 16

extern "C"
{

	/*uint64_t entry asm("entry_loc"); 

    

    typedef struct {
        unsigned char e_ident[EI_NIDENT];
        uint16_t      e_type;
        uint16_t      e_machine;
        uint32_t      e_version;
        uint64_t      e_entry;
        uint64_t      e_phoff;
        uint64_t      e_shoff;
        uint32_t      e_flags;
        uint16_t      e_ehsize;
        uint16_t      e_phentsize;
        uint16_t      e_phnum;
        uint16_t      e_shentsize;
        uint16_t      e_shnum;
        uint16_t      e_shstrndx;
    } Elf64_Ehdr;
	*/


	void bmain(void)
	{
		
		init_serial(); //probably already initialized by pure64 but what-evs
		
		write_str("\r\nEntering bootloader...\r\n");


		read_pages(KERNEL_LOCATION, KERNEL_SIZE/0x200, KERNEL_LOCATION/0x200);

		uint8_t* buf = (uint8_t*)MODULE_HEADER_LOCATION;
		read_ata_drive((uint16_t*)buf, MODULE_HEADER_LOCATION / 0x200, 1);

		/*
		Module layout
		First 8 bytes: module_count;
		Each subsequent 8 bytes (up to filling a page) 
		is a module location on disk(bytes not pages)
		The last module location value is not acutally a module,
		nor is it counted in module_count
		but instead is used to find the size of the last module.

		*/

		uint64_t* module_data = (uint64_t*)buf;
		uint64_t module_count = *module_data;
		module_data++;
		write_bytes(&module_count, sizeof(module_count), true);
		write_str("\r\n");
		if(module_count != 0)
		{
			for(uint64_t i = 0; i < module_count; i++)
			{
				uint64_t location = *module_data;
				module_data++;
				uint64_t next = *module_data;

				//all of this is be page aligned by the image generator
				read_pages((uintptr_t)location, (next - location)/0x200, location/0x200); 
			}
		}



		//Elf64_Ehdr* elf_header = (Elf64_Ehdr*)KERNEL_LOCATION;

		//asm(".intel_syntax noprefix");
		
		//entry = elf_header->e_entry;
		//write_bytes(&entry, sizeof(entry));
		//write_str("\r\n");

		//asm("jmp entry_loc");

		
	

		//while(1);
	}
}