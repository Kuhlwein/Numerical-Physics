CFLAGS = -std=gnu99 -Wall -O
LDLIBS = -lm

.PHONEY:default
default: out.txt
	cat out.txt

out.txt: main
	./main > out.txt

main: main.c equal.c
	cc $(CFLAGS) main.c equal.c -o main

.PHONEY:clean
clean:
	$(RM) main out.txt
