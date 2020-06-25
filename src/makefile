CC := clang++
CFLAGS := -target i386-unknown-elf -O1 -fno-rtti -fno-exceptions -nostdlib -Wall -I../include

ASM := /opt/local/bin/nasm
ASMFLAGS := -felf32

LD := ld.lld 
LDFLAGS := 
OBJS := main.o kmain.o kernel.o kio.o 


.PHONY: all clean depend

all: kernel


kernel: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o kernel

main.o: main.s kmain.cpp
	$(ASM) $(ASMFLAGS) main.s



depend:
	$(CC) $(CFLAGS) -MM -E *.cpp > .depend

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	-rm *.o
	-rm kernel

#include .depend