CXXFLAGS = -std=c++11 -Wall -O3 -fopenmp
LDLIBS = -lstdc++ -lm -lgomp
OBJ = main.o montecarlo.o

.PHONY: clean all

all : out.txt plot.pdf
	cat out.txt

out.txt : main
	./main > out.txt

main : $(OBJ)

plot.pdf : plot.gpi out.txt
	gnuplot plot.gpi

clean:
	find . -type f -executable -delete
	$(RM) *.o *.txt *.pdf $(OBJ)
