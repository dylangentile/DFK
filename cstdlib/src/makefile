.PHONY: all clean

all: cstdlib.o

cstdlib.o: string.o hash_map.o stdlib.o
	$(LD) -r $^ -o $@


%.o: %.cpp
	$(CC) -I$(KINCLUDE) -I../include $(CFLAGS) -o $@ -c $<


clean:
	-rm *.o