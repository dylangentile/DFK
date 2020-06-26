ENVS := CC=$(CC) CFLAGS="$(CFLAGS)" LD=$(LD) KINCLUDE=$(KINCLUDE)

.PHONY: stupidfs ramdisk all

all: ramdisk stupidfs

ramdisk: 
	$(MAKE) -C ramdisk/ -e $(ENVS)

stupidfs:
	$(MAKE) -C stupidfs/ -e $(ENVS)

clean:
	$(MAKE) -C ramdisk/ clean
	$(MAKE) -C stupidfs/ clean