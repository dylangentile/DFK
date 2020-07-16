.PHONY: all

all: vga.ko

vga.ko: vga.cpp $(KINCLUDE)/kernel/device.h $(KINCLUDE)/device/graphics_device.h
	$(CC) $(CFLAGS) -I$(KINCLUDE) -I$(STDLIBINC) -c vga.cpp -o vga.ko

clean:
	-rm *.o
	-rm vga.ko