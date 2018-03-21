CC = gcc

.PHONY: default clean

default : out.txt
	cat out.txt

out.txt : main
	./main > out.txt

main : main.o nvector.o equal.o

clean :
	$(RM) out.txt main *.o
