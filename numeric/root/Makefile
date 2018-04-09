CXXFLAGS = -std=c++11 -Wall -O3
LDLIBS = -lstdc++ -lm -larmadillo
OBJ = main.o root.o ../lineq/qr_decomp.o

.PHONY: clean all

all : out.txt
	cat out.txt

out.txt : main
	./main > out.txt

main : $(OBJ)

clean:
	find . -type f -executable -delete
	$(RM) *.o *.txt *.pdf $(OBJ)
