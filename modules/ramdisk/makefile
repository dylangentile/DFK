
.PHONY: all

all: ramdisk

ramdisk: ramdisk.cpp
	$(CC) -I$(KINCLUDE) ramdisk.cpp -c

clean:
	-rm *.o
	-rm ramdisk