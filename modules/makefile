
ENVS := CC=$(CC) ASM=$(ASM) LD=$(LD)

.PHONY: all

all: ramdisk

ramdisk:
	$(MAKE) -C ramdisk/ -e $(ENVS)

clean:
	$(MAKE) -C ramdisk clean