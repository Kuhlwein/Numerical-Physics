CFLAGS = -Wall -std=gnu99  $$(gsl-config --cflags)
LDLIBS = $$(gsl-config --libs)

.PHONEY : all

all : main plot.svg

main : main.c

dat.txt : main
	./main > dat.txt

plot.svg : plot.gpi dat.txt
	gnuplot plot.gpi
