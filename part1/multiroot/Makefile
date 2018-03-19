CFLAGS = -Wall -std=gnu99  $$(gsl-config --cflags)
LDLIBS = $$(gsl-config --libs)

.PHONEY : all

all : out.txt out2.txt plot.pdf
	cat out.txt out2.txt

plot.pdf : plot.gpi
	gnuplot plot.gpi

out.txt : main
	./main > out.txt

out2.txt : main2
	./main2 > out2.txt

main2 : main2.c

main : main.c

clean:
	$(RM) main main2 *.o *.txt
