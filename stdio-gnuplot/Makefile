CFLAGS = -Wall -std=gnu99
LDLIBS = -lm

.PHONEY : all

all : main-stdio main-cmdline in.txt out.io.txt out.cmd.txt plot.svg

main-stdio : main-stdio.c

main-cmdline : main-cmdline.c

in.txt :
	seq 0 0.1 5 | sed -e 's/,/./g' > in.txt

out.io.txt : in.txt main-stdio
	cat in.txt | ./main-stdio > out.io.txt

out.cmd.txt : in.txt main-cmdline
	./main-cmdline $$(cat in.txt) > out.cmd.txt

plot.svg : plot.gpi
	gnuplot plot.gpi

clean:
	$(RM) *.o *.txt main-cmdline main-stdio
