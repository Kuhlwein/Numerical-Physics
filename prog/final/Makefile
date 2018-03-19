CFLAGS = -Wall -std=gnu99  $$(gsl-config --cflags)
LDLIBS = $$(gsl-config --libs)

report.pdf : report.tex plot.tex
	latex report
	latex report
	dvipdf report

out.txt : main
	./main > out.txt

plot.tex : plot.gpi out.txt
	gnuplot plot.gpi

main : main.c

clean :
	$(RM) main out.txt plot.tex report.aux report.dvi report.log report.pdf
