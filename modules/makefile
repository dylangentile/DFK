ENVS := CC=$(CC) CFLAGS="$(CFLAGS)" LD=$(LD) KINCLUDE=$(KINCLUDE)

.PHONY: stupidfs ramdisk vga basictty all

all: ramdisk stupidfs vga basictty

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

basictty:
	$(info )
	$(info ********* Building BasicTTY Kernel Module *********)
	$(info )
	@$(MAKE) -C basictty/ -e $(ENVS)

clean:
	@$(MAKE) -C ramdisk/ clean
	@$(MAKE) -C stupidfs/ clean
	@$(MAKE) -C vga/ clean
	@$(MAKE) -C basictty/ clean