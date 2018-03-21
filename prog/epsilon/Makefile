CFLAGS = -std=gnu99 -Wall -O
LDLIBS = -lm

.PHONEY:default clean

default: out.txt
	cat out.txt

out.txt: main
	./main > out.txt

main: main.c equal.o

clean:
	$(RM) main out.txt *.o
