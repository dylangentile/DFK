.PHONY: all

all: stupidfs.ko

stupidfs.ko: stupidfs.cpp
	$(CC) $(CFLAGS) -I$(KINCLUDE) -I$(STDLIBINC) -c stupidfs.cpp -o stupidfs.ko

clean:
	-rm *.o
	-rm stupidfs.ko