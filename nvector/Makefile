CC = gcc

.PHONY: default

default : out.txt
	cat out.txt

out.txt : main
	./main > out.txt

main : main.o nvector.o equal.o
