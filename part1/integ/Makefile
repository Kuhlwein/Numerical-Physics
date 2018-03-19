CFLAGS = -Wall -std=gnu99  $$(gsl-config --cflags)
LDLIBS = $$(gsl-config --libs)

.PHONEY : all

all : out.txt plot.pdf
	cat out.txt

out.txt : main
	./main > out.txt

dat.txt : main2
	./main2 > dat.txt

main2 : main2.c

main : main.c

plot.pdf : dat.txt plot.gpi
	gnuplot plot.gpi

clean:
	$(RM) main main2 *.o *.txt
