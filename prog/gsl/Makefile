CFLAGS = -Wall -std=gnu99  $$(gsl-config --cflags)
LDLIBS = $$(gsl-config --libs)

.PHONEY : all

all : main plot.svg out.txt
	cat out.txt

out.txt : main-linalg
	./main-linalg > out.txt

main : main.c

main-linalg : main-linalg.c

dat.txt : main
	./main > dat.txt

plot.svg : plot.gpi dat.txt
	gnuplot plot.gpi
