ENVS := CC=$(CC) CFLAGS="$(CFLAGS)" LD=$(LD) KINCLUDE=$(KINCLUDE)

.PHONY: cstdlib clean all

all: cstdlib

cstdlib:
	$(MAKE) -C src/ -e $(ENVS)

clean:
	$(MAKE) -C src/ clean