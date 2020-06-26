ENVS := CC=$(CC) CFLAGS="$(CFLAGS)" LD=$(LD) KINCLUDE=$(KINCLUDE)

.PHONY: stupidfs ramdisk all

all: ramdisk stupidfs

ramdisk: 
	$(info )
	$(info ********* Building RamDisk Kernel Module  *********)
	$(info )
	@$(MAKE) -C ramdisk/ -e $(ENVS)

stupidfs:
	$(info )
	$(info ********* Building StupidFS Kernel Module *********)
	$(info )
	@$(MAKE) -C stupidfs/ -e $(ENVS)

clean:
	@$(MAKE) -C ramdisk/ clean
	@$(MAKE) -C stupidfs/ clean