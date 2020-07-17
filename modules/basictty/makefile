.PHONY: all

all: basictty.ko

basictty.ko: basictty.cpp $(KINCLUDE)/kernel/module.h $(KINCLUDE)/module/tty_module.h
	$(CC) $(CFLAGS) -I$(KINCLUDE) -I$(STDLIBINC) -c basictty.cpp -o basictty.ko

clean:
	-rm *.o
	-rm basictty.ko