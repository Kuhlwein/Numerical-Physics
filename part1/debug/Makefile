CFLAGS = -w -std=gnu99
CFLAGS += $$(gsl-config --cflags)
LDLIBS += $$(gsl-config --libs)

all: output
	cat output

output: main
	./main > output

clean:
	$(RM) main output
