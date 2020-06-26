ENVS := CC=clang++ CFLAGS="-target i386-unknown-elf -O1 -fno-rtti -fno-exceptions -nostdlib -Wall" LD=ld.lld KINCLUDE=$(PWD)/include/ 

.PHONY: modules kernel clean

all: kernel modules

kernel: cstdlib
	$(MAKE) -C src/ -e $(ENVS)

modules: cstdlib
	$(MAKE) -C modules/ -e  $(ENVS)

cstdlib:
	$(MAKE) -C cstdlib/ -e  $(ENVS)


linkmodules: 

clean:
	$(MAKE) -C src/ clean
	$(MAKE) -C modules/ clean