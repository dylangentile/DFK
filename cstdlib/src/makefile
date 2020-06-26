.PHONY: all

all: cstdlib.o

cstdlib.o: string.o
	$(LD) $< -o $@


%.o: %.cpp
	$(CC) -I../include $(CFLAGS) -o $@ -c $<