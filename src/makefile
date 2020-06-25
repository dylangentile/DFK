CC := clang++
CFLAGS := -target i386-unknown-elf -O1 -fno-rtti -fno-exceptions -nostdlib -Wall -I../include

ASM := /opt/local/bin/nasm
ASMFLAGS := -felf32

LD := ld.lld 
LDFLAGS := 
OBJS := kmain.o main.o


.PHONY: all clean

all: kernel


kernel: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o kernel


kmain.o: kmain.cpp
	$(CC) $(CFLAGS) -c kmain.cpp

main.o: main.s
	$(ASM) $(ASMFLAGS) main.s

clean:
	rm $(OBJS)