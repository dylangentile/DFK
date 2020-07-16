ENVS := CC=$(CC) CFLAGS="$(CFLAGS)" LD=$(LD) KINCLUDE=$(KINCLUDE)

.PHONY: stupidfs ramdisk vga all

all: ramdisk stupidfs vga

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

vga:
	$(info )
	$(info ********* Building VGA Kernel Module *********)
	$(info )
	@$(MAKE) -C vga/ -e $(ENVS)

clean:
	@$(MAKE) -C ramdisk/ clean
	@$(MAKE) -C stupidfs/ clean
	@$(MAKE) -C vga/ clean