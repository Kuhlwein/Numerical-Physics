CFLAGS = -Wall -std=gnu99  $$(gsl-config --cflags)
LDLIBS = $$(gsl-config --libs)

.PHONEY : all

all : out.txt
	cat out.txt

out.txt : main
	./main > out.txt

main : main.c

clean:
	$(RM) main *.o out.txt
