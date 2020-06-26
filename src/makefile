#CC := clang++
#CFLAGS := -target i386-unknown-elf -O1 -fno-rtti -fno-exceptions -nostdlib -Wall
#KINCLUDE := ../include

ASM := /opt/local/bin/nasm
ASMFLAGS := -felf64

LD := ld.lld 
LDFLAGS := -Tlink.ld
OBJS := bootstrap.o main.o kmain.o kernel.o kio.o alloc.o device.o module.o


.PHONY: kernel clean depend

all: kernel


kernel: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(STDLIBOBJ) -o kernel

main.o: main.s kmain.cpp
	$(ASM) $(ASMFLAGS) main.s

bootstrap.o: bootstrap.s
	$(ASM) $(ASMFLAGS) bootstrap.s



depend:
	$(CC) -I$(KINCLUDE) $(CFLAGS) -MM -E *.cpp > .depend

%.o: %.cpp
	$(CC) -I$(KINCLUDE) -I$(STDLIBINC) $(CFLAGS) -o $@ -c $<

clean:
	-rm *.o
	-rm kernel

#include .depend