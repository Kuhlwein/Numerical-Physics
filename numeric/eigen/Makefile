CXXFLAGS = -std=c++11 -Wall -DARMA_NO_DEBUG -O3
LDLIBS = -lstdc++ -lm -larmadillo

.PHONY: clean all

all : out.txt
	cat out.txt

out.txt : main plot.pdf
	./main > out.txt

dat.txt : benchmark
	./benchmark > dat.txt

main : main.o jacobi.o

benchmark : benchmark.o jacobi.o

plot.pdf : plot.gpi dat.txt
	gnuplot plot.gpi

clean:
	find . -type f -executable -delete
	$(RM) *.o *.txt *.pdf
