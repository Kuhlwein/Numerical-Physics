CFLAGS = -Wall -std=gnu99  $$(gsl-config --cflags)
LDLIBS = $$(gsl-config --libs)

.PHONEY : all

all : main out.txt plot.tex report.pdf
	cat out.txt

report.pdf : report.tex plot.tex
	latex report
	latex report
	dvipdf report

out.txt : main
	./main -3 3 0.2 > out.txt

plot.tex : plot.gpi
	gnuplot plot.gpi

main : main.c
