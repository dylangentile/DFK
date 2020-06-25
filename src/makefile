CC := clang++
CFLAGS := -target i386-unknown-elf -O1 -fno-rtti -fno-exceptions -nostdlib -Wall

ASM := /opt/local/bin/nasm
ASMFLAGS := -felf32

LD := ld.lld 
OBJS := kmain.o main.o


.PHONY: all clean

all: kernel


kernel: $(OBJS)
	$(LD) $(OBJS) -o kernel


kmain.o: kmain.cpp
	$(CC) $(CFLAGS) -c kmain.cpp

main.o: main.s
	$(ASM) $(ASMFLAGS) main.s

clean:
	rm $(OBJS)