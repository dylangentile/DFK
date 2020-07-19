.PHONY: all clean bootstrap

all: bootstrap


#image: bootstrap
#	@dd if=/dev/zero of=disk.img count=128 bs=0x100000
#	@dd if=mbr.sys of=disk.img conv=notrunc
#	@dd if=kernel of=disk.img bs=512 seek=16 conv=notrunc


bootstrap: raw_bootstrap
	cat pure64.sys raw_bootstrap > bootstrap	

raw_bootstrap: bootstrap.o main.o
	$(LD) -Tlink.ld bootstrap.o main.o -o raw_bootstrap_with_header
	@dd if=raw_bootstrap_with_header of=raw_bootstrap bs=1 iseek=0x1000 #we have to delete the ELF header
	-rm raw_bootstrap_with_header

main.o:
	nasm -felf64 -o main.o main.s


%.o: %.cpp
	$(CC) $(CFLAGS) -I$(KINCLUDE) -o $@ -c $<

clean:
	-rm *.o
	-rm bootstrap
	-rm raw_bootstrap