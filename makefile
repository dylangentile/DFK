ENVS := CC=clang++ CFLAGS=" -std=c++11 -target x86_64-unknown-elf -O0 -g -ffreestanding -fno-rtti -fno-exceptions -nostdlib -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -Wall" LD=ld.lld KINCLUDE=$(PWD)/include/ STDLIBINC=$(PWD)/cstdlib/include STDLIBOBJ=$(PWD)/cstdlib/src/cstdlib.o

.PHONY: modules kernel cstdlib clean

all: kernel modules

kernel: cstdlib
	$(info )
	$(info ********* Building Kernel *********)
	$(info )
	@$(MAKE) -C src/ -e $(ENVS)

modules: cstdlib
	@$(MAKE) -C modules/ -e  $(ENVS)

cstdlib:
	@$(MAKE) -C cstdlib/ -e  $(ENVS)


linkmodules: 

clean:
	@$(MAKE) -C src/ clean
	@$(MAKE) -C modules/ clean
	@$(MAKE) -C cstdlib/ clean