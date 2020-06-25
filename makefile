ENVS := CC=clang++ ASM=/opt/local/bin/nasm LD=ld.lld KINCLUDE=$(PWD)/include/

.PHONY: all clean

all: kernel modules


kernel:
	$(MAKE) -C src/ -e $(ENVS)

modules:
	$(MAKE) -C modules/ -e  $(ENVS)


clean:
	$(MAKE) -C src/ clean
	$(MAKE) -C modules/ clean