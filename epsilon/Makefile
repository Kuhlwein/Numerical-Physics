CFLAGS = -std=gnu99 -Wall -O

.PHONEY:default
default: out.txt
	cat out.txt

out.txt: main
	./main > out.txt

main: main.c
	cc $(CFLAGS) main.c -o main

.PHONEY:clean
clean:
	$(RM) main out.txt
