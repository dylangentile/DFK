ENVS := CC=$(CC) CFLAGS="$(CFLAGS)" LD=$(LD) KINCLUDE=$(KINCLUDE)

.PHONY: cstdlib clean all

all: cstdlib

cstdlib:
	$(info )
	$(info ********* Building cstdlib.o  *********)
	$(info )
	@$(MAKE) -C src/ -e $(ENVS)

clean:
	@$(MAKE) -C src/ clean