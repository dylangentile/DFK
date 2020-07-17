#CC := clang++
#CFLAGS := -target i386-unknown-elf -O1 -fno-rtti -fno-exceptions -nostdlib -Wall
#KINCLUDE := ../include

ASM := /opt/local/bin/nasm
ASMFLAGS := -felf64

LD := ld.lld 
LDFLAGS := -Tlink.ld
OBJS := main.o kmain.o kernel.o kio.o alloc.o device.o module.o


.PHONY: kernel clean depend

all: image

image: kernel
	@dd if=/dev/zero of=disk.img count=128 bs=1048576
	@dd if=mbr.sys of=disk.img conv=notrunc 
	@dd if=kernel of=disk.img bs=512 seek=16 conv=notrunc

kernel: rawkernel mbr.sys pure64.sys
	-rm kernel
	cat pure64.sys rawkernel > kernel


rawkernel: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(STDLIBOBJ) -o rawkernel_with_header
	dd if=rawkernel_with_header of=rawkernel bs=1 iseek=0x1000 #we have to delete the ELF header
	rm rawkernel_with_header


main.o: main.s kmain.cpp
	$(ASM) $(ASMFLAGS) main.s




depend:
	$(CC) -I$(KINCLUDE) $(CFLAGS) -MM -E *.cpp > .depend

%.o: %.cpp
	$(CC) -I$(KINCLUDE) -I$(STDLIBINC) $(CFLAGS) -o $@ -c $<

clean:
	-rm *.o
	-rm kernel rawkernel
	-rm *.img

#include .depend