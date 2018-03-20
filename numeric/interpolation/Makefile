CXXFLAGS = -std=c++11 -Wall
LDLIBS = -lstdc++ -lm

.PHONY: clean all

all : out.txt plot.pdf
	cat out.txt

out.txt : main
	./main > out.txt

plot.pdf : plot.gpi out.txt
	gnuplot plot.gpi

main : main.o spline.o

clean:
	find . -type f -executable -delete
	$(RM) *.o out*
