CFLAGS = -Wall -std=gnu99  $$(gsl-config --cflags)
LDLIBS = $$(gsl-config --libs)

.PHONEY : all clean

all : main out.txt plot.svg out2.txt plot2.svg
	cat out.txt; cat out2.txt

out.txt : main
	./main > out.txt

out2.txt : main2
	./main2 > out2.txt

main : main.c

main2 : main2.c

plot.svg : out.txt plot.gpi
	gnuplot plot.gpi

plot2.svg : out2.txt plot2.gpi
	gnuplot plot2.gpi

clean :
	$(RM) main main2 *.txt
