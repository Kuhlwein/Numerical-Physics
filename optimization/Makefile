CFLAGS = -Wall -std=gnu99  $$(gsl-config --cflags)
LDLIBS = $$(gsl-config --libs)

.PHONEY : all

all : out.txt plot.pdf
	cat out.txt out2.txt

out.txt : main
	./main > out.txt

main : main.c

out2.txt : main2
	./main2 > out2.txt

main2 : main2.c

plot.pdf : plot.gpi out2.txt
	gnuplot plot.gpi

clean:
	$(RM) main main2 *.o *.txt
