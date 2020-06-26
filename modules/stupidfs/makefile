.PHONY: all

all: ramdisk.ko

ramdisk.ko: ramdisk.cpp $(KINCLUDE)/kernel/device.h
	$(CC) $(CFLAGS) -I$(KINCLUDE) -c ramdisk.cpp -o ramdisk.ko

clean:
	-rm *.o
	-rm ramdisk.ko