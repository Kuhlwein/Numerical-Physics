CXXFLAGS = -std=c++11 -Wall -O3
LDLIBS = -lstdc++ -lm -larmadillo
OBJ = main.o lsfit.o ../lineq/qr_decomp.o ../eigen/jacobi.o

.PHONY: clean all

all : out.txt plot.pdf
	cat out.txt

out.txt : main
	./main > out.txt

main : $(OBJ)

plot.pdf : out.txt plot.gpi
	gnuplot plot.gpi

clean:
	find . -type f -executable -delete
	$(RM) *.o *.txt *.pdf $(OBJ)
