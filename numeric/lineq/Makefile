CXXFLAGS = -std=c++11 -Wall
LDLIBS = -lstdc++ -lm -larmadillo

.PHONY: clean all

all : out.txt
	cat out.txt

out.txt : main
	./main > out.txt

main : main.o qr_gramschmidt.o

clean:
	find . -type f -executable -delete
	$(RM) *.o out*
