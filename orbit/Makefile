CFLAGS = -Wall -std=gnu99  $$(gsl-config --cflags)
LDLIBS = $$(gsl-config --libs)

.PHONEY : all

all : main out.txt plot.svg
	cat out.txt

out.txt : main
	./main > out.txt

main : main.c

plot.svg : plot.gpi
	gnuplot plot.gpi


